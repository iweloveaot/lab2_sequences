#include <iostream>
#include "mutable_array_sequence.h"
#include "mutable_list_sequence.h"
#include "option.h"

bool isEven(const int &el) {
    return (el % 2 == 0);
}

int main() {

    int items[] = {1, 3, 5, 7};
    MutableListSequence<int> arr1 = MutableListSequence<int>(items, 4);
    IEnumerator<int> *iter = arr1.GetEnumerator();
    while (iter->HasNext()) {
        std::cout << iter->GetCurrent() << " ";
    }
    delete iter; 
}    
