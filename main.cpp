#include <iostream>
#include "mutable_array_sequence.h"
#include "option.h"

bool isEven(const int &el) {
    return (el % 2 == 0);
}

int main() {

    MutableArraySequence<int> arr1;
    Option<int> res1 = arr1.TryGetFirst(*isEven);
    if (res1.HasValue()) std::cout << res1.GetValue() << " ";
    else std::cout << "None" << " ";
    
    arr1.Append(1);
    arr1.Append(3);
    arr1.Append(5);

    Option<int> res2 = arr1.TryGetLast(*isEven);
    if (res2.HasValue()) std::cout << res2.GetValue() << " ";
    else std::cout << "None" << " ";

}    
