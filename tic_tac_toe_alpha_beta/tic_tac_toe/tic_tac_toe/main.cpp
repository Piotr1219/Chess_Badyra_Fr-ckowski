#include <iostream>
#include "Board.cpp"
#include "main.h"
#include "Search.cpp"

int main() {
	Board board = Board(3);

	Node* current_pos = new Node;

	// set who is starting game
	// board.human_starts = false;

	PrintBoard(board.squares, board.size);

	if (!board.human_starts) {
		board.ComputerMove(board);
		PrintBoard(board.squares, board.size);
	}

	int depth = 1;
	while (!board.IsGameFinished(board)) {
		board.HumanMove(board);
		std::cout << "Generowanie ruchow" << std::endl;

		Node* root = new Node;
		root->squares = new int[board.size * board.size];
		std::copy(board.squares, board.squares + 9, root->squares);
		root->score = 0;
		root->parent = 0;

		current_pos = GeneratePositions(board.squares, depth, board.size, root);
		std::cout << "Adres current_pos: " << current_pos << std::endl;
		std::cout << "Ilosc dzieci current_pos: " << current_pos->children_count << std::endl;
		//std::cout << "Potencjalne miejsce problemu " << current_pos->children_count << std::endl;
		//PrintBoard(current_pos->children[7]->squares, board.size);
		int val = SearchBestMove(current_pos);
		std::cout << "Po generowaniu ruchow, pozycja wyglada nastepujaco: " << std::endl;

		PrintBoard(current_pos->squares, board.size);
		if (board.IsGameFinished(board)) {
			break;
		}
		else {
			board.ComputerMove(board);
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