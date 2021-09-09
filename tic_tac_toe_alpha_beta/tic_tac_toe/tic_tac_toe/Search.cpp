#include <iostream>
#include <algorithm>
#include <iterator>
#include "Search.h"
#include "Board.h"
#include "main.h"

void GeneratePositions(Board board, int &depth) {

	int* possible_moves = board.GenerateValidMoves(board);
	int len = possible_moves[0];

	Node* root = new Node;
	root->squares = new int[board.size * board.size];
	std::copy(board.squares, board.squares + 9, root->squares);
	root->score = 0;
	root->parent = 0;
	root->children = new Node* [len];

	for (int i = 0; i < len; ++i) {
		Node* child = new Node;
		child->squares = new int[board.size * board.size];
		std::copy(root->squares, root->squares + 9, child->squares);
		char symbol = board.CountWhoseMove(board);
		if (symbol == 'x') {
			child->squares[possible_moves[i + 1]] = 1;
		}
		else {
			child->squares[possible_moves[i + 1]] = -1;
		}
		child->score = 0;
		child->parent = root;
		root->children[i] = child;
		//std::cout << "Depth is: " << depth << ", i is: " << i << std::endl;
		//PrintBoard(child->squares, board.size);

		Board new_board = Board(3);
		new_board.squares = child->squares;
		depth = depth + 1;
		int* left_cells;
		left_cells = new_board.GenerateValidMoves(board);
		if (left_cells[0]!=0) {
			GeneratePositions(new_board, depth);
		}
		else {
			depth = depth - 1;
		}
	}
	depth = depth - 1;
	//return root;
}