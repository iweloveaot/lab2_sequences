#ifndef _LIST_SEQUANCE_H_
#define _LIST_SEQUANCE_H_

#include "linked_list.h"
#include "sequance.h"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list; 

protected:
    virtual Sequence<T>* CreateSequence(const LinkedList<T> &lst) const = 0;
    virtual Sequence<T>* Instance() = 0;
    virtual Sequence<T>* AppendImplict(const T &item) override {
        list.Append(item);
        return this;
    };

    virtual Sequence<T>* PrependImplict(const T &item) override {
        list.Prepend(item);
        return this;
    }

    virtual Sequence<T>* InsertAtImplict(const T &item, int index) override {
        list.InsertAt(item, index);
        return this;
    }

    virtual Sequence<T>* ConcatImplict(const Sequence<T>* other) override {
        for (int i = 0; i < other->GetLength(); i++) {
            list.Append(other->Get(i));
        }
        return this;
    }

public:
    ListSequence() : list(LinkedList<T>()) {}
    ListSequence(const T* items, int count) : list(LinkedList<T>(items, count)) {}
    ListSequence(const LinkedList<T> &lst) : list(LinkedList<T>(lst)) {}
    ListSequence(const ListSequence<T> &other) : list(LinkedList<T>(other.list)) {}
    ~ListSequence() override {}

    const T& GetFirst() const override {
        return list.GetFirst();
    }

    const T& GetLast() const override {
        return list.GetLast();
    }

    const T& Get(int index) const override {
        return list.Get(index);
    }

    int GetLength() const override {
        return list.GetLength();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override 
    {
        LinkedList<T> *tmp_list = list.GetSubList(startIndex, endIndex);
        Sequence<T>* sub_seq = CreateSequence(*tmp_list);
        delete tmp_list;
        return sub_seq;
    }
    
    const T& operator[](int index) const override {
        return Get(index);
    }

    Sequence<T>* Map(T (*func)(const T&)) const override {
        int size = list.GetLength();
        LinkedList<T> mapped;
        for (int i = 0; i < size; i++) {
            mapped.Append(func(list.Get(i)));
        }
        Sequence<T>* result = CreateSequence(mapped);
        return result;
    }

    Sequence<T>* Where(bool (*pred)(const T&)) const override {
        LinkedList<T> filtered;
        int size = list.GetLength();
        for (int i = 0; i < size; i++) {
            T val = list.Get(i);
            if (pred(val))
                filtered.Append(val);
        }
        Sequence<T>* result = CreateSequence(filtered);
        return result;
    }

    void Reduce(T (*func)(const T&, const T&), const T &init, T *result) const override {
        int size = list.GetLength();
        T reduced = init;
        for (int i = 0; i < size; i++)
            reduced = func(reduced, list.Get(i));
        *result = reduced;
    }


    // Option<T> FindFirst(bool (*pred)(T)) const override {
    //     int sz = list->GetLength();
    //     for (int i = 0; i < sz; ++i) {
    //         T val = list->Get(i);
    //         if (!pred || pred(val))
    //             return Option<T>(val);
    //     }
    //     return Option<T>();
    // }

    // Option<T> FindLast(bool (*pred)(T)) const override {
    //     int sz = list->GetLength();
    //     for (int i = sz - 1; i >= 0; --i) {
    //         T val = list->Get(i);
    //         if (!pred || pred(val))
    //             return Option<T>(val);
    //     }
    //     return Option<T>();
    // }
};

#endif /* _LIST_SEQUANCE_H_ */