#ifndef _ARRAY_SEQUENCE_BUILDER_H_
#define _ARRAY_SEQUENCE_BUILDER_H_

#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"

template<typename T>
class ArraySequenceBuilder {
private:
    DynamicArray<T> buffer;
    bool buildImmutable;

public:
    ArraySequenceBuilder();

    ArraySequenceBuilder& SetImmutable(bool val);
    ArraySequenceBuilder& Add(const T& item);
    ArraySequenceBuilder& AddRange(const T* items, int count);
    ArraySequenceBuilder& AddRange(const Sequence<T>* seq);
    ArraySequenceBuilder& Clear();

    Sequence<T>* Build() const;
    MutableArraySequence<T>* BuildMutable() const;
    ImmutableArraySequence<T>* BuildImmutable() const;
};

#include "array_sequence_builder.tpp"

#endif // _ARRAY_SEQUENCE_BUILDER_H_