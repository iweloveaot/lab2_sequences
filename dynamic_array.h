#ifndef _DYNAMIC_ARRAY_H_
#define _DUNAMIC_ARRAY_H_

#include "exceptions.h"

template <typename T>
class DynamicArray {
private:

    T* data;
    int size;
    int capacity;

    void ensureCapacity(int newSize) {
        if (newSize <= capacity) 
            return;
        int newCap = capacity * 2;
        if (newCap < newSize) newCap = newSize;
        T* newData = new T[newCap];
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    DynamicArray(const T *items, int count) : size(count), capacity(count) {
        if (count < 0) throw InvalidArgumentException("Negative count");
        data = new T[capacity];
        for (int i = 0; i < count; i++)
            data[i] = items[i];
    }

    explicit DynamicArray(int size) : size(size), capacity(size) {
        if (size < 0) throw InvalidArgumentException("Negative size");
        data = new T[capacity];
        for (int i=0; i<size; i++)
            data[i] = T();
    }

    DynamicArray(const DynamicArray<T>& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (int i=0; i<size; i++)
            data[i] = other.data[i];
    }

    ~DynamicArray() {
        delete[] data;
    }

    const T& Get(int index) const {
        if (index < 0 || index >= size)
            throw IndexOutOfRangeException("Index out of range in DynamicArray::Get");
        return data[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= size)
            throw IndexOutOfRangeException("Index out of range in DynamicArray::Set");
        data[index] = value;
    }

    int GetSize() const { 
        return size; 
    }

    void Resize(int newSize) {
        if (newSize < 0) 
            throw InvalidArgumentException("Negative new size");
        if (newSize == size)    
            return;
        ensureCapacity(newSize);
        if (newSize < size) {
            T *newData = new T[capacity];
            for (int i = 0; i < newSize; i++)
                newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        if (newSize > size) {
            for (int i=size; i<newSize; i++)
                data[i] = T();
        }
        size = newSize;
    }

    DynamicArray<T>& operator=(const DynamicArray<T> &other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
};

#endif // _DYNAMIC_ARRAY_H_