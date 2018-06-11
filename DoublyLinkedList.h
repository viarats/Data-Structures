#pragma once

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;

	Node(const T& data, Node* prev = NULL, Node* next = NULL) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};

template <typename T>
class DoublyLinkedList {

public:
	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(DoublyLinkedList& other);
	DoublyLinkedList<T>& operator=(DoublyLinkedList& other);

	class Iterator {
	private:

		friend class DoublyLinkedList;
		Node<T>* target;

	public:

		Iterator(Iterator& other) {
			target = other.target;
		}

		Iterator(Node<T>* n) {
			target = n;
		}

		void moveBack() {
			if (target) {
				target = target->prev;
			}
		}

		void moveForward() {
			if (target) {
				target = target->next;
			}
		}

		const T& operator*() {
			return target->data;
		}

		Node<T>* getTarget() {
			return target;
		}

		void setTarget(Node<T>* target) {
			this->target = target;
		}
	};

	Node<T>* getFirst();
	Node<T>* getLast();

	void append(const T& data);
	void prepend(const T& data);

	void insertBefore(Iterator& it, const T& data);
	void insertAfter(Iterator& it, const T& data);

	void removeFirst();
	void removeLast();
	void removeAt(Iterator& it);

	bool isEmpty();
	bool isFirst(Iterator& it);
	bool isLast(Iterator& it);

	void sort(bool(*lessThan)(const T& v1, const T& v2));

private:
	Node<T>* first;
	Node<T>* last;

	void copy(DoublyLinkedList& other);
	void destroy();

	Node<T>* insert(Node<T>* tail, Node<T>* value, bool(*lessThan)(const T& v1, const T& v2));
	void swapAt(Node<T>* i, Node<T>* j, Node<T>* k);
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	first = NULL;
	last = NULL;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList& other) {
	copy(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList& other) {
	if (this != &other) {
		destroy();
		copy(other);
	}
	return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	destroy();
}

template <typename T>
void DoublyLinkedList<T>::copy(DoublyLinkedList& other) {
	first = NULL;
	last = NULL;
	for (Iterator it(other.target); it.target; it.moveForward()) {
		append(it.target->data);
	}
}

template <typename T>
void DoublyLinkedList<T>::destroy() {
	while (first) {
		Node<T>* toDelete = first;
		first = first->next;
		delete toDelete;
	}
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getFirst() {
	return first;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getLast() {
	return last;
}

template <typename T>
void DoublyLinkedList<T>::append(const T& data) {
	if (isEmpty()) {
		first = last = new Node<T>(data);
	}
	else {
		last->next = new Node<T>(data, last, NULL);
		last = last->next;
	}
}

template <typename T>
void DoublyLinkedList<T>::prepend(const T& data) {
	if (isEmpty()) {
		first = last = new Node<T>(data);
	}
	else {
		first->prev = new Node<T>(data, NULL, first);
		first = first->prev;
	}
}

template <typename T>
void DoublyLinkedList<T>::insertBefore(Iterator& it, const T& data) {
	if (!it.target) {
		return;
	}
	if (it.target == first) {
		prepend(data);
	}
	else {
		Node<T>* n = new Node<T>(data, it.target->prev, it.target);
		it.target->prev = n;
		n->prev->next = n;
	}
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(Iterator& it, const T& data) {
	if (!it.target) {
		return;
	}
	if (it.target == last) {
		append(data);
	}
	else {
		Node<T>* n = new Node<T>(data, it.target, it.target->next);
		it.target->next = n;
		n->next->prev = n;
	}
}

template <typename T>
void DoublyLinkedList<T>::removeFirst() {
	Node<T>* toDelete = first;
	first = first->next;
	first->prev = NULL;
	delete toDelete;
}

template <typename T>
void DoublyLinkedList<T>::removeLast() {
	Node<T>* toDelete = last;
	last = last->prev;
	last->next = NULL;
	delete toDelete;
}

template <typename T>
void DoublyLinkedList<T>::removeAt(Iterator& it) {
	if (!it.target) {
		return;
	}
	if (it.target == first && it.target == last) {
		it.target = first = last = NULL;
	}
	else if (it.target == first) {
		it.moveForward();
		removeFirst();
	}
	else if (it.target == last) {
		it.moveBack();
		removeLast();
	}
	else {
		Node<T>* toDelete = it.target;
		it.target->prev->next = it.target->next;
		it.target->next->prev = it.target->prev;

		it.target = it.target->next;

		delete toDelete;
	}
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
	return !first;
}

template <typename T>
bool DoublyLinkedList<T>::isFirst(Iterator& it) {
	return it.target == first;
}

template <typename T>
bool DoublyLinkedList<T>::isLast(Iterator& it) {
	return it.target == last;
}

template <typename T>
void DoublyLinkedList<T>::sort(bool(*lessThan)(const T& v1, const T& v2)) {
	if (!first || !first->next) {
		return;
	}
	Node<T>* i = first;

	while (i->next) {
		Node<T>* j = i->next;
		i = insert(i, j, lessThan);
	}

	last = i;
	while (i->prev) {
		i = i->prev;
	}
	first = i;

}

template <typename T>
Node<T>* DoublyLinkedList<T>::insert(Node<T>* tail, Node<T>* value, bool(*lessThan)(const T& v1, const T& v2)) {
	if (!lessThan(value->data, tail->data)) {             //check if value >= tail
		return value;
	}
	Node<T>* target = tail;
	while (target->prev && lessThan(value->data, target->prev->data)) {
		target = target->prev;
	}
	swapAt(tail, value, target);
	return tail;

}

template <typename T>
void DoublyLinkedList<T>::swapAt(Node<T>* i, Node<T>* j, Node<T>* k) {
	i->next = j->next;
	if (i->next) {
		i->next->prev = i;
	}

	j->prev = k->prev;
	if (j->prev) {
		j->prev->next = j;
	}

	k->prev = j;
	j->next = k;
}