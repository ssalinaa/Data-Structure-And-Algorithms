#pragma once
#include <deque>

template<class T, class Container=std::deque<T>>
class Stack {
private:
    Container c;
public:
    T& top() {
        return c.back();
    }
    const T& top() const {
        return c.back();
    }
    bool empty() const {
        return c.empty();
    }
    size_t size() const {
        return c.size();
    }
    void push(const T& element) {
        c.push_back(element);
    }
    void pop() {
        c.pop_back();
    }
};