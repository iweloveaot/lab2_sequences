#ifndef _IMMUTABLE_LIST_SEQUANCE_H_
#define _IMMUTABLE_LIST_SEQUANCE_H_

#include "list_sequance.h"

template <typename T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    virtual Sequence<T>* Instance() override {
        return new ImmutableListSequence<T>(*this);
    }

    virtual Sequence<T>* CreateSequence(const LinkedList<T> &lst) const override {
        return new ImmutableListSequence<T>(lst);
    };

public:
    ImmutableListSequence() :  ListSequence<T>() {}
    ImmutableListSequence(const T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T> &lst) : ListSequence<T>(lst) {}
    ImmutableListSequence(const ListSequence<T> &other) : ListSequence<T>(other) {}
};

#endif /* _MUTABLE_LIST_SEQUANCE_H_ */