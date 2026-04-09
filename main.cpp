#include <iostream>
#include "bit_sequence.h"
#include "option.h"

bool isNotEven(const int &el) {
    return (el % 2 != 0);
}

int half(const int &el) {
    return el/2;
}

int main() {

    bool items[] = {1, 0, 0, 0, 1};
    bool items2[] = {1, 1, 0, 0, 1};
    
    BitSequence seq1 = BitSequence(items, 5);
    BitSequence seq2 = BitSequence(items2, 5);
    std::cout << seq2.GetBit(1) << std::endl;
    BitSequence *seq1n = ~seq1;
    BitSequence *seq1a = seq1&seq2;
    BitSequence *seq1o = seq1|seq2;
    BitSequence *seq1xo = seq1^seq2;

    for (int i=0; i<5; i++) {
        std::cout << seq1n->GetBit(i) << " " << seq1a->GetBit(i) << " " << seq1o->GetBit(i) << " " << seq1xo->GetBit(i) << std::endl;
    }

    delete seq1n;
    delete seq1a;
    delete seq1o;
    delete seq1xo;
}    
