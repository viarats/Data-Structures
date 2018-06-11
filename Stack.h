#pragma once
#include <exception>

template <typename T>
class Stack {

public:
	Stack();
	~Stack();
	Stack(const Stack& other);
	Stack<T>& operator=(Stack& other);

	void push(const T& elem);
	T pop();
	bool isEmpty();
	const T& top() const;

private:
	struct Node {
		T data;
		Node* next;
		Node(const T& data, Node* next = NULL);
	};

	Node* tos;

	void copy(Stack& other);
	void destroy();
};

template <typename T>
Stack<T>::Node::Node(const T& data, Node* next) {
	this->data = data;
	this->next = next;
}

template <typename T>
Stack<T>::Stack() {
	tos = NULL;
}

template <typename T>
void Stack<T>::destroy() {
	Node* temp;
	while (tos) {
		temp = tos;
		tos = tos->next;
		delete temp;
	}
}

template <typename T>
Stack<T>::~Stack() {
	destroy();
}

template <typename T>
void Stack<T>::copy(Stack& other) {
	if (other.isEmpty()) {
		return;
	}
	Node* ours;
	Node* theirs;
	try {
		tos = new Node(other.tos->data);
		ours = tos;
		theirs = other.tos->next;

		while (theirs) {
			ours->next = new Node(theirs->data);
			ours = ours->next;
			theirs = theirs->next;
		}
	}
	catch (std::bad_alloc&) {
		destroy();
		throw;
	}
}

template <typename T>
Stack<T>::Stack(const Stack& other) {
	copy(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack& other) {
	if (this != &other) {
		destroy();
		copy(other);
	}
	return *this;
}


template <typename T>
bool Stack<T>::isEmpty() {
	return !tos;
}

template <typename T>
void Stack<T>::push(const T& elem) {
	tos = new Node(elem, tos);
}

template <typename T>
T Stack<T>::pop() {
	Node* temp = tos;
	tos = tos->next;
	T data = temp->data;
	delete temp;
	return data;
}

template <typename T>
const T& Stack<T>::top() const {
	return tos->data;
}