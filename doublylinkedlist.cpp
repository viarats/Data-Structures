 // doublylinkedlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;

bool lessThan(const int& x, const int& y) {
	return x < y;
}

int main() {

	DoublyLinkedList<int> l;
	l.append(3);
	l.prepend(4);
	l.prepend(9);
	l.prepend(8);
	l.prepend(1);
	l.append(4);
	l.append(4);
	l.append(5);
	DoublyLinkedList<int>::Iterator it(l.getFirst());

	while (it.getTarget()) {
		cout << *it << " ";
		it.moveForward();
	}

	cout << endl << "----sorted----" << endl;

	l.sort(&lessThan);
	it.setTarget(l.getFirst());

	while (it.getTarget()) {
		cout << *it << " ";
		it.moveForward();
	}

	cout << endl;

    return 0;
}