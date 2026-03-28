#ifndef _SEQUANCE_H_
#define _SEQUANCE_H_

template <typename T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    // Mutable operations (for mutable sequences)
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) = 0;

    // Immutable operations (return new sequence)
    virtual Sequence<T>* AppendImmutable(T item) const = 0;
    virtual Sequence<T>* PrependImmutable(T item) const = 0;
    virtual Sequence<T>* InsertAtImmutable(T item, int index) const = 0;
    virtual Sequence<T>* ConcatImmutable(const Sequence<T>* other) const = 0;

    // Map-Reduce
    virtual Sequence<T>* Map(T (*func)(T)) const = 0;
    virtual Sequence<T>* Where(bool (*pred)(T)) const = 0;
    virtual T Reduce(T (*func)(T, T), T init) const = 0;
    // virtual Option<T> FindFirst(bool (*pred)(T) = nullptr) const = 0;
    // virtual Option<T> FindLast(bool (*pred)(T) = nullptr) const = 0;

    // Indexed access via operator[]
    virtual T operator[](int index) const = 0;

    virtual ~Sequence() {}
};

#endif /* _SEQUANCE_H_ */