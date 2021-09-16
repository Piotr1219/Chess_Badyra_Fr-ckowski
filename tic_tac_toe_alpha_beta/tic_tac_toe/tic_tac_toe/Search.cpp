#include <iostream>
#include <algorithm>
#include <iterator>
#include "Search.h"
#include "Board.h"
#include "main.h"

void GeneratePositions(int* board, int &depth, int board_size, Node* &root) {

	// from defaut x starts each game, need to specify that everywhere

	// generate all possible moves from given position, where first element of pointer is moves count
	int* possible_moves = Board::GenerateValidMoves(board, board_size);
	const int len = possible_moves[0];

	// allocate space for all root's children and declare child_count

	root->children = new Node * [len];
	root->children_count = len;

	// check which symbol should be drawn next and declare symbol value: 1 = 'x', -1 = 'o'
	int move_count = Board::CountMoves(root->squares, board_size);
	int symbol = 0;
	if (move_count % 2 == 0) {
		symbol = 1;
	}
	else {
		symbol = -1;
	}

	// for each possible position we need to create new child and add it to root->children array
	for (int i = 0; i < len; ++i) {

		Node* child = new Node;
		child->squares = new int[board_size * board_size];

		// we need to copy squares, so root squares will not be changed
		std::copy(root->squares, root->squares + int(board_size*board_size), child->squares);

		// adding 1 to array index, because [0] element is moves count, not index of squares array
		child->squares[possible_moves[i + 1]] = symbol;
		child->score = 0;
		child->parent = root;
		root->children[i] = child;
		child->children_count = 0;

		// in small board_size values depth is not needed, we can evaluate all positions, but might be usefull in future implementations

		int* left_cells = Board::GenerateValidMoves(child->squares, board_size);
		if (left_cells[0] != 0) {

			// increasing value of depth, because we are going deeper into tree
			depth = depth + 1;
			GeneratePositions(child->squares, depth, board_size, child);
		}

		//std::cout << "Try to delete left_cells" << std::endl;
		delete[] left_cells;
	}

	//std::cout << "Try to delete possible_moves" << std::endl;
	delete[] possible_moves;

	// decreasing depth, because we are returning from recursive algorithm, which means we are going up
	depth = depth - 1;
}

int SearchBestMove(Node* &root) {
	PrintBoard(root->squares, 3);
	while (root->children_count != 0) {
		//std::cout << "Children count: "<< root->children_count << std::endl;
		root = root->children[0];
		//PrintBoard(root->squares, 3);
	}
	//PrintBoard(root->squares, 3);
	//std::cout << "Koniec searchbestmove" << std::endl;
	return 0;
}

void DeleteTree(Node* root, int &depth) {
	for (int i = 0; i < root->children_count; ++i) {
		if (root->children[i]->children_count != 0) {
			depth = depth + 1;
			DeleteTree(root->children[i], depth);
		}
		//std::cout << "Delete tree depth: " << depth << ", i: " << i << ", children_count: " << root->children[i]->children_count << std::endl;
		root->children[i]->parent = NULL;
		root->children[i]->score = NULL;
		delete[] root->children[i]->squares;
		delete root->children[i];
	}
	delete[] root->children;
	root->children_count = 0;
	depth = depth - 1;
	if (root->parent == NULL) {
		root->score = NULL;
		delete[] root->squares;
		delete root;
	}
}