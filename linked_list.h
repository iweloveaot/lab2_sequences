#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <iostream>
#include "exceptions.h"

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;
        Node(const T &val, Node *n = nullptr) : data(val), next(n) {}
    };

    Node *first;
    Node *last;
    int length;

public:
    LinkedList() : first(nullptr), last(nullptr), length(0) {}

    LinkedList(const T *items, int count) : first(nullptr), last(nullptr), length(0) {
        if (count < 0)
            throw InvalidArgumentException("Negative count");
        for (int i = 0; i < count; i++) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &other) : first(nullptr), last(nullptr), length(0) {
        Node *current = other.first; 
        while (current) {
            Append(current->data);            
            current = current->next;
        }
    }

    ~LinkedList() {
        while (first) {
            Node *tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    const T& GetFirst() const {
        if (length == 0) 
            throw EmptyContainerException("List is empty");
        return first->data;
    }

    const T& GetLast() const {
        if (length == 0) 
            throw EmptyContainerException("List is empty");
        return last->data;
    }

    const T& Get(int index) const { 
        if (index < 0 || index >= length)
            throw IndexOutOFRangeException("Index out of range in LinkedList::Get");
        Node *current = first;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex)
            throw IndexOutOFRangeException("Invalid sublist indexes");
        LinkedList<T> *sub_list = new LinkedList<T>();
        Node *cur = first;
        for (int i = 0; i < startIndex; i++)
            cur = cur->next;
        for (int i = startIndex; i <= endIndex; i++) {
            sub_list->Append(cur->data);
            cur = cur->next;
        }
        return sub_list;
    }

    int GetLength() const { 
        return length;
    }

    void Append(const T &item) {
        Node *newNode = new Node(item, nullptr);
        if (first) 
            last->next = newNode;
        else
            first = newNode;
        last = newNode;
        length++;
    }

    void Prepend(const T &item) {
        Node *newNode = new Node(item, nullptr);
        if (first) 
            newNode->next = first;
        else 
            last = newNode;
        first = newNode;
        length++;
    }

    void InsertAt(const T &item, int index) {
        if (index < 0 || index > length)
            throw IndexOutOFRangeException("Index out of range in LinkedList::InsertAt");
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == length) {
            Append(item);
            return;
        }
        Node* current = first;
        for (int i = 0; i < index-1; i++)
            current = current->next;
        Node* newNode = new Node(item, current->next);
        current->next = newNode;
        length++;
    }

    LinkedList<T>* Concat(const LinkedList<T> &other) const {
        LinkedList<T> *result = new LinkedList<T>(); 
        *result = *this;
        Node* cur = other.first;
        while (cur) {
            result->Append(cur->data);
            cur = cur->next;
        }
        return result;
    }

    LinkedList<T>& operator=(const LinkedList<T> &other) {
        if (this != &other) {
            while (first) {
                Node* tmp = first;
                first = first->next;
                delete tmp;
            }
            first = last = nullptr;
            length = 0;
            Node *current = other.first; 
            while (current) {
                Append(current->data);            
                current = current->next;
            } 
        }
        return *this;
    }
};

#endif // _LINKED_LIST_H_