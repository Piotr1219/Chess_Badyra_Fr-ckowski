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
	while (IsGameFinished(board.squares, board.size)==0) {
		board.HumanMove(board);
		++depth;

		// create a root from current position
		Node* root = new Node;
		root->squares = new int[board.size * board.size];
		std::copy(board.squares, board.squares + 9, root->squares);
		root->score = 0;
		root->parent = NULL;

		if (IsGameFinished(board.squares, board.size)!=0) {
			PrintBoard(board.squares, board.size);
			board.CheckWhoWon(board);
			PrintBoard(board.squares, board.size);
			break;
		}
		else {
			GeneratePositions(board.squares, depth, board.size, root);
			int alpha = -10000;
			int beta = 10000;
			int val = SearchBestMove(root, false, alpha, beta);
			std::cout << "Val returned by searching tree: " << val << std::endl;

			for (int i = 0; i < root->children_count; ++i) {
				std::cout << "Wynik wezla: " << root->children[i]->score << std::endl;
				PrintBoard(root->children[i]->squares, 3);
			}

			std::cout << "Sprawdzono dzieci" << std::endl;
			for (int i = 0; i < root->children_count; ++i) {
				if (root->children[i]->score == val) {
					std::cout << "Wczytanie board" << std::endl;
					//PrintBoard(root->children[i]->squares, board.size);
					//std::copy(board.squares, board.squares + int(board.size * board.size), root->children[i]->squares);
					//PrintBoard(board.squares, board.size);
					//board.squares = root->children[i]->squares;
					for (int j = 0; j < board.size * board.size; ++j) {
						board.squares[j] = root->children[i]->squares[j];
					}
					std::cout << "Break" << std::endl;
					break;
				}
			}
			//board.ComputerMove(board);
			int delete_depth = 0;
			PrintBoard(board.squares, board.size);
			++depth;
			DeleteTree(root, delete_depth);
		}
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