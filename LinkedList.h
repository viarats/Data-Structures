#pragma once

template <typename T>
struct Node {
	T data;
	Node* next;

	Node(const T& data, Node* next = NULL) {
		this->data = data;
		this->next = next;
	}
};

template <typename T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList<T>& operator=(const LinkedList& other);

	class Iterator {
	private:

		Node<T>* target;
		friend class LinkedList;

	public:

		Iterator(Node<T>* n) {
			this->target = n;
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

		void setTarget(Node<T>* n) {
			this->target = n;
		}
	};

	Node<T>* getFirst();
	Node<T>* getLast();
	int getSize() const;

	void append(const T& data);
	void prepend(const T& data);

	void insertAfter(int index, const T& data);
	void insertBefore(int index, const T& data);

	void removeFirst();
	void removeLast();
	void removeAt(int index, Iterator& it);

	bool isEmpty();

	void sort(bool(*lessThan)(const T& v1, const T& v2));

private:
	Node<T>* first;
	Node<T>* last;
	int size;

	void copy(const LinkedList& other);
	void destroy();

	Node<T>* insert(Node<T>* n, bool(*lessThan)(const T& v1, const T& v2));
	Node<T>* findNode(int index);
};

template <typename T>
LinkedList<T>::LinkedList() {
	first = NULL;
	last = NULL;
	size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
	void copy(other);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
	if (this != &other) {
		destroy();
		copy(oter);
	}
	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	destroy();
}

template <typename T>
void LinkedList<T>::destroy() {
	while (first) {
		Node<T>* temp = first;
		first = first->next;
		delete temp;
	}
}

template <typename T>
void LinkedList<T>::copy(const LinkedList& other) {
	first = NULL;
	last = NULL;

	for (Iterator it(other.first); it.target; it.moveForward()) {
		append(it.target->data);
	}
}

template <typename T>
Node<T>* LinkedList<T>::getFirst() {
	return first;
}

template <typename T>
Node<T>* LinkedList<T>::getLast() {
	return last;
}

template <typename T>
void LinkedList<T>::append(const T& data) {
	if (isEmpty()) {
		first = last = new Node<T>(data);
	}
	else {
		last->next = new Node<T>(data);
		last = last->next;
	}
	size++;
}

template <typename T>
void LinkedList<T>::prepend(const T& data) {
	if (isEmpty()) {
		first = last = new Node<T>(data);
	}
	else {
		first = new Node<T>(data, first);
	}
	size++;
}

template <typename T>
void LinkedList<T>::insertAfter(int index, const T& data) {
	if (index < 0) {
		return;
	}
	if (index == size - 1) {
		append(data);
	}
	else {
		findNode(index)->next = new Node<T>(data, findNode(index)->next);
	}
	size++;
}

template <typename T>
void LinkedList<T>::insertBefore(int index, const T& data) {
	if (index < 0) {
		return;
	}
	if (!index) {
		prepend(data);
	}
	else {
		findNode(index - 1)->next = new Node<T>(data, findNode(index));
	}
	size++;
}

template <typename T>
void LinkedList<T>::removeFirst() {
	Node<T>* temp = first;
	first = first->next;

	delete temp;
	size--;
}

template <typename T>
void LinkedList<T>::removeLast() {
	Node<T>* toDelete = last;
	last = findNode(size - 2);
	last->next = NULL;

	delete toDelete;
	size--;
}

template <typename T>
Node<T>* LinkedList<T>::findNode(int index) {
	if (index < 0) {
		return NULL;
	}

	Node<T>* n = first;
	for (int i = 0; i < index; i++) {
		if (n) {
			n = n->next;
		}
	}
	return n;
}

template <typename T>
void LinkedList<T>::removeAt(int index, Iterator& it) {
	if (index < 0) {
		return;
	}
	if (!index) {
		removeFirst();
		it.target = first;
	}
	else if (index == size - 1) {
		removeLast();
		it.target = last;
	}
	else {

		Node<T>* toDelete = findNode(index);
		Node<T>* beforeIndex = findNode(index - 1);
		beforeIndex->next = findNode(index)->next;
		it.target = beforeIndex->next;
		delete toDelete;

		size--;
	}
}

template <typename T>
int LinkedList<T>::getSize() const {
	return size;
}

template <typename T>
bool LinkedList<T>::isEmpty() {
	return !first;
}

template <typename T>
Node<T>* LinkedList<T>::insert(Node<T>* n, bool (*lessThan)(const T& v1, const T& v2)) {
	if (!n || !n->next) {
		return n;
	}
	Node<T>* head = NULL;

	while (n) {
		Node<T>* curr = n;
		n = n->next;

		if (!head || lessThan(curr->data, head->data)) {
			curr->next = head;
			head = curr;
		}

		else {
			Node<T>* i = head;
			while (i) {
				if (!i->next || lessThan(curr->data, i->next->data)) {
					curr->next = i->next;
					i->next = curr;
					break;
				}
				i = i->next;
			}
		}
	}
	return head;
}

template <typename T>
void LinkedList<T>::sort(bool(*lessThan)(const T& v1, const T& v2)) {
	first = insert(first, lessThan);
	last = first;
	while (last->next) {
		last = last->next;
	}
}