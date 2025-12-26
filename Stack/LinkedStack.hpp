#include <iostream>

template<typename T>
class LinkedStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) {
            this->data = data;
            next = nullptr;
        }
    };
    Node* head;

    void free();
    void copyFrom(const LinkedStack& other);
public:
    LinkedStack();
    LinkedStack(const LinkedStack& other);
    LinkedStack<T>& operator=(const LinkedStack& other);
    ~LinkedStack();

    void push(const T&);
    void pop();
    const T& peek() const;
    bool isEmpty() const;
};

template<typename T>
void LinkedStack<T>::free() {
    Node* current = head;
    while(current) {
        Node* toBeDeleted = current;
        current = current->next;
        delete toBeDeleted;
    }
}

template<typename T>
void LinkedStack<T>::copyFrom(const LinkedStack<T>& other) {
    head = nullptr;
    if(other.isEmpty()) {
        return;
    }

    Node* currentOther = other.head;
    head = new Node(currentOther->data);
    Node* current = head;
    currentOther = currentOther->next;
    while(currentOther) {
        current->next = new Node(currentOther->data);
        currentOther = currentOther->next;
        current = current->next;
    }
}

template<typename T>
LinkedStack<T>::LinkedStack() {
    head = nullptr;
}

template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other) {
    copyFrom(other);
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    free();
}

template<typename T>
void LinkedStack<T>::push(const T& element) {
    Node* newNode = new Node(element);
    if(isEmpty()) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

template<typename T>
void LinkedStack<T>::pop() {
    if(isEmpty()) {
        throw std::logic_error("Empty stack!");
    }
    else if(!head->next) {
        delete head;
        head = nullptr;
    } else {
        Node* toBeDeleted = head;
        head = head->next;
        delete toBeDeleted;
    }
}

template<typename T>
const T& LinkedStack<T>::peek() const {
    if(isEmpty()) {
        throw std::logic_error("Empty stack!");
    }
    return head->data;
}

template<typename T>
bool LinkedStack<T>::isEmpty() const {
    return head == nullptr;
}
