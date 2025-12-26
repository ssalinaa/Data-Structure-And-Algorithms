#include <iostream>

template<typename T>
class CircularQueue {
private:
    T* data;
    size_t capacity;
    size_t count;

    size_t getIter;
    size_t putIter;

    void resize();
    void copyFrom(const CircularQueue& other);
    void free();
public:
    CircularQueue();
    CircularQueue(const CircularQueue& other);
    CircularQueue& operator=(const CircularQueue& other);
    ~CircularQueue();

    void enqueue(const T& element);
    void dequeue();
    const T& peek() const;
    bool isEmpty() const;
};  

template<typename T>
void CircularQueue<T>::resize() {
    size_t newCapacity = capacity * 2;
    size_t currentCapacity = capacity;

    T* newData = new T[newCapacity];
    for (size_t i = 0; i < currentCapacity; i++)
    {
        newData[i] = peek();
        dequeue();
    }
    getIter = 0;
    putIter = capacity;

    count = capacity;
    capacity *= 2;

    delete[] data;
    data = newData;
}

template<typename T>
void CircularQueue<T>::copyFrom(const CircularQueue& other) {
    data = new T[other.capacity];
    for (size_t i = other.getIter; i != other.putIter; (i+=1)%=other.capacity)
    {
        data[i] = other.data[i];
    }
    count = other.count;
    capacity = other.capacity;

    putIter = other.putIter;
    getIter = other.getIter;
}

template<typename T>
void CircularQueue<T>::free() {
    delete[] data;
    count = capacity = 0;
}

template<typename T>
CircularQueue<T>::CircularQueue() {
    const size_t DEFAULT_CAPACITY = 4;

    data = new T[DEFAULT_CAPACITY];
    capacity = DEFAULT_CAPACITY;
    count = 0;
    getIter = 0;
    putIter = 0;
}

template<typename T>
CircularQueue<T>::CircularQueue(const CircularQueue<T>& other) {
    copyFrom(other);
}

template<typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
CircularQueue<T>::~CircularQueue() {
    free();
}

template<typename T>
void CircularQueue<T>::enqueue(const T& element) {
    if(count == capacity) {
        resize();
    }
    data[putIter] = element;
    (++putIter) %= capacity;
    count++;
}

template<typename T>
void CircularQueue<T>::dequeue() {
    if(isEmpty()) {
        throw std::runtime_error("Empty queue!");
    }
    count--;
    (++getIter) %= capacity;
}

template<typename T>
const T& CircularQueue<T>::peek() const {
    if(isEmpty()) {
        throw std::runtime_error("Empty queue!");
    }
    return data[getIter];
}

template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return count == 0;
}