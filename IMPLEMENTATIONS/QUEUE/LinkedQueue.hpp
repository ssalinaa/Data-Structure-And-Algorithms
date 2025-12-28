#include <iostream>

template <typename T>
class LinkedQueue {
    struct Node {
        T data;
        Node* next;

        Node(T data) {
            this->data = data;
            next = nullptr;
        }
    };
    Node* head;
    Node* tail;

    void free();
    void copyFrom(const LinkedQueue& other);
public: 
    LinkedQueue();
    LinkedQueue(const LinkedQueue& other);
    LinkedQueue& operator=(const LinkedQueue& other);
    ~LinkedQueue();

    void enqueue(const T&);
    void dequeue();
    const T& peek() const;
    bool isEmpty() const;
};

template <typename T>
void LinkedQueue<T>::free() {
    Node* current = head;
    while(current) {
        Node* toBeDeleted = current;
        current = current->next;
        delete toBeDeleted;
    }
    head = tail = nullptr;
}

template <typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue& other) {
    Node* currentOther = other.head;
    while(currentOther) {
        enqueue(currentOther->data);
        currentOther = currentOther->next;
    }
}

template <typename T>
LinkedQueue<T>::LinkedQueue() {
    head = tail = nullptr;
}   

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& other) {
    copyFrom(other);
}   

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    free();
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& element) {
    Node* newNode = new Node(element);
    if(isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
void LinkedQueue<T>::dequeue() {
    if(isEmpty()) {
        throw std::logic_error("Empty queue!");
    } else if (head == tail) {
        T element = head->data;
        delete head;
        head = tail = nullptr;
    } else {
        Node* toBeDeleted = head;
        head = head->next;
        delete toBeDeleted;
    }
}

template <typename T>
const T& LinkedQueue<T>::peek() const {
    if(isEmpty()) {
        throw std::logic_error("Empty queue!");
    }
    return head->data;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return head == nullptr && tail == nullptr;
}