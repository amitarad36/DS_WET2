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
    }

    const T& top() const {
        if (!empty()) {
            return topNode->data;
        }
    }

    bool empty() const {
        return topNode == nullptr;
    }

    int size() const {
        int count = 0;
        Node<T>* current = topNode;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    void print() const {
        if (empty()) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }
        std::cout << "Stack (top to bottom): ";
        Node<T>* current = topNode;
        while (current != nullptr) {
            std::cout << *(current->data) << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};
