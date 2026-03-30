#ifndef _MUTABLE_LIST_SEQUANCE_H_
#define _MUTABLE_LIST_SEQUANCE_H_

#include "list_sequance.h"

template <typename T>
class MutableListSequence : public ListSequence<T> {
protected:
    virtual Sequence<T>* Instance() override {
        return this;
    }

    virtual Sequence<T>* CreateSequence(const LinkedList<T> &lst) const override {
        return new MutableListSequence<T>(lst);
    }

public:
    MutableListSequence() :  ListSequence<T>() {}
    MutableListSequence(const T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T> &lst) : ListSequence<T>(lst) {}
    MutableListSequence(const ListSequence<T> &other) : ListSequence<T>(other) {}
};

#endif /* _MUTABLE_LIST_SEQUANCE_H_ */