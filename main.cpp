#include <iostream>
#include "mutable_list_sequence.h"
#include "option.h"

bool isNotEven(const int &el) {
    return (el % 2 != 0);
}

int half(const int &el) {
    return el/2;
}

int main() {

    int items[] = {1, 3, 5, 7};
    MutableListSequence<int> arr1 = MutableListSequence<int>(items, 4);
    Option<int> opt = arr1.TryGetFirst(*isNotEven);
    if (opt.HasValue()) std::cout << opt.GetValue();

}    
