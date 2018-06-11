#include "stdafx.h"
#include "Stack.h"

template <typename T>
Stack<T>::Node::Node(const T& data, const Node* next) {
	this->data = data;
	this->next = next;
}

template <typename T>
Stack<T>::Stack() {
	tos = NULL;
}

template <typename T>
void Stack<T>::destroy() {
	Node<T>* temp;
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
void Stack<T>::copy(const Stack& other) {
	if (other.isEmpty()) {
		return;
	}
	Node<T>* ours;
	Node<T>* theirs;
	try {
		tos = new Node<T>(other.tos->data);
		ours = tos;
		theirs = other.tos->next;

		while (theirs) {
			ours->next = new Node<T>(theirs->data);
			ours = ours->next;
			theirs = theirs->next;
		}
		catch (std::bad_alloc&) {
			destroy();
			throw;
		}
	}
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	copy(other);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
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
	tos = new Node<T>(elem, tos);
}

template <typename T>
T Stack<T>::pop() {
	Node<T>* temp = tos;
	tos = tos->next;
	T data = temp->data;
	delete temp;
	return data;
}

template <typename T>
const T& Stack<T>::top() const {
	return tos->data;
}