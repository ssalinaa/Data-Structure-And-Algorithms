#pragma once
#include <iostream>

template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;
    SinglyLinkedList(const SinglyLinkedList<T>& other);
    SinglyLinkedList(SinglyLinkedList<T>&& other);
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
    SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other);
    ~SinglyLinkedList();

    void pushFront(const T& element);
    void pushBack(const T& element);

    void popFront();

    const T& front() const;
    const T& back() const;

    T& front();
    T&back();

    size_t getSize() const;
    bool isEmpty() const;

    template <typename U>
    friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

    void print() const;
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& data) {
            this->data = data;
            next = nullptr;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

    void copyFrom(const SinglyLinkedList<T>& other);
    void moveFrom(SinglyLinkedList<T>&& other);
    void free();
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
    copyFrom(other);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) {
    moveFrom(std::move(other));
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    free();
}

template <typename T>
void SinglyLinkedList<T>::pushFront(const T& element) {
    Node* toAdd = new Node(element);
    if(isEmpty()) {
        head = tail = toAdd;
    } else {
        toAdd->next = head;
        head = toAdd;
    }
    size++;
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T& element) {
    Node* toAdd = new Node(element);
    if(isEmpty()) {
        head = tail = toAdd;
    } else {
        tail->next = toAdd;
        tail = toAdd;
    }
    size++;
}

template <typename T>
void SinglyLinkedList<T>::popFront() {
    if(isEmpty()) {
        throw std::logic_error("Empty list!");
    }
    if(head == tail) {
        delete head;
        head = tail = nullptr;
        size = 0;
        return;
    } else {   
        Node* toBeDeleted = head;
        head = head->next;
        delete toBeDeleted;
    }
    size--;
}

template <typename T>
const T& SinglyLinkedList<T>::front() const {
    if(!head) {
        throw std::logic_error("Empty list!");
    }
    return head->data;
}

template <typename T>
const T& SinglyLinkedList<T>::back() const {
    if(!tail) {
        throw std::logic_error("Empty list!");
    }
    return tail->data;
}

template <typename T>
T& SinglyLinkedList<T>::front() {
    if(!head) {
        throw std::logic_error("Empty list!");
    }
    return head->data;
}

template <typename T>
T& SinglyLinkedList<T>::back() {
    if(!tail) {
        throw std::logic_error("Empty list!");
    }
    return tail->data;
}

template <typename T>
size_t SinglyLinkedList<T>::getSize() const {
    return size;
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const {
    return getSize() == 0;
}

template <typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs) {
    SinglyLinkedList<T> result;

    if(!lhs.head) {
        result.head = rhs.head;
        result.tail = rhs.tail;
    } else if(!rhs.head) {
        result.head = lhs.head;
        result.tail = lhs.tail;
    } else {
        lhs.tail->next = rhs.head;
        result.head = lhs.head;
        result.tail = rhs.tail;
    }
    result.size = lhs.size + rhs.size;
    lhs.size = rhs.size = 0;
    lhs.head = lhs.tail = rhs.head = rhs.tail = nullptr;

    return result;
}
template <typename T>
void SinglyLinkedList<T>::print() const {
    Node* current = head;
    while(current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr";
}

template <typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other) {
    Node* current = other.head;
    while(current) {
        pushBack(current->data);
        current = current->next;
    }
}

template <typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = other.tail = nullptr;
    other.size = 0;
}

template <typename T>
void SinglyLinkedList<T>::free() {
    Node* current = head;
    while(current) {
        Node* toBeDeleted = current;    
        current = current->next;
        delete toBeDeleted;
    }
    head = tail = nullptr;
    size = 0;
}