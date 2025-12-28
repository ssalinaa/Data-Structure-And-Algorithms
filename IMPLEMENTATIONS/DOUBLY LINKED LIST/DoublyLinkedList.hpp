#pragma once
#include <iostream>

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList(DoublyLinkedList<T>&& other);
    
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other);
    ~DoublyLinkedList();

    void pushBack(const T& element);
    void pushFront(const T& element);
    void popBack();
    void popFront();

    const T& front() const;
    const T& back() const;
    T& front();
    T& back();

    size_t getSize() const;
    bool isEmpty() const;
    void clear();

private:
    struct Node {
        T data;
        Node* next;
        Node* previous;
        
        Node(const T& data) : data(data), next(nullptr), previous(nullptr) { }
    };
    
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t count = 0;

    void copyFrom(const DoublyLinkedList& other);
    void moveFrom(DoublyLinkedList&& other);
    void free();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) { }

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr) {
    copyFrom(other);
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) {
    moveFrom(std::move(other));

}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other) {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    free();
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& element) {
    Node* toAdd = new Node(element);
    if(isEmpty()) {
        head = tail = toAdd;
    } else {
        tail->next = toAdd;
        toAdd->previous = tail;
        tail = toAdd;
    }
    count++;
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T& element) {
    Node* toAdd = new Node(element);
    if(isEmpty()) {
        head = tail = toAdd;
    } else {
        head->previous = toAdd;
        toAdd->next = head;
        head = toAdd;
    }
    count++;
}

template <typename T>
void DoublyLinkedList<T>::popBack() {
    if(isEmpty()) {
       throw std::logic_error("Empty list!");
    }
    if(head == tail) {
        delete head;
        head = tail = nullptr;
        count = 0;
        return;
    } else {   
        Node* toBeDeleted = tail;
        tail = tail->previous;
        tail->next = nullptr;
        delete toBeDeleted;
    }
    count--;
}

template <typename T>
void DoublyLinkedList<T>::popFront() {
    if(isEmpty()) {
       throw std::logic_error("Empty list!");
    }
    if(head == tail) {
        delete head;
        head = tail = nullptr;
        count = 0;
        return;
    } else {   
        Node* toBeDeleted = head;
        head = head->next;
        head->previous = nullptr;
        delete toBeDeleted;
    }
    count--;
}

template <typename T>
const T& DoublyLinkedList<T>::front() const {
    if(isEmpty()) {
       throw std::logic_error("Empty list!");
    }
    return head->data;
}

template <typename T>
const T& DoublyLinkedList<T>::back() const {
    if(isEmpty()) {
       throw std::logic_error("Empty list!");
    }
    return tail->data;
}

template <typename T>
T& DoublyLinkedList<T>::front() {
    if(isEmpty()) {
       throw std::logic_error("Empty list!");
    }
    return head->data;
}

template <typename T>
T& DoublyLinkedList<T>::back() {
    if(isEmpty()) {
       throw std::logic_error("Empty list!");
    }
    return tail->data;
}

template <typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return count;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    free();
}

template <typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other) {
    Node* current = other.head;
    while(current) {
        pushBack(current->data);
        current = current->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList<T>&& other) {
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = other.tail = nullptr;
    other.count = 0;
}

template <typename T>
void DoublyLinkedList<T>::free() {
    Node* current = head;
    while(current) {
        Node* toBeDeleted = current;
        current = current->next;
        delete toBeDeleted;
    }
    head = tail = nullptr;
    count = 0;
}