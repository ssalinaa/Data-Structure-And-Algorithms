#include <iostream>

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) {
            this->data = data;
            next = nullptr;
        }
    };
public:
    SinglyLinkedList();
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
    T& back();

    size_t getSize() const;
    bool isEmpty() const;

    template<typename U>
    friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

    void print() const;

    class Iterator {
        friend class SinglyLinkedList;
    public:
        typedef std::forward_iterator_tag iterator_category;
        
        Iterator(Node* currentElementPointer = nullptr) : currentElementPointer(currentElementPointer) { }
        
        T& operator*() {
            return currentElementPointer->data;
        }
        T* operator->() {
            return &currentElementPointer->data;
        }
        Iterator& operator++() {
            if(currentElementPointer) {
                currentElementPointer = currentElementPointer->next;
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator copy(*this);
            ++(*this);
            return copy;
        }
        Iterator operator+=(size_t s) {
            while(s--) {
                ++(*this);
            }
            return *this;
        }
        Iterator operator+(int i) const {
            Iterator res(*this);
            return res += i;
        }
        bool operator==(const Iterator& other) const {
            return currentElementPointer == other.currentElementPointer;
        }
        bool operator!=(const Iterator& other) const {
            return !(other == *this);
        }
    };

    class ConstIterator {
    public:
        Node* currentElementPointer;
        friend class SinglyLinkedList;
    public:
        typedef std::forward_iterator_tag iterator_category;
        
        ConstIterator(const Iterator& nonConstIterator) : currentElementPointer(nonConstIterator.currentElementPointer) { }
        ConstIterator(Node* currentElementPointer = nullptr) : currentElementPointer(currentElementPointer) { }

        const T& operator*() const {
            return currentElementPointer->data;
        }
        const T* operator->() const {
            return &currentElementPointer->data;
        }
        ConstIterator& operator++() {
            if(currentElementPointer) {
                currentElementPointer = currentElementPointer->next;
            }
            return *this;
        }
        ConstIterator operator++(int) {
            ConstIterator copy(*this);
            ++(*this);
            return copy;
        }
        ConstIterator& operator+=(size_t s) {
            while(s--) {
                ++(*this);
            }
            return *this;
        }
        ConstIterator operator+(int i) const {
            ConstIterator res(*this);
            return res += i;
        }
        bool operator==(const ConstIterator& other) const {
            return currentElementPointer == other.currentElementPointer;
        }
        bool operator!=(const ConstIterator& other) const {
            return !(other == *this);        
        }
    };

    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    ConstIterator cbegin() const {
        return ConstIterator(head);
    }
    ConstIterator cend() const {
        return ConstIterator(nullptr);
    }

    Iterator insertAfter(const T& element, const ConstIterator& it);
    Iterator insertBefore(const T& element, const ConstIterator& it);
    Iterator erase(const ConstIterator& it);
    Iterator eraseAfter(const ConstIterator& it);

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

    void copyFrom(const SinglyLinkedList<T>& other);
    void moveFrom(SinglyLinkedList<T>&& other);
    void free();
};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
    copyFrom(other);
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) {
    moveFrom(std::move(other));
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    free();
}

template<typename T>
void SinglyLinkedList<T>::pushFront(const T& element) {
    Node* newNode = new Node(element);
    if(isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

template<typename T>
void SinglyLinkedList<T>::pushBack(const T& element) {
    Node* newNode = new Node(element);
    if(isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template<typename T>
void SinglyLinkedList<T>::popFront() {
    if(isEmpty()) {
        throw std::logic_error("Empty list!");
    } else if(head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* toBeDeleted = head;
        head = head->next;
        delete toBeDeleted;
    }
}

template<typename T>
const T& SinglyLinkedList<T>::front() const {
    if(!head) {
        throw std::logic_error("Empty list!");
    }
    return head->data;
}

template<typename T>
const T& SinglyLinkedList<T>::back() const {
    if(!tail) {
        throw std::logic_error("Empty list!");
    }
    return tail->data;
}

template<typename T>
T& SinglyLinkedList<T>::front() {
    if(!head) {
        throw std::logic_error("Empty list!");
    }
    return head->data;
}

template<typename T>
T& SinglyLinkedList<T>::back() {
    if(!tail) {
        throw std::logic_error("Empty list!");
    }
    return tail->data;
}

template<typename T>
size_t SinglyLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
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
    rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;
    return result;
}

template<typename T>
void SinglyLinkedList<T>::print() const {
    Node* current = head;
    while(current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << " nullptr ";
}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::insertAfter(const T& element, const typename SinglyLinkedList<T>::ConstIterator& it) {
    Node* current = it.currentElementPointer;

    if(!current) {
        throw std::logic_error("Cannot insert after end iterator!");
    }
    Node* newNode = new Node(element);
    newNode->next = current->next;
    current->next = newNode;

    if(current == tail) {
        tail = newNode;
    }

    ++size;
    return Iterator(newNode);
}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::insertBefore(const T& element, const typename SinglyLinkedList<T>::ConstIterator& it) {
    Node* current = it.currentElementPointer;

    if(!current) {
        throw std::logic_error("Cannot insert before end iterator!");
    }
    if(current == head) {
        pushFront(element);
        return Iterator(head);
    }
    Node* previous = head;
    while(previous && previous->next != current) {
        previous = previous->next;
    }

    if(!previous) {
        throw std::logic_error("Iterator does not belong to this list!");
    }

    Node* newNode = new Node(element);
    newNode->next = current;
    previous->next = newNode;
    ++size;

    return Iterator(newNode);
}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::erase(const typename SinglyLinkedList<T>::ConstIterator& it) {
    Node* current = it.currentElementPointer;
    if(!current) {
        throw std::logic_error("Cannot erase end iterator!");
    }

    if(current == head) {
        popFront();
        return Iterator(head);
    }

    Node* previous = head;
    while(previous && previous->next != current) {
        previous = previous->next;
    }

    if(!previous) {
       throw std::logic_error("Iterator does not belong to this list!");
    }
    
    previous->next = current->next;
    if(current == tail) {
        tail = previous;
    }
    Node* nextNode = current->next;
    delete current;
    --size;
    
    return Iterator(nextNode);
}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::eraseAfter(const typename SinglyLinkedList<T>::ConstIterator& it) {
    Node* current = it.currentElementPointer;
    if(!current || !current->next) {
        throw std::logic_error("Nothing to erase after iterator!");    
    }
    Node* toDelete = current->next;
    current->next = toDelete->next;

    if(toDelete == tail) {
        tail = current;
    }
    Iterator result(toDelete->next);
    delete toDelete;
    --size;
    return result;
}

template<typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other) {
    Node* currentOther = other.head;
    while(currentOther) {
        pushBack(currentOther->data);
        currentOther = currentOther->next;
    }
}

template<typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList<T>&& other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = other.tail = nullptr;
    other.size = 0;
}

template<typename T>
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

int main() {
    SinglyLinkedList<int> list;

    std::cout << "=== Initial pushBack & pushFront ===\n";
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushFront(5);
    list.print();
    std::cout << "\n";

    std::cout << "\n=== insertAfter (insert 15 after 10) ===\n";
    auto it = list.begin();
    while (*it != 10 && it != list.end()) ++it;
    if (it != list.end()) {
        list.insertAfter(15, it);
    }
    list.print(); 
    std::cout << "\n";

    std::cout << "\n=== insertBefore (insert 17 before 20) ===\n";
    auto it2 = list.begin();
    while (*it2 != 20 && it2 != list.end()) ++it2;
    if (it2 != list.end()) {
        list.insertBefore(17, it2);
    }
    list.print(); 
    std::cout << "\n";

    std::cout << "\n=== erase (remove 17) ===\n";
    auto it3 = list.begin();
    while (*it3 != 17 && it3 != list.end()) ++it3;
    if (it3 != list.end()) {
        list.erase(it3);
    }
    list.print(); 
    std::cout << "\n";

    std::cout << "\n=== eraseAfter (remove element after 15) ===\n";
    auto it4 = list.begin();
    while (*it4 != 15 && it4 != list.end()) ++it4;
    if (it4 != list.end()) {
        list.eraseAfter(it4);
    }
    list.print(); 
    std::cout << "\n";

    std::cout << "\n=== popFront ===\n";
    list.popFront();
    list.print(); 
    std::cout << "\n";

    std::cout << "\n=== Testing front() and back() ===\n";
    std::cout << "Front: " << list.front() << "\n";
    std::cout << "Back: " << list.back() << "\n";

    std::cout << "\n=== Iterating with Iterator ===\n";
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Size check ===\n";
    std::cout << "Size: " << list.getSize() << "\n";

    return 0;
}
