//
// Created by Avia on 28/11/2019.
//

#ifndef HW2_AUXILIARIES_H
#define HW2_AUXILIARIES_H

#include <iostream>

using namespace std;
template<typename T>
class Node {
public:
    Node *next;
    Node *prev;
    T data;
};

template<typename T>
class LinkedList {
    int length;
public:
    Node<T> *head;
    Node<T> *tail;

    LinkedList<T>();

    ~LinkedList<T>();

    void add(T data);

    T getFirst();

    void removeFirst();

    void removeNode(Node<T> *node);

    int getListSize() const;

    bool isListEmpty();

};



template<typename T>
LinkedList<T>::LinkedList() {
    length = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node <T> *next = head;
    Node <T> *cur = nullptr;
    while (next != nullptr) {
        cur = next;
        next = next->next;
        delete cur;
    }
}

template<typename T>
void LinkedList<T>::add(T data) {
    Node <T> *node = new Node<T>();
    if (getListSize() == 0) {
        this->head = node;
    } else {
        this->tail->next = node;
        node->prev = this->tail;
    }
    node->data = data;
    node->next = nullptr;
    this->tail = node;
    this->length++;
}

template<typename T>
T LinkedList<T>::getFirst() {
    return this->head->data;
}

template<typename T>
void LinkedList<T>::removeFirst() {
    Node <T> *first = this->head;
    this->head = this->head->next;
    this->head->prev = nullptr;
    this->length--;
    delete (first);
}

template<typename T>
int LinkedList<T>::getListSize() const {
    return length;
}

template<typename T>
bool LinkedList<T>::isListEmpty() {
    return head == nullptr;
}

template<typename T>
void LinkedList<T>::removeNode(Node <T> *node) {
    if (((node->prev) == nullptr) && ((node->next) == nullptr)) {
        this->head = nullptr;
        this->tail = nullptr;
        length--;
        delete (node);
        return;
    }
    if ((node->prev) == nullptr) {
        this->head = node->next;
        length--;
        delete (node);
        return;
    }
    if ((node->next) == nullptr) {
        this->tail = node->prev;
        this->tail->next = nullptr;
        length--;
        delete (node);
        return;
    }
    node->prev->next = node->next;
    length--;
    delete (node);
}


#endif //HW2_AUXILIARIES_H
