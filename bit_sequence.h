#ifndef _BIT_SEQUENCE_H_
#define _BIT_SEQUENCE_H_

#include "sequence.h"
#include "dynamic_array.h"
#include "exceptions.h"

// ===== Класс Bit =====
class Bit {
private:
    bool value;
    
public:
    Bit(bool val = false) : value(val) {}
    
    Bit& operator=(bool val) {
        value = val;
        return *this;
    }
    
    operator bool() const { 
        return value; 
    }
    
    Bit operator~() const { 
        return Bit(!value); 
    }
    
    Bit operator&(const Bit& other) const {
        return Bit(value && other.value); 
    }

    Bit operator|(const Bit& other) const { 
        return Bit(value || other.value); 
    }

    Bit operator^(const Bit& other) const {
        return Bit(value != other.value); 
    }
    
    Bit& operator&=(const Bit& other) {
        value = value && other.value; 
        return *this; 
    }

    Bit& operator|=(const Bit& other) {
        value = value || other.value; 
        return *this; 
    }

    Bit& operator^=(const Bit& other) { 
        value = value != other.value; 
        return *this; 
    }
    
    bool operator==(const Bit& other) const {
        return value == other.value; 
    }

    bool operator!=(const Bit& other) const {
        return value != other.value; 
    }
};


class BitSequence : public Sequence<Bit> {
private:
    DynamicArray<Bit> bits;
    

    BitSequence* applyBitwise(const BitSequence& other, 
                            Bit (Bit::*op)(const Bit&) const) const {
        if (GetLength() != other.GetLength()) {
            throw InvalidArgumentException("BitSequence lengths must match for bitwise operations");
        }
        
        BitSequence* result = new BitSequence();
        for (int i = 0; i < GetLength(); ++i) {
            result->AppendImplict((Get(i).*op)(other.Get(i)));
        }
        return result;
    }

protected:
    
    virtual Sequence<Bit>* Instance() override {
        return this;
    }
    
    virtual Sequence<Bit>* AppendImplict(const Bit& item) override {
        int size = bits.GetSize();
        bits.Resize(size+1);
        bits.Set(size, item);
        return this;
    }
    
    virtual Sequence<Bit>* PrependImplict(const Bit& item) override {
        DynamicArray<Bit> newArr(bits.GetSize() + 1);
        newArr.Set(0, item);
        for (int i = 0; i < bits.GetSize(); ++i) {
            newArr.Set(i + 1, bits.Get(i));
        }
        bits = newArr;
        return this;
    }
    
    virtual Sequence<Bit>* InsertAtImplict(const Bit& item, int index) override {
        if (index < 0 || index > bits.GetSize())
            throw IndexOutOfRangeException("Index out of range in BitSequence::InsertAt");
        
        if (index == bits.GetSize()) {
            return AppendImplict(item);
        }
        if (index == 0) {
            return PrependImplict(item);
        }
        
        DynamicArray<Bit> newArr(bits.GetSize() + 1);
        for (int i = 0; i < index; ++i)
            newArr.Set(i, bits.Get(i));
        newArr.Set(index, item);
        for (int i = index; i < bits.GetSize(); ++i)
            newArr.Set(i + 1, bits.Get(i));
        bits = newArr;
        return this;
    }
    
    virtual Sequence<Bit>* ConcatImplict(const Sequence<Bit>* other) override {
        if (!other) throw InvalidArgumentException("Null sequence in Concat");
        for (int i = 0; i < other->GetLength(); ++i) {
            AppendImplict(other->Get(i));
        }
        return this;
    }
    
public:
    BitSequence() : bits() {}
    
    BitSequence(const bool* items, int count) : bits() {
        if (count < 0) throw InvalidArgumentException("Negative count");
        for (int i = 0; i < count; ++i) {
            AppendImplict(Bit(items[i]));
        }
    }
    BitSequence(const Bit* items, int count) : bits(items, count) {}
    explicit BitSequence(int size) : bits(size) {}
    BitSequence(const DynamicArray<Bit>& arr) : bits(arr) {}
    BitSequence(const BitSequence& other) : bits(other.bits) {}
    ~BitSequence() override {};
    
    const Bit& GetFirst() const override {
        if (bits.GetSize() == 0)
            throw EmptyContainerException("BitSequence is empty");
        return bits.Get(0);
    }
    
    const Bit& GetLast() const override {
        if (bits.GetSize() == 0)
            throw EmptyContainerException("BitSequence is empty");
        return bits.Get(bits.GetSize() - 1);
    }
    
    const Bit& Get(int index) const override {
        return bits.Get(index);
    }
    
    Sequence<Bit>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= bits.GetSize() || startIndex > endIndex)
            throw IndexOutOfRangeException("Invalid subsequence indexes");
        DynamicArray<Bit> tmp_array;
        int tmp_ind = 0;
        for (int i = startIndex; i <= endIndex; i++) {
            tmp_array.Set(tmp_ind, bits.Get(i));
            tmp_ind++;
        }
        return new BitSequence(tmp_array);
    }
    
    int GetLength() const override {
        return bits.GetSize();
    }
    
    BitSequence* operator~() const {
        BitSequence* result = new BitSequence();
        for (int i = 0; i < bits.GetSize(); ++i) {
            result->AppendImplict(~bits.Get(i));
        }
        return result;
    }
    
    BitSequence* operator&(const BitSequence& other) const {
        return applyBitwise(other, &Bit::operator&);
    }
    
    BitSequence* operator|(const BitSequence& other) const {
        return applyBitwise(other, &Bit::operator|);
    }
    
    BitSequence* operator^(const BitSequence& other) const {
        return applyBitwise(other, &Bit::operator^);
    }
    
    
    BitSequence& operator&=(const BitSequence& other) {
        if (GetLength() != other.GetLength())
            throw InvalidArgumentException("BitSequence lengths must match for &= operator");
        for (int i = 0; i < bits.GetSize(); ++i) {
            bits.Set(i, bits.Get(i) & other.Get(i));
        }
        return *this;
    }
    
    BitSequence& operator|=(const BitSequence& other) {
        if (GetLength() != other.GetLength())
            throw InvalidArgumentException("BitSequence lengths must match for |= operator");
        for (int i = 0; i < bits.GetSize(); ++i) {
            bits.Set(i, bits.Get(i) | other.Get(i));
        }
        return *this;
    }
    
    BitSequence& operator^=(const BitSequence& other) {
        if (GetLength() != other.GetLength())
            throw InvalidArgumentException("BitSequence lengths must match for ^= operator");
        for (int i = 0; i < bits.GetSize(); ++i) {
            bits.Set(i, bits.Get(i) ^ other.Get(i));
        }
        return *this;
    }
    
    void SetBit(int index, bool value) {
        if (index < 0 || index >= bits.GetSize())
            throw IndexOutOfRangeException("Index out of range in BitSequence::SetBit");
        bits.Set(index, Bit(value));
    }
    
    bool GetBit(int index) const {
        return bool(Get(index));
    }
};

#endif /* _BIT_SEQUENCE_H_ */