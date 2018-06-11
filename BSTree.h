#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct TreeNode {
	T data;
	TreeNode* left;
	TreeNode* right;

	TreeNode() {
		left = NULL;
		right = NULL;
	}
};

template <typename T>
class BSTree {
public:
	BSTree();
	~BSTree();
	BSTree(const BSTree& other);
	BSTree<T>& operator=(const BSTree& other);

	void add(const T& data);
	void removeFirst(const T& data, bool(*isEqual)(const T& v1, const T& v2));
	void removeAll(const T& data);
	bool search(const T& data, bool(*isMatch)(const T& v1, const T& v2));

	void print();

private:
	TreeNode<T>* root;
	 
	TreeNode<T>* copy(TreeNode<T>* root);
	void destroy(TreeNode<T>*& n);

	void add(const T& data, TreeNode<T>*& root);
	void removeFirst(const T& data, bool(*isEqual)(const T& v1, const T& v2), TreeNode<T>*& root);
	void removeAll(const T& data, TreeNode<T>*& root);

	bool search(const T& data, bool(*isMatch)(const T& v1, const T& v2), TreeNode<T>*& root);
	T findMin(TreeNode<T>*& root);

	void print(TreeNode<T>*& root, int level = 0);
};

template <typename T>
BSTree<T>::BSTree() {
	root = NULL;
}

template <typename T>
BSTree<T>::~BSTree() {
	destroy(root);
}

template <typename T>
BSTree<T>::BSTree(const BSTree& other) {
	root = copy(other.root);
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& other) {
	if (this != &other) {
		destroy(root);
		root = copy(other.root);
	}
	return *this;
}

template <typename T>
TreeNode<T>* BSTree<T>::copy(TreeNode<T>* root) {
	if (!root) {
		return NULL;
	}
	
	TreeNode<T>* newNode = new TreeNode<T>;
	newNode->data = root->data;
	newNode->left = copy(root->left);
	newNode->right = copy(root->right);

	return newNode;
}

template <typename T>
void BSTree<T>::destroy(TreeNode<T>*& n) {
	if (n) {
		destroy(n->right);
		destroy(n->left);

		delete n;
		n = NULL;
	}
}

template <typename T>
void BSTree<T>::add(const T& data) {
	add(data, root);
}

template <typename T>
void BSTree<T>::add(const T& data, TreeNode<T>*& root) {
	if (!root) {

		TreeNode<T>* newElem = new TreeNode<T>;
		newElem->data = data;
		newElem->left = NULL;
		newElem->right = NULL;
		root = newElem;
	}
	else {

		if (data <= root->data) {
			add(data, root->left);
		}
		else {
			add(data, root->right);
		}
	}
}

template <typename T>
void BSTree<T>::removeFirst(const T& data, bool(*isEqual)(const T& v1, const T& v2)) {
	removeFirst(data, isEqual, root);
}

template <typename T>
void BSTree<T>::removeFirst(const T& data, bool(*isEqual)(const T& v1, const T& v2), TreeNode<T>*& root) {
	if (root) {
		if (data < root->data) {
			removeFirst(data, isEqual, root->left);
		}
		if (data > root->data) {
			removeFirst(data, isEqual, root->right);
		}
		if (data == root->data) {
			if (isEqual(data, root->data)) {
				if (root->left && root->right) {
					T minElement = findMin(root->right);
					root->data = minElement;
					removeFirst(minElement, isEqual, root->right);
				}
				else if (root->left) {
					TreeNode<T>* toDelete = root;
					root = root->left;
					delete toDelete;
					toDelete = NULL;
				}
				else if (root->right) {
					TreeNode<T>* toDelete = root;
					root = root->right;
					delete toDelete;
					toDelete = NULL;
				}
				else {
					delete root;
					root = NULL;
				}
			}
			else {
				removeFirst(data, isEqual, root->left);
			}
		}
	}
}

template <typename T>
void BSTree<T>::removeAll(const T& data) {
	removeAll(data, root);
}

template <typename T>
void BSTree<T>::removeAll(const T& data, TreeNode<T>*& root) {
	if (root) {
		if (data < root->data) {
			removeAll(data, root->left);
		}
		if (data > root->data) {
			removeAll(data, root->right);
		}
		if(data == root->data) {
			if (root->left && root->right) {
				T minElement = findMin(root->right);
				root->data = minElement;
				removeAll(minElement, root->right);
				removeAll(data, root->left);
			}
			else if (root->left) {
				TreeNode<T>* toDelete = root;
				root = root->left;
				delete toDelete;
				toDelete = NULL;
			}
			else if (root->right){
				TreeNode<T>* toDelete = root;
				root = root->right;
				delete toDelete;
				toDelete = NULL;
			}
			else {
				delete root;
				root = NULL;
			}
		}
	}
}

template <typename T>
T BSTree<T>::findMin(TreeNode<T>*& root) {
	TreeNode<T>* elem = root;
	while (elem->left) {
		elem = elem->left;
	}
	return elem->data;
}

template <typename T>
void BSTree<T>::print(){
	print(root);
}

template <typename T>
void BSTree<T>::print(TreeNode<T>*& root, int level){
	if (root) {
		for (int i = 0; i < level; i++) {
			cout << '\t';
		}
		cout << root->data << endl;
		
		print(root->left, level + 1);
		print(root->right, level + 1);
	}
}

template <typename T>
bool BSTree<T>::search(const T& data, bool(*isMatch)(const T& v1, const T& v2)) {
	return search(data, isMatch, root);
}

template <typename T>
bool BSTree<T>::search(const T& data, bool(*isMatch)(const T& v1, const T& v2), TreeNode<T>*& root) {
	if (root) {
		if (data < root->data) {
			return search(data, isMatch, root->left);
		}
		else if (data == root->data) {
			if (isMatch(data, root->data)) {
				return true;
			}
			else {
				return search(data, isMatch, root->left);
			}
		}
		else {
			return search(data, isMatch, root->right);
		}
	}

	return false;
}