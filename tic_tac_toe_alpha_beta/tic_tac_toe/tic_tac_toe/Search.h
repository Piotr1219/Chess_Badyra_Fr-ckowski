#pragma once
#include <iostream>

struct Node {
	Node* parent;
	Node** children;
	short score;
	int* squares;
};