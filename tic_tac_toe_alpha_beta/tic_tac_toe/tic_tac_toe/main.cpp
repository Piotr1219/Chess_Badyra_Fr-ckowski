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
		board.ComputerMove(board);
		PrintBoard(board.squares, board.size);
	}

	while (!board.IsGameFinished(board)) {
		board.HumanMove(board);
		std::cout << "Generowanie ruchow" << std::endl;
		int depth = 1;
		GeneratePositions(board, depth);
		std::cout << "Po generowaniu ruchow, pozycja wyglada nastepujaco: " << std::endl;

		PrintBoard(board.squares, board.size);
		if (board.IsGameFinished(board)) {
			break;
		}
		else {
			board.ComputerMove(board);
		}
		PrintBoard(board.squares, board.size);
	}

}

void PrintBoard(int* squares, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << squares[i * size + j] << "   ";
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << std::endl;
}