#include "bit_sequence.h"

Bit::Bit(bool val) : value(val) {}

Bit::Bit(int val) : value(val != 0) {}

Bit& Bit::operator=(bool val) {
    value = val;
    return *this;
}

Bit& Bit::operator=(int val) {
    value = (val != 0);
    return *this;
}

Bit::operator bool() const {
    return value;
}

Bit Bit::operator~() const {
    return Bit(!value);
}

Bit Bit::operator&(const Bit& other) const {
    return Bit(value && other.value);
}

Bit Bit::operator|(const Bit& other) const {
    return Bit(value || other.value);
}

Bit Bit::operator^(const Bit& other) const {
    return Bit(value != other.value);
}

Bit& Bit::operator&=(const Bit& other) {
    value = value && other.value;
    return *this;
}

Bit& Bit::operator|=(const Bit& other) {
    value = value || other.value;
    return *this;
}

Bit& Bit::operator^=(const Bit& other) {
    value = value != other.value;
    return *this;
}

bool Bit::operator==(const Bit& other) const {
    return value == other.value;
}

bool Bit::operator!=(const Bit& other) const {
    return value != other.value;
}

BitSequence* BitSequence::applyBitwise(const BitSequence& other,
                                       Bit (Bit::*op)(const Bit&) const) const {
    if (GetLength() != other.GetLength()) {
        throw InvalidArgumentException("BitSequence lengths must match for bitwise operations");
    }
    BitSequence* result = new BitSequence();
    if (result == nullptr)
        throw MemoryAllocationException("Error during bit operation");
    for (int i = 0; i < GetLength(); ++i) {
        result->AppendImplict((Get(i).*op)(other.Get(i)));
    }
    return result;
}

BitSequence::BitSequence() : MutableArraySequence<Bit>() {}

BitSequence::BitSequence(const unsigned char* bytes, int bitCount) 
    : MutableArraySequence<Bit>() {
    if (bitCount < 0) 
        throw InvalidArgumentException("Negative bit count");
    if (bytes == nullptr && bitCount > 0)
        throw InvalidArgumentException("Null pointer with positive bit count");
    
    for (int bitIndex = 0; bitIndex < bitCount; ++bitIndex) {
        int byteIndex = bitIndex / 8;
        int bitOffset = bitIndex % 8;
        bool bitValue = (bytes[byteIndex] >> (7 - bitOffset)) & 1;
        AppendImplict(Bit(bitValue));
    }
}

BitSequence::BitSequence(const int* items, int count) : MutableArraySequence<Bit>() {
    if (count < 0) throw InvalidArgumentException("Negative count");
    for (int i = 0; i < count; ++i) {
        AppendImplict(Bit(items[i]));
    }
}

BitSequence::BitSequence(const bool* items, int count) : MutableArraySequence<Bit>() {
    if (count < 0) throw InvalidArgumentException("Negative count");
    for (int i = 0; i < count; ++i) {
        AppendImplict(Bit(items[i]));
    }
}

BitSequence::BitSequence(const Bit* items, int count) 
    : MutableArraySequence<Bit>(items, count) {}

BitSequence::BitSequence(int size) : MutableArraySequence<Bit>(size) {}

BitSequence::BitSequence(const DynamicArray<Bit>& arr) 
    : MutableArraySequence<Bit>(arr) {}

BitSequence::BitSequence(const BitSequence& other) 
    : MutableArraySequence<Bit>(other) {}

BitSequence::~BitSequence() {}

BitSequence* BitSequence::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
        throw IndexOutOfRangeException("Invalid subsequence indexes");
    
    DynamicArray<Bit> tmp_array(endIndex - startIndex + 1);
    int tmp_ind = 0;
    for (int i = startIndex; i <= endIndex; i++) {
        tmp_array.Set(tmp_ind, this->Get(i));
        tmp_ind++;
    }
    try {
        return new BitSequence(tmp_array);
    } catch (...) {
        throw MemoryAllocationException("Error while getting bit subsequence");
    }
}

BitSequence* BitSequence::operator~() const {
    BitSequence* result = new BitSequence();
    if (result == nullptr)
        throw MemoryAllocationException("Error during bit operation ~");
    for (int i = 0; i < GetLength(); ++i) {
        result->AppendImplict(~this->Get(i));
    }
    return result;
}

BitSequence* BitSequence::operator&(const BitSequence& other) const {
    return applyBitwise(other, &Bit::operator&);
}

BitSequence* BitSequence::operator|(const BitSequence& other) const {
    return applyBitwise(other, &Bit::operator|);
}

BitSequence* BitSequence::operator^(const BitSequence& other) const {
    return applyBitwise(other, &Bit::operator^);
}

bool BitSequence::GetBit(int index) const {
    return bool(this->Get(index));
}