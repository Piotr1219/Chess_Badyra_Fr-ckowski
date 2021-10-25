#include <iostream>
#include <algorithm>
#include <iterator>
#include "Search.h"
#include "Board.h"
#include "main.h"

void GeneratePositions(int* board, int& depth, int board_size, Node*& root) {

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
		std::copy(root->squares, root->squares + int(board_size * board_size), child->squares);

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


long factorial(long long k) {
	long res = 1;
	while (k > 0) {
		res *= k--;
	}
	return res;
}

void GenerateFlatTree(int parent_offset, int parent_sibling_count, int& depth, int board_size, flat_node** memory, int last_child) {

	// calculate symbol (-1 o 1) to be added to board
	int move_count = Board::CountMoves(memory[parent_offset]->squares, board_size);
	int symbol = 0;
	if (move_count % 2 == 0) {
		symbol = 1;
	}
	else {
		symbol = -1;
	}
	
	int len = 0;

	// fist child of new layer is 1 later than last from previous layer
	int offset = last_child+1;

	// for each parent 
	for (parent_offset; parent_offset <= last_child; ++parent_offset) {

		int* possible_moves = Board::GenerateValidMoves(memory[parent_offset]->squares, board_size);
		len = possible_moves[0];

		memory[parent_offset]->children_count = len;

		if (len != 0) {

			//printf("There are possible moves\n");

			// initialize each parent with now known child_count
			memory[parent_offset]->first_child = parent_offset + parent_sibling_count;
			//printf("Parent address: %p\n", memory[parent_offset]);
			//for (parent_offset; parent_offset <= last_child; ++parent_offset) {

			// for each child in parent
			for (int i = 0; i < len; ++i) {
				memory[offset] = new flat_node;
				//printf("Offset: %d, parent_offset: %d\n", offset, parent_offset);
				//printf("New address: %p\n", memory[offset]);
				memory[offset]->parent = parent_offset;
				memory[offset]->score = 0;
				std::copy(memory[parent_offset]->squares, memory[parent_offset]->squares + int(board_size * board_size), memory[offset]->squares);
				//for (int j = 0; j < 9; ++j) {
				//	printf("%d ", memory[i+1]->squares[j]);
				//}
				//printf("\n");
				memory[offset]->squares[possible_moves[i + 1]] = symbol;
				//for (int j = 0; j < 9; ++j) {
				//	printf("%d ", memory[offset]->squares[j]);
				//}
				//printf("\n\n");
				printf("Offset: %d, depth: %d, parent_offset: %d, child_number %d\n", offset, depth, parent_offset, i);
				offset = offset + 1;
			}
		}
	}
	if (len != 0) {
		depth = depth + 1;
		GenerateFlatTree(parent_offset, memory[parent_offset - 1]->children_count, depth, board_size, memory, offset - 1);
	}

}

flat_node ** CreateFlatTreeHead(int* board, int& depth, int board_size) {
	// not sure how to properly calculate numbers of nodes, always can add too much 
	int elements_count = factorial(8) + factorial(8) / factorial(2) + factorial(8)/factorial(3) + factorial(8)/factorial(4) + factorial(8)/factorial(5) + factorial(8)/factorial(6) + 8;	// + factorial(0) ???
	printf("Elements count: %d\n", elements_count);

	// allocating linear block of memory
	flat_node** memory = (flat_node**)malloc(elements_count * sizeof(flat_node*));

	// if allocation succeeds
	if (memory) {

		// root initialization
		int offset = 0;
		memory[offset] = new flat_node;
		memory[offset]->parent = 0;
		memory[offset]->score = 0;
		std::copy(board, board + int(board_size * board_size), memory[offset]->squares);

		// generating from root
		GenerateFlatTree(offset, 1, depth, board_size, memory, offset);
	}
	else {
		printf("Not enough space to alocate for tree\n");
	}
	return memory;
}

int SearchBestMove(Node* root, bool Maximize, int alpha, int beta) {
	if (root->children_count == 0) {
		root->score = IsGameFinished(root->squares, 3);						// HARDCODED FOR NOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//std::cout << "Returned score from leaf: " << root->score << " from: " << std::endl;
		//PrintBoard(root->squares, 3);
		return root->score;
	}

	if (Maximize) {
		int bestVal = -10000;
		for (int i = 0; i < root->children_count; ++i) {
			int val = SearchBestMove(root->children[i], false, alpha, beta);
			bestVal = std::max(bestVal, val);
			alpha = std::max(bestVal, alpha);
			if (beta <= alpha) {
				break;
			}
			
		}
		root->score = bestVal;
		return root->score;
	}
	else {
		int bestVal = 10000;
		for (int i = 0; i < root->children_count; ++i) {
			int val = SearchBestMove(root->children[i], true, alpha, beta);
			bestVal = std::min(bestVal, val);
			beta = std::min(bestVal, beta);
			if (beta <= alpha) {
				break;
			}
			
		}
		root->score = bestVal;
		return root->score;
	}
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