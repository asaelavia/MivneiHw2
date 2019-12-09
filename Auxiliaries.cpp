//
// Created by Avia on 28/11/2019.
//

#include "Auxiliaries.h"
#include <iostream>


using namespace std;

template<typename T>
LinkedList<T>::LinkedList() {
    length = 0;
    head = NULL;
    tail = NULL;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node <T> *next = head;
    Node <T> *cur = NULL;
    while (next != NULL) {
        cur = next;
        next = next->next;
        delete cur;
    }
    std::cout << "LIST DELETED";
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
    node->next = NULL;
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
    this->head->prev = NULL;
    this->length--;
    delete (first);
}

template<typename T>
int LinkedList<T>::getListSize() const {
    return length;
}

template<typename T>
bool LinkedList<T>::isListEmpty() {
    return head == NULL;
}

template<typename T>
void LinkedList<T>::removeNode(Node <T> *node) {
    if (((node->prev) == NULL) && ((node->next) == NULL)) {
        this->head = NULL;
        this->tail = NULL;
        length--;
        delete (node);
        return;
    }
    if ((node->prev) == NULL) {
        this->head = node->next;
        length--;
        delete (node);
        return;
    }
    if ((node->next) == NULL) {
        this->tail = node->prev;
        this->tail->next = NULL;
        length--;
        delete (node);
        return;
    }
    node->prev->next = node->next;
    length--;
    delete (node);
}
