#include <iostream>
#include "list_sequance.h"

int main() {
    int int_list[] = {1, 3, 5, 8};
    int count  = 4;
    ListSequence<int> list;



    LinkedList<int> list1;
    LinkedList<int> list2 = LinkedList<int>(int_list, count);
    list1.Append(2);
    LinkedList<int> *list3;
    list3 = list1.Concat(list2);
    LinkedList<int> *slist;
    slist = list3->GetSubList(1, 3);

    for (int i=0; i<list3->GetLength(); i++) std::cout << list3->Get(i) << std::endl;
    for (int i=0; i<slist->GetLength(); i++) std::cout << slist->Get(i) << std::endl;

    delete slist;
    delete list3;
}


