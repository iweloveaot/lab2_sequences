#ifndef _ARRAY_SEQUANCE_H_
#define _ARRAY_SEQUANCE_H_

#include "exceptions.h"
#include "dynamic_array.h"
#include "sequance.h"

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> array; 

protected:
    virtual Sequence<T>* CreateSequence(const DynamicArray<T> &arr) const = 0;
    virtual Sequence<T>* Instance() = 0;
    virtual Sequence<T>* AppendImplict(const T &item) override {
        int size = array.GetSize();
        array.Resize(size+1);
        array.Set(size, item);
        return this;
    };

    virtual Sequence<T>* PrependImplict(const T &item) override {  // переписать без препенда
        int size = array.GetSize();
        DynamicArray<T> tmp_arr = DynamicArray<T>(size+1);
        for (int i = 1; i <= array.GetSize(); i++) {
            tmp_arr.Set(i, array.Get(i-1));
        }
        tmp_arr.Set(0, item);
        array = tmp_arr;
        return this;
    }

    virtual Sequence<T>* InsertAtImplict(const T &item, int index) override { 
        if (index < 0 || index > array.GetSize())
            throw IndexOutOfRangeException("Index out of range in Sequence::InsertAt");
        
        if (index == array.GetSize())
            AppendImplict(item);
        else if (index == 0)
            PrependImplict(item);
        else {
            DynamicArray<T> tmp_arr = DynamicArray<T>(array.GetSize()+1);
            for (int i = 0; i < index; i++)
                tmp_arr.Set(i, array.Get(i));
            tmp_arr.Set(index, item);
            for (int i = index; i < array.GetSize(); i++)
                tmp_arr.Set(i+1, array.Get(i));
            array = tmp_arr;
        }
        return this;
    }

    virtual Sequence<T>* ConcatImplict(const Sequence<T>* other) override {  
        for (int i = 0; i < other->GetLength(); i++) {
            AppendImplict(other->Get(i));
        }
        return this;
    }

public:
    ArraySequence() : array(DynamicArray<T>()) {}
    ArraySequence(const T* items, int count) : array(DynamicArray<T>(items, count)) {}
    explicit ArraySequence(int size) : array(DynamicArray<T>(size)) {}
    ArraySequence(const DynamicArray<T> &arr) : array(DynamicArray<T>(arr)) {}
    ArraySequence(const ArraySequence<T> &other) : array(DynamicArray<T>(other.array)) {}
    ~ArraySequence() override {}

    const T& GetFirst() const override {
        if (array.GetSize() == 0)
            throw EmptyContainerException("Array sequence is empty");
        return array.Get(0);
    }

    const T& GetLast() const override {
        if (array.GetSize() == 0)
            throw EmptyContainerException("Array sequence is empty");
        return array.Get(array.GetSize()-1);
    }

    const T& Get(int index) const override {
        return array.Get(index);
    }

    int GetLength() const override {
        return array.GetSize();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override 
    {
        if (startIndex < 0 || endIndex >= array.GetSize() || startIndex > endIndex)
            throw IndexOutOfRangeException("Invalid subsequence indexes");
        DynamicArray<T> tmp_array;
        int tmp_ind = 0;
        for (int i = startIndex; i <= endIndex; i++) {
            tmp_array.Set(tmp_ind, array.Get(i));
            tmp_ind++;
        }
        Sequence<T>* sub_seq = CreateSequence(tmp_array);
        return sub_seq;
    }
    
    const T& operator[](int index) const override {
        return array.Get(index);
    }

    // Sequence<T>* Map(T (*func)(T)) const override {
    //     LinkedList<T> newList;
    //     int sz = list->GetLength();
    //     for (int i = 0; i < sz; ++i)
    //         newList.Append(func(list->Get(i)));
    //     ListSequenceBase<T>* result = Clone();
    //     delete result->list;
    //     result->list = new LinkedList<T>(newList);
    //     return result;
    // }

    // Sequence<T>* Where(bool (*pred)(T)) const override {
    //     LinkedList<T> filtered;
    //     int sz = list->GetLength();
    //     for (int i = 0; i < sz; ++i) {
    //         T val = list->Get(i);
    //         if (pred(val))
    //             filtered.Append(val);
    //     }
    //     ListSequenceBase<T>* result = Clone();
    //     delete result->list;
    //     result->list = new LinkedList<T>(filtered);
    //     return result;
    // }

    // T Reduce(T (*func)(T, T), T init) const override {
    //     int sz = list->GetLength();
    //     T acc = init;
    //     for (int i = 0; i < sz; ++i)
    //         acc = func(acc, list->Get(i));
    //     return acc;
    // }

    // Option<T> FindFirst(bool (*pred)(T)) const override {
    //     int sz = list->GetLength();
    //     for (int i = 0; i < sz; ++i) {
    //         T val = list->Get(i);
    //         if (!pred || pred(val))
    //             return Option<T>(val);
    //     }
    //     return Option<T>();
    // }

    // Option<T> FindLast(bool (*pred)(T)) const override {
    //     int sz = list->GetLength();
    //     for (int i = sz - 1; i >= 0; --i) {
    //         T val = list->Get(i);
    //         if (!pred || pred(val))
    //             return Option<T>(val);
    //     }
    //     return Option<T>();
    // }
};

#endif /* _LIST_SEQUANCE_H_ */