#include <iostream>
#include "bit_sequence.h"

int main() {
    bool items[] = {true, false, true, true, true, false};
    bool itemsforbits[] = {true, true, true, false};
    Bit biits[4];
    for (int i=0; i<4; i++) {
        biits[i] = Bit(itemsforbits[i]);
    }
    DynamicArray<Bit> arr = DynamicArray<Bit>(biits, 4);
    BitSequence bits1 = BitSequence(items, 6);
    BitSequence bits2 = BitSequence(biits, 4);
    BitSequence bits3 = BitSequence();
    BitSequence bits4 = BitSequence(7);
    BitSequence bits5 = BitSequence(arr);
    BitSequence bits6 = BitSequence(bits4);
    std::cout << bits1.GetLength() << " " << bits2.GetLength() << " " << bits3.GetLength() << " " << bits4.GetLength() << " " << bits5.GetLength() << " " << bits6.GetLength();
}


