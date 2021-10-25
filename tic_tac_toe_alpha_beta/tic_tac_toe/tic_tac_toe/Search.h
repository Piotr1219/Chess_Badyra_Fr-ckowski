#pragma once
#include <iostream>

struct Node {
	Node* parent;
	Node** children;
	int children_count;
	short score;
	int* squares;
};

struct flat_node {
	unsigned int parent;
	unsigned int first_child;
	unsigned int children_count;
	unsigned int score;
	int squares[9];		// hardcoded for now 
};