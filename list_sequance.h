#ifndef _LIST_SEQUANCE_H_
#define _LIST_SEQUANCE_H_

#include "linked_list.h"
#include "sequance.h"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list; 
    // virtual ListSequenceBase<T>* Clone() const = 0;

protected:
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

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        ListSequence<T> *sub_seq = new ListSequence<T>();
        sub_seq->list = *(list.Concat(other->list));
        return sub_seq;
    }



public:
    ListSequence() : list(LinkedList<T>()) {}
    ListSequence(const T* items, int count) : list(LinkedList<T>(items, count)) {}
    ListSequence(const LinkedList<T> &lst) : list(LinkedList<T>(lst)) {}
    ListSequence(const ListSequence<T> &other) : list(LinkedList<T>(other.list)) {}
    ~ListSequence() {}

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

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        ListSequence<T> *sub_seq = new ListSequence<T>();
        sub_seq->list = *(list.GetSubList(startIndex, endIndex));
        return sub_seq;
    }

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        ListSequence<T> *sub_seq = new ListSequence<T>();
        sub_seq->list = *(list.Concat(other->list));
        return sub_seq;
    }
    
    const T& operator[](int index) const override {
        return Get(index);
    }

    // Sequence<T>* Map(T (*func)(T)) const override {
    //     LinkedList<T> newList;
    //     int sz = list->GetLength();
    //     for (int i = 0; i < sz; ++i)
    //         newList.Append(func(list->Get(i)));
    //     ListSequenceBase<T>* result = Clone();
    //     delete result->list;
    //     result->list = new LinkedList<T>(newList);
    //     return result;
    // }

    // Sequence<T>* Where(bool (*pred)(T)) const override {
    //     LinkedList<T> filtered;
    //     int sz = list->GetLength();
    //     for (int i = 0; i < sz; ++i) {
    //         T val = list->Get(i);
    //         if (pred(val))
    //             filtered.Append(val);
    //     }
    //     ListSequenceBase<T>* result = Clone();
    //     delete result->list;
    //     result->list = new LinkedList<T>(filtered);
    //     return result;
    // }

    // T Reduce(T (*func)(T, T), T init) const override {
    //     int sz = list->GetLength();
    //     T acc = init;
    //     for (int i = 0; i < sz; ++i)
    //         acc = func(acc, list->Get(i));
    //     return acc;
    // }

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