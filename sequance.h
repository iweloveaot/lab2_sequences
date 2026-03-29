#ifndef _SEQUANCE_H_
#define _SEQUANCE_H_

template <typename T>
class Sequence {
protected:
    virtual Sequence<T>* Instance() const = 0;
    virtual Sequence<T>* AppendImplict(const T &item) = 0;
    virtual Sequence<T>* PrependImplict(const T &item) = 0;
    virtual Sequence<T>* InsertAtImplict(const T &item, int index) = 0;
    
public:
    virtual const T& GetFirst() const = 0;
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* Concat(const Sequence<T>* other) const = 0;
    virtual const T& operator[](int index) const = 0;

    virtual Sequence<T>* Append(const T &item) {
        return Instance()->AppendImplict(item);
    }

    virtual Sequence<T>* Prepend(const T &item) {
        return Instance()->PrependImplict(item);
    }

    virtual Sequence<T>* InsertAt(const T &item, int index) {
        return Instance()->InsertAtImplict(item, index);
    }


    // Map-Reduce
    // virtual Sequence<T>* Map(T (*func)(T)) const = 0;
    // virtual Sequence<T>* Where(bool (*pred)(T)) const = 0;
    // virtual T Reduce(T (*func)(T, T), T init) const = 0;
    // virtual Option<T> FindFirst(bool (*pred)(T) = nullptr) const = 0;
    // virtual Option<T> FindLast(bool (*pred)(T) = nullptr) const = 0;

    virtual ~Sequence() {}
};

#endif /* _SEQUANCE_H_ */