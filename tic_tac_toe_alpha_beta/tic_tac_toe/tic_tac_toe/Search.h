#pragma once
#include <iostream>

struct Node {
	Node* parent;
	Node** children;
	int children_count;
	short score;
	int* squares;
};