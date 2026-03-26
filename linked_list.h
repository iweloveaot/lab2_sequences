#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val, Node* n = nullptr) : data(val), next(n) {}
    };

    Node* first;
    Node* last;
    int length;

public:
    LinkedList() : first(nullptr), last(nullptr), length(0) {}

    LinkedList(T* items, int count) : first(nullptr), last(nullptr), length(0) {
        for (int i=0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& other) : first(nullptr), last(nullptr), length(0) { // проверка на пустоту
        Node *current = other->first; 
        while (current) {
            Append(current->data);            
            current = current->next;
        }
    }

    ~LinkedList() {
        while (first) {
            Node* tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    T GetFirst() const { // IndexOutOfRange (если список пуст) 
        if (length == 0) 
            throw EmptyContainer("List is empty");
        return first->data;
    }

    T GetLast() const { // IndexOutOfRange (если список пуст) 
        if (length == 0) 
            throw EmptyContainer("List is empty");
        return last->data;
    }

    T Get(int index) const { // IndexOutOfRange (если индекс отрицательный или больше/равен числу элементов) 
        if (index < 0 || index >= length)
            throw IndexOutOfRange("Index out of range in LinkedList::Get");
        Node* current = first;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
            throw IndexOutOfRange("Invalid sublist indices");
        LinkedList<T> sub;
        Node* cur = head;
        for (int i=0; i<startIndex; i++)
            cur = cur->next;
        for (int i=startIndex; i<=endIndex; i++) {
            sub.Append(cur->data);
            cur = cur->next;
        }
        return &sub;
    }

    int GetLength() const { 
        return length;
    }

    void Append(T item) {
        Node *newNode = new Node(item, nullptr);
        if (first) 
            last->next = newNode;
        else 
            first = newNode;
        last = newNode;
        length++;
    }

    void Prepend(T item) {
        Node* newNode = new Node(item, nullptr);
        if (first) 
            newNode->next = first;
        else 
            last = newNode;
        first = newNode;
        length++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > length)
            throw IndexOutOfRange("Index out of range in LinkedList::InsertAt");
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == length) {
            Append(item);
            return;
        }
        Node* current = first;
        for (int i=0; i<index-1; i++)
            current = current->next;
        Node* newNode = new Node(item, current->next);
        current->next = newNode;
        length++;
    }

    LinkedList<T>* Concat(const LinkedList<T>& other) const {
        LinkedList<T> result = this;
        Node* current = other->head;
        while (current) {
            result->Append(current->data);
            current = current->next;
        }
        return result;
    }

    // LinkedList<T>& operator=(const LinkedList<T>& other) {
    //     if (this != &other) {
    //         while (head) {
    //             Node* tmp = head;
    //             head = head->next;
    //             delete tmp;
    //         }
    //         head = tail = nullptr;
    //         length = 0;
    //         copyFrom(other);
    //     }
    //     return *this;
    // }
};

#endif // _LINKED_LIST_H_