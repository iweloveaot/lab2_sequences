#ifndef _LIST_SEQUENCE_BUILDER_H_
#define _LIST_SEQUENCE_BUILDER_H_

#include "mutable_list_sequence.h"
#include "immutable_list_sequence.h"

template<typename T>
class ListSequenceBuilder {
private:
    LinkedList<T> buffer;
    bool buildImmutable;

public:
    ListSequenceBuilder();

    ListSequenceBuilder& SetImmutable(bool val);
    ListSequenceBuilder& Add(const T& item);
    ListSequenceBuilder& AddToFront(const T& item);
    ListSequenceBuilder& AddRange(const T* items, int count);
    ListSequenceBuilder& AddRange(const Sequence<T>* seq);
    ListSequenceBuilder& Clear();

    Sequence<T>* Build() const;
    MutableListSequence<T>* BuildMutable() const;
    ImmutableListSequence<T>* BuildImmutable() const;
};

#include "list_sequence_builder.tpp"

#endif // _LIST_SEQUENCE_BUILDER_H_