#ifndef _ARRAY_SEQUENCE_BUILDER_TPP_
#define _ARRAY_SEQUENCE_BUILDER_TPP_


template<typename T>
ArraySequenceBuilder<T>::ArraySequenceBuilder() : buffer(), buildImmutable(false) {}

template<typename T>
ArraySequenceBuilder<T>& ArraySequenceBuilder<T>::SetImmutable(bool val) {
    buildImmutable = val;
    return *this;
}

template<typename T>
ArraySequenceBuilder<T>& ArraySequenceBuilder<T>::Add(const T& item) {
    int size = buffer.GetSize();
    buffer.Resize(size + 1);
    buffer.Set(size, item);
    return *this;
}

template<typename T>
ArraySequenceBuilder<T>& ArraySequenceBuilder<T>::AddRange(const T* items, int count) {
    for (int i = 0; i < count; ++i) {
        Add(items[i]);
    }
    return *this;
}

template<typename T>
ArraySequenceBuilder<T>& ArraySequenceBuilder<T>::AddRange(const Sequence<T>* seq) {
    if (!seq) throw InvalidArgumentException("Null sequence in AddRange");
    for (int i = 0; i < seq->GetLength(); ++i) {
        Add(seq->Get(i));
    }
    return *this;
}

template<typename T>
ArraySequenceBuilder<T>& ArraySequenceBuilder<T>::Clear() {
    buffer = DynamicArray<T>();
    return *this;
}

template<typename T>
Sequence<T>* ArraySequenceBuilder<T>::Build() const {
    if (buildImmutable) {
        return new ImmutableArraySequence<T>(buffer);
    } else {
        return new MutableArraySequence<T>(buffer);
    }
}

template<typename T>
MutableArraySequence<T>* ArraySequenceBuilder<T>::BuildMutable() const {
    return new MutableArraySequence<T>(buffer);
}

template<typename T>
ImmutableArraySequence<T>* ArraySequenceBuilder<T>::BuildImmutable() const {
    return new ImmutableArraySequence<T>(buffer);
}

#endif /* _ARRAY_SEQUENCE_BUILDER_TPP_ */