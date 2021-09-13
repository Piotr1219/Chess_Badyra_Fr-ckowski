#include <iostream>
#include <algorithm>
#include <iterator>
#include "Search.h"
#include "Board.h"
#include "main.h"

Node* GeneratePositions(int* board, int &depth, int board_size, Node* root) {

	//to find mistakes
	Board temp_board = Board(board_size);
	temp_board.squares = board;

	int* possible_moves = temp_board.GenerateValidMoves(temp_board);
	int len = possible_moves[0];

	root->children = new Node * [len];
	root->children_count = len;

	int temp_count = temp_board.CountMoves(root->squares, board_size);
	//if (temp_count <= 3) {
	//	std::cout << "Root adress: " << root << ", when count_moves is: " << temp_count << std::endl;
	//}

	for (int i = 0; i < len; ++i) {
		Node* child = new Node;
		//std::cout << "My address: " << child << std::endl;
		child->squares = new int[board_size * board_size];
		std::copy(root->squares, root->squares + int(board_size*board_size), child->squares);
		char symbol = temp_board.CountWhoseMove(temp_board);
		if (symbol == 'x') {
			child->squares[possible_moves[i + 1]] = 1;
		}
		else {
			child->squares[possible_moves[i + 1]] = -1;
		}
		child->score = 0;
		child->parent = root;
		root->children[i] = child;
		//std::cout << "Parent adress: " << child->parent << std::endl;
		//std::cout << "Depth is: " << depth << ", i is: " << i << std::endl;
		//PrintBoard(child->squares, board.size);

		Board new_board = Board(3);
		new_board.squares = child->squares;
		depth = depth + 1;
		int* left_cells;
		left_cells = new_board.GenerateValidMoves(new_board);
		if (left_cells != 0) {
			child = GeneratePositions(new_board.squares, depth, new_board.size, child);
			int count = new_board.CountMoves(child->squares, new_board.size);
			if (count <= 2) {
				//std::cout << "Child children_count: " << child->children_count << std::endl;
				//std::cout << "Parent adress: " << child->parent << std::endl;
				//PrintBoard(child->squares, board.size);
			}
		}
		else {
			depth = depth - 1;
		}
	}
	//delete[] possible_moves;
	depth = depth - 1;
	if (root->children_count == 7) {
		//std::cout << "Parent adress: " << root->parent << std::endl;
		//std::cout << "root->children[i] before returning child_count: " << root->children[0]->children_count << std::endl;
		//PrintBoard(root->squares, board.size);
	}
	return root;
}

int SearchBestMove(Node* &root) {
	PrintBoard(root->squares, 3);
	while (root->children_count != 0) {
		std::cout << "Children count: "<< root->children_count << std::endl;
		root = root->children[0];
		PrintBoard(root->squares, 3);
	}
	//PrintBoard(root->squares, 3);
	std::cout << "Koniec searchbestmove" << std::endl;
	return 0;
}