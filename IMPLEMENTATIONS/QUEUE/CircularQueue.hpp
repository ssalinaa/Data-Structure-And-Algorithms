#include <iostream>

template<typename T>
class CircularQueue {
private:
    T* data;
    size_t capacity;
    size_t count;

    size_t putIter;
    size_t getIter;

    void resize();
    void copyFrom(const CircularQueue<T>& other);
    void free();
public:
    CircularQueue();
    CircularQueue(const CircularQueue<T>& other);
    CircularQueue& operator=(const CircularQueue<T>& other);
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
void CircularQueue<T>::copyFrom(const CircularQueue<T>& other) {
    data = new T[other.capacity];
    for(int i = other.getIter; i != other.putIter; i = (i + 1) % other.capacity) {
        data[i] = other.data[i];
    }
    count = other.count;
    capacity = other.capacity;

    getIter = other.getIter;
    putIter = other.putIter;
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
bool CircularQueue<T>::isEmpty() const {
    return count == 0;
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
    if(count == 0) {
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