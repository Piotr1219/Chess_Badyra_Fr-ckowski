#include <iostream>
#include "Board.cpp"
#include "main.h"
#include "Search.cpp"

int main() {
	Board board = Board(3);

	// set who is starting game
	// board.human_starts = false;

	PrintBoard(board.squares, board.size);

	if (!board.human_starts) {

		// have to add creating game tree if coumputer starts
		board.ComputerMove(board);
		PrintBoard(board.squares, board.size);
	}

	int depth = 0;
	while (!board.IsGameFinished(board)) {
		board.HumanMove(board);
		++depth;

		// create a root from current position
		Node* root = new Node;
		root->squares = new int[board.size * board.size];
		std::copy(board.squares, board.squares + 9, root->squares);
		root->score = 0;
		root->parent = NULL;

		if (board.IsGameFinished(board)) {
			PrintBoard(board.squares, board.size);
			board.CheckWhoWon(board);
			break;
		}
		else {
			GeneratePositions(board.squares, depth, board.size, root);

			//int val = SearchBestMove(root);
			board.ComputerMove(board);
			int delete_depth = 0;
			DeleteTree(root, delete_depth);
		}
		PrintBoard(board.squares, board.size);
		++depth;
	}

}

void PrintBoard(int* squares, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (squares[i * size + j] == 1) {
				std::cout << "x" << "   ";
			}
			else if (squares[i * size + j] == -1) {
				std::cout << "o" << "   ";
			}
			else {
				std::cout << "-" << "   ";
			}
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << std::endl;
}