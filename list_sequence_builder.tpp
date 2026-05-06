#ifndef _LIST_SEQUENCE_BUILDER_TPP_
#define _LIST_SEQUENCE_BUILDER_TPP_


template<typename T>
ListSequenceBuilder<T>::ListSequenceBuilder() : buffer(), buildImmutable(false) {}


template<typename T>
ListSequenceBuilder<T>& ListSequenceBuilder<T>::SetImmutable(bool val) {
    buildImmutable = val;
    return *this;
}

template<typename T>
ListSequenceBuilder<T>& ListSequenceBuilder<T>::Add(const T& item) {
    buffer.Append(item);
    return *this;
}

template<typename T>
ListSequenceBuilder<T>& ListSequenceBuilder<T>::AddToFront(const T& item) {
    buffer.Prepend(item);
    return *this;
}

template<typename T>
ListSequenceBuilder<T>& ListSequenceBuilder<T>::AddRange(const T* items, int count) {
    for (int i = 0; i < count; ++i) {
        buffer.Append(items[i]);
    }
    return *this;
}

template<typename T>
ListSequenceBuilder<T>& ListSequenceBuilder<T>::AddRange(const Sequence<T>* seq) {
    if (!seq) throw InvalidArgumentException("Null sequence in AddRange");
    for (int i = 0; i < seq->GetLength(); ++i) {
        buffer.Append(seq->Get(i));
    }
    return *this;
}

template<typename T>
ListSequenceBuilder<T>& ListSequenceBuilder<T>::Clear() {
    buffer = LinkedList<T>();
    return *this;
}

template<typename T>
Sequence<T>* ListSequenceBuilder<T>::Build() const {
    if (buildImmutable) {
        return new ImmutableListSequence<T>(buffer);
    } else {
        return new MutableListSequence<T>(buffer);
    }
}

template<typename T>
MutableListSequence<T>* ListSequenceBuilder<T>::BuildMutable() const {
    return new MutableListSequence<T>(buffer);
}

template<typename T>
ImmutableListSequence<T>* ListSequenceBuilder<T>::BuildImmutable() const {
    return new ImmutableListSequence<T>(buffer);
}


#endif /* _LIST_SEQUENCE_BUILDER_TPP_ */