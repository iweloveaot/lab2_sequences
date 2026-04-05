#include <iostream>
#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"
#include "mutable_list_sequence.h"
#include "immutable_list_sequence.h"

int add(const int &el, const int &n) {
    return el + n;
}

int main() {

    int items[] = {1, 2, 3, 4, 5 , 6, 7};
    MutableArraySequence<int> arr1 = MutableArraySequence<int>(items, 7);
    ImmutableArraySequence<int> arr2 = ImmutableArraySequence<int>(items, 7);
    int add1;
    arr1.Reduce(*add, 3, &add1);
    int add2;
    arr2.Reduce(*add, 4, &add2);
    std::cout << add1 << " ";
    std::cout << add2 << " ";

    MutableListSequence<int> list1 = MutableListSequence<int>(items, 7);
    ImmutableListSequence<int> list2 = ImmutableListSequence<int>(items, 7);
    int add11;
    list1.Reduce(*add, 5, &add11);
    int add22;
    list2.Reduce(*add, 6, &add22);
    std::cout << add11 << " ";
    std::cout << add22 << " ";

}    
