#include <iostream>

class Node {
private:
	int contestant_strength;
	int contestant_time_stamp;
	Node* next;

public:
	Node(int strength, int time_stamp) : contestant_strength(strength), contestant_time_stamp(time_stamp), next(nullptr) {}

	virtual ~Node() {}

	int getContestantStrength() const {
		return contestant_strength;
	}

	void setContestantStrength(int strength) {
		contestant_strength = strength;
	}

	int getContestantTimeStamp() const {
		return contestant_time_stamp;
	}

	void setContestantTimeStamp(int time_stamp) {
		contestant_time_stamp = time_stamp;
	}

	Node* getNext() const {
		return next;
	}

	void setNext(Node* next_node) {
		next = next_node;
	}
};


class Stack {
private:
	Node* topNode;

public:
	Stack() : topNode(nullptr) {}

	~Stack() {
		while (!empty()) {
			pop();
		}
	}

	void push(int strength, int time_stamp) {
		Node* newNode = new Node(strength, time_stamp);
		newNode->setNext(topNode);
		topNode = newNode;
	}

	void pop() {
		if (!empty()) {
			Node* temp = topNode;
			topNode = topNode->getNext();
			delete temp;
		}
	}

	Node* top() const {
		return topNode;
	}

	bool empty() const {
		return topNode == nullptr;
	}

	Stack* flipStack() const {
		Stack* flipped = new Stack();
		Node* current = topNode;
		while (current != nullptr) {
			flipped->push(current->getContestantStrength(), current->getContestantTimeStamp());
			current = current->getNext();
		}
		return flipped;
	}


	int size() const {
		int count = 0;
		Node* current = topNode;
		while (current != nullptr) {
			count++;
			current = current->getNext();
		}
		return count;
	}

	void print() const {
		if (empty()) {
			std::cout << "Stack is empty." << std::endl;
			return;
		}
		std::cout << "Stack (top to bottom): ";
		Node* current = topNode;
		while (current != nullptr) {
			std::cout << "(" << current->getContestantStrength() << ", " << current->getContestantTimeStamp() << ") ";
			current = current->getNext();
		}
		std::cout << std::endl;
	}
};
