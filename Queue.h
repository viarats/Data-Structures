#pragma once

template <typename T>
class Queue {
public:
	Queue();
	~Queue();
	Queue(const Queue& other);
	Queue<T>& operator=(Queue& other);

	void enqueue(const T& element);
	void dequeue();
	const T& front() const;
	bool isEmpty();

private:
	struct Node {
		T data;
		Node* next;

		Node(const T& data, Node* next = NULL);
	};

	Node* first;
	Node* last;

	void copy(Queue& other);
	void destroy();
};

template <typename T>
Queue<T>::Node::Node(const T& data, Node* next) {
	this->data = data;
	this->next = next;
}

template <typename T>
Queue<T>::Queue() {
	first = NULL;
	last = NULL;
}

template <typename T>
void Queue<T>::destroy() {
	while (!isEmpty()) {
		Node* temp = first;
		first = first->next;
		delete temp;
	}
}

template <typename T>
Queue<T>::~Queue() {
	destroy();
}

template <typename T>
void Queue<T>::copy(Queue& other) {
	while (!other.isEmpty()) {
		this->enqueue(other.front());
		other.dequeue();
	}
}

template <typename T>
Queue<T>::Queue(const Queue& other) {
	copy(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue& other) {
	if (this != &other) {
		destroy();
		copy(other);
	}
	return *this;
}

template <typename T>
void Queue<T>::enqueue(const T& element) {
	Node* n = new Node(element);
	if (isEmpty()) {
		first = n;
	}
	else {
		last->next = n;
	}
	last = n;
}

template <typename T>
void Queue<T>::dequeue() {
	first = first->next;
}

template <typename T>
bool Queue<T>::isEmpty() {
	return first == NULL;
}

template <typename T>
const T& Queue<T>::front() const {
	return first->data;
}