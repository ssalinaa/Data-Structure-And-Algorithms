#include <iostream>
#include <deque>

template<typename T, typename Container = std::deque<T>>
class Queue {
private:
    Container c;

public:
    void push(const T& element) {
        c.push_back(element);
    }
    void push(T&& element) {
        c.push_back(std::move(element));
    }
    void pop() {
        c.pop_front();
    }
    T& front() {
        return c.front();
    }
    const T& front() const {
        return c.front();
    }
    T& back() {
        return c.back();
    }
    const T& back() const {
        return c.back();
    }
    bool empty() const {
        return c.empty();
    }
    size_t size() const {
        return c.size();
    }
};