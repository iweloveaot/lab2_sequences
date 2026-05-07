#ifndef _BIT_SEQUENCE_H_
#define _BIT_SEQUENCE_H_

#include "mutable_array_sequence.h"
#include "exceptions.h"

class Bit {
private:
    bool value;

public:
    Bit(bool val = false);
    Bit(int val);

    Bit& operator=(bool val);
    Bit& operator=(int val);

    operator bool() const;

    Bit operator~() const;
    Bit operator&(const Bit& other) const;
    Bit operator|(const Bit& other) const;
    Bit operator^(const Bit& other) const;

    Bit& operator&=(const Bit& other);
    Bit& operator|=(const Bit& other);
    Bit& operator^=(const Bit& other);

    bool operator==(const Bit& other) const;
    bool operator!=(const Bit& other) const;
};

class BitSequence : public MutableArraySequence<Bit> {
private:
    BitSequence* applyBitwise(const BitSequence& other,
                              Bit (Bit::*op)(const Bit&) const) const;

public:
    BitSequence();
    BitSequence(const unsigned char* bytes, int bitCount);
    BitSequence(const int* items, int count);
    BitSequence(const bool* items, int count);
    BitSequence(const Bit* items, int count);
    explicit BitSequence(int size);
    BitSequence(const DynamicArray<Bit>& arr);
    BitSequence(const BitSequence& other);

    ~BitSequence() override;

    BitSequence* GetSubsequence(int startIndex, int endIndex) const;

    BitSequence* operator~() const;
    BitSequence* operator&(const BitSequence& other) const;
    BitSequence* operator|(const BitSequence& other) const;
    BitSequence* operator^(const BitSequence& other) const;

    bool GetBit(int index) const;
};

#endif // _BIT_SEQUENCE_H_