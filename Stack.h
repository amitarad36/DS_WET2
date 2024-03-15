#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& newData) : data(newData), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    Node<T>* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (!empty()) {
            Node<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        else {
            // std::cerr << "Stack underflow: Cannot pop from an empty stack." << std::endl;
        }
    }

    const T& top() const {
        if (!empty()) {
            return topNode->data;
        }
        else {
            // throw std::out_of_range("Stack is empty");
        }
    }

    bool empty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        Node<T>* current = topNode;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};
