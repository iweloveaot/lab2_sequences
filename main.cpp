#include <iostream>
#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"

int main() {
    int items[] = {1, 3, 5, 6, 7};
    MutableArraySequence<int> arr = MutableArraySequence<int>(items, 5);
    MutableArraySequence<int> arr1;
    arr1.Prepend(2);
    arr1.Append(9);
    arr1.InsertAt(11, 1);
    arr.Concat(&arr1);
    for (int i=0; i<arr.GetLength(); i++) std::cout << arr.Get(i) << " ";
}


