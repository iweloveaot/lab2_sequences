#ifndef _LIST_SEQUANCE_H_
#define _LIST_SEQUANCE_H_

#include "linked_list.h"
#include "sequance.h"

template <typename T>
class ListSequence : public Sequence<T> {
private:

    LinkedList<T>* list;
    
    virtual ListSequenceBase<T>* Clone() const = 0;

public:
    ListSequence() : list(new LinkedList<T>()) {}
    ListSequence(T* items, int count) : list(new LinkedList<T>(items, count)) {}
    ListSequence(const LinkedList<T>& lst) : list(new LinkedList<T>(lst)) {}
    ListSequence(const ListSequence<T>& other) : list(new LinkedList<T>(*(other->list))) {}
    virtual ~ListSequence() { 
        delete list;
    }

    T GetFirst() const override {
        return list->GetFirst();
    }

    T GetLast() const override {
        return list->GetLast();
    }

    T Get(int index) const override {
        return list->Get(index);
    }

    int GetLength() const override {
        return list->GetLength();
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        LinkedList<T> sub = list->GetSubList(startIndex, endIndex);
        ListSequence<T>* result = Clone();
        delete result->list;
        result->list = new LinkedList<T>(sub);
        return result;
    }

    T operator[](int index) const override {
        return Get(index);
    }

    Sequence<T>* Map(T (*func)(T)) const override {
        LinkedList<T> newList;
        int sz = list->GetLength();
        for (int i = 0; i < sz; ++i)
            newList.Append(func(list->Get(i)));
        ListSequenceBase<T>* result = Clone();
        delete result->list;
        result->list = new LinkedList<T>(newList);
        return result;
    }

    Sequence<T>* Where(bool (*pred)(T)) const override {
        LinkedList<T> filtered;
        int sz = list->GetLength();
        for (int i = 0; i < sz; ++i) {
            T val = list->Get(i);
            if (pred(val))
                filtered.Append(val);
        }
        ListSequenceBase<T>* result = Clone();
        delete result->list;
        result->list = new LinkedList<T>(filtered);
        return result;
    }

    T Reduce(T (*func)(T, T), T init) const override {
        int sz = list->GetLength();
        T acc = init;
        for (int i = 0; i < sz; ++i)
            acc = func(acc, list->Get(i));
        return acc;
    }

    Option<T> FindFirst(bool (*pred)(T)) const override {
        int sz = list->GetLength();
        for (int i = 0; i < sz; ++i) {
            T val = list->Get(i);
            if (!pred || pred(val))
                return Option<T>(val);
        }
        return Option<T>();
    }

    Option<T> FindLast(bool (*pred)(T)) const override {
        int sz = list->GetLength();
        for (int i = sz - 1; i >= 0; --i) {
            T val = list->Get(i);
            if (!pred || pred(val))
                return Option<T>(val);
        }
        return Option<T>();
    }
};

#endif /* _LIST_SEQUANCE_H_ */