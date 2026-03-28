#include <iostream>
#include "linked_list.h"
#include "list_sequance.h"

int main() {
    int int_list[] = {1, 3, 5, 8};
    int count  = 4;
    LinkedList<int> list1;
    LinkedList<int> list2 = LinkedList<int>(int_list, count);
    try {
        std::cout << list1.GetFirst();
    } catch(const EmptyContainerException& e) {
        std::cout << e.what() << std::endl;
    }


}