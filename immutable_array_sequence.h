#ifndef _IMMUTABLE_ARRAY_SEQUANCE_H_
#define _IMMUTABLE_ARRAY_SEQUANCE_H_

#include "array_sequence.h"

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    virtual Sequence<T>* Instance() override {
        return new ImmutableArraySequence<T>(*this);
    }

    virtual Sequence<T>* CreateSequence(const DynamicArray<T> &arr) const override {
        return new ImmutableArraySequence<T>(arr);
    }

public:
    ImmutableArraySequence() :  ArraySequence<T>() {}
    ImmutableArraySequence(const T* items, int count) : ArraySequence<T>(items, count) {}
    explicit ImmutableArraySequence(int size) : ArraySequence<T>(size) {}
    ImmutableArraySequence(const DynamicArray<T> &arr) : ArraySequence<T>(arr) {}
    ImmutableArraySequence(const ArraySequence<T> &other) : ArraySequence<T>(other) {}
};

#endif /* _MUTABLE_ARRAY_SEQUANCE_H_ */