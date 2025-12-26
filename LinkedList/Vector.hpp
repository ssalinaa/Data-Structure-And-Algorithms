#pragma once
#include <stdexcept>

namespace Constants {
    constexpr unsigned GROWTH_FACTOR = 2;
}

template<typename T>
class Vector {
public:
    Vector() = default;
    explicit Vector(size_t count);
    Vector(size_t count, const T& intial);

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    void push_back(const T& element);
    void push_back(T&& element);
    void pop_back();

    void clear();
    void resize(size_t n);
    void reserve(size_t n);
    void shrink_to_fit();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t getSize() const;
    size_t getCapacity() const;
    bool empty() const;

    T& back();
    const T& back() const;
    T& front();
    const T& front() const;

private:
    void copy(const Vector& other);
    void move(Vector&& other) noexcept;
    void free(); 
    size_t calculate_capacity() const;

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

template<typename T>
Vector<T>::Vector(size_t count) : data(new T[count]), size(count), capacity(count) { }
    
template<typename T>
Vector<T>::Vector(size_t count, const T& initial) : data(new T[count]), size(count), capacity(count) { 
    for (size_t i = 0; i < size; i++)
    {
        data[i] = initial;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
    copy(other);
}
    
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if(this != &other) {
        free();
        copy(other);
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    move(std::move(other));
}
    
template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if(this != &other) {
        free();
        move(std::move(other));
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    free();
}
    
template<typename T>
void Vector<T>::push_back(const T& element) {
    if(size == capacity) {
        reserve(calculate_capacity());
    }
    data[size++] = element;
}
    
template<typename T>
void Vector<T>::push_back(T&& element) {
    if(size == capacity) {
        reserve(calculate_capacity());
    }
    data[size++] = std::move(element);
}
    
template<typename T>
void Vector<T>::pop_back() {
    if(!empty()) {
        --size;
    }
}
    
template<typename T>
void Vector<T>::clear() {
    size = 0;
}
    
template<typename T>
void Vector<T>::resize(size_t n) {
    if(n > capacity) {
        reserve(n);
    }
    size = n;
}
    
template<typename T>
void Vector<T>::reserve(size_t n) {
    if(n <= capacity) return;
    T* newData = new T[n];
    for (size_t i = 0; i < size; i++)
    {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    capacity = n;
}
    
template<typename T>
void Vector<T>::shrink_to_fit() {
    if(capacity == size) return;
    T* newData = new T[size];
    for (size_t i = 0; i < size; i++)
    {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    capacity = size;
}

    
template<typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}
    
template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data[index];
}

template<typename T>
size_t Vector<T>::getSize() const {
    return size;
}
    
template<typename T>
size_t Vector<T>::getCapacity() const {
    return capacity;
}
    
template<typename T>
bool Vector<T>::empty() const {
    return getSize() == 0;
}
    
template<typename T>
T& Vector<T>::back() {
    if(empty()) {
        throw std::logic_error("Empty vector!");
    }
    return data[size - 1];
}
    
template<typename T>
const T& Vector<T>::back() const {
    if(empty()) {
        throw std::logic_error("Empty vector!");
    }
    return data[size  - 1];
}
    
template<typename T>
T& Vector<T>::front() {
    if(empty()) {
        throw std::logic_error("Empty vector!");
    }
    return data[0];
}
    
template<typename T>
const T& Vector<T>::front() const {
    if(empty()) {
        throw std::logic_error("Empty vector!");
    }
    return data[0];
}

template<typename T>
void Vector<T>::copy(const Vector& other) {
    data = new T[other.capacity];
    for (size_t i = 0; i < other.size; i++)
    {
        data[i] = other.data[i];
    }
    size = other.size;
    capacity = other.capacity;
}
    
template<typename T>
void Vector<T>::move(Vector&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}
    
template<typename T>
void Vector<T>::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}
    
template<typename T>
size_t Vector<T>::calculate_capacity() const {
    return capacity == 0 ? 1 : capacity * Constants::GROWTH_FACTOR;
}