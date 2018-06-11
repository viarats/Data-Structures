// linkedlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

bool lessThan(const int& x, const int& y) {
	return x < y;
}

int main() {

	LinkedList<int> l;
	l.append(4);
	l.append(2);
	l.append(5);
	l.append(0);
	l.append(9);
	l.append(1);
	l.append(3);
	l.append(7);
	LinkedList<int>::Iterator it(l.getFirst());

	for (int i = 0; i < l.getSize(); i++) {
		cout << *it << " ";
		it.moveForward();
	}

	cout << endl << "----sorted-----" << endl;

	l.sort(&lessThan);
	it.setTarget(l.getFirst());
	for (int i = 0; i < l.getSize(); i++) {
		cout << *it << " ";
		it.moveForward();
	}

	cout << endl;

    return 0;
}
