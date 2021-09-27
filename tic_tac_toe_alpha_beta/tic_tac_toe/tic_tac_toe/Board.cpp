#include <iostream>
#include "Board.h"
#include "main.h"

Board::Board(int row_len) {

	size = row_len;
	squares = new int[int(size * size)];
	human_starts = true;
	x_placed_count = 0;
	o_placed_count = 0;

	// set board to be empty
	for (int i = 0; i < size * size; ++i) {
		squares[i] = 0;
	}

}

int IsGameFinished(int* squares, int board_size) {
	int test_sum_row = 0;

	// look for win in rows
	for (int i = 0; i < board_size; ++i) {
		test_sum_row = 0;
		for (int j = 0; j < board_size; ++j) {
			if (squares[i * board_size + j] == 1 and test_sum_row >= 0) {
				++test_sum_row;
			}
			else if (squares[i * board_size + j] == -1 and test_sum_row <= 0) {
				--test_sum_row;
			}
			else {
				test_sum_row = 0;
			}

			if (test_sum_row == 3 || test_sum_row == -3) {
				return test_sum_row;
			}
		}
	}

	int test_sum_col = 0;

	// look for win in columns
	for (int j = 0; j < board_size; ++j) {
		test_sum_col = 0;
		for (int i = 0; i < board_size; ++i) {
			if (squares[i * board_size + j] == 1 and test_sum_col >= 0) {
				++test_sum_col;
			}
			else if (squares[i * board_size + j] == -1 and test_sum_col <= 0) {
				--test_sum_col;
			}
			else {
				test_sum_col = 0;
			}

			if (test_sum_col == 3 || test_sum_col == -3) {
				return test_sum_col;
			}
		}
	}

	int test_sum_diagonal = 0;

	// look for win in diagonals

	// for now only support 3x3 boards and their main diagonals
	for (int i = 0; i < board_size; ++i) {
		if (squares[i * board_size + i] == 1 and test_sum_diagonal >= 0) {
			++test_sum_diagonal;
		}
		else if (squares[i * board_size + i] == -1 and test_sum_diagonal <= 0) {
			--test_sum_diagonal;
		}
		else {
			test_sum_diagonal = 0;
		}

		if (test_sum_diagonal == 3 || test_sum_diagonal == -3) {
			return test_sum_diagonal;
		}
	}

	test_sum_diagonal = 0;

	for (int i = 0; i < board_size; ++i) {
		if (squares[i * board_size + (board_size - 1 - i)] == 1 and test_sum_diagonal >= 0) {
			++test_sum_diagonal;
		}
		else if (squares[i * board_size + (board_size - 1 - i)] == -1 and test_sum_diagonal <= 0) {
			--test_sum_diagonal;
		}
		else {
			test_sum_diagonal = 0;
		}

		if (test_sum_diagonal == 3 || test_sum_diagonal == -3) {
			return test_sum_diagonal;
		}
	}

	int test_draw = 1;
	for (int i = 0; i < board_size * board_size; ++i) {
		test_draw = test_draw * squares[i];
	}

	return test_draw;
}

// need to check from CheckWhoseMove to CheckWhatSymbolNext, because x is always placed first
char Board::CheckWhoseMove(Board board) {

	// based on parity of placed symbols and value of board.human_starts evaluates which symbol will be placed next
	if (board.human_starts) {
		if (board.x_placed_count == board.o_placed_count) {
			return 'x';
		}
		return 'o';
	}
	else {
		if (board.x_placed_count == board.o_placed_count) {
			return 'o';
		}
		return 'x';
	}
}

// for now does first possible move 
void Board::ComputerMove(Board &board) {
	char symbol = Board::CheckWhoseMove(board);

	// further implementation of choosing best move

	int *free_cells = Board::GenerateValidMoves(board.squares, board.size);
	if (free_cells[0] != 0) {
		int move = free_cells[0];

		board.squares[move] = -1;
		board.o_placed_count = board.o_placed_count + 1;
	}
	else {
		std::cout << "Game is drawn" << std::endl;
	}
	delete[] free_cells;
}

void Board::HumanMove(Board& board) {

	int* free_cells = Board::GenerateValidMoves(board.squares, board.size);

	// if there is possible move to be made
	if (sizeof(free_cells) > 0) {
		bool move_made = false;
		int move = -1;
		while (!move_made) {
			std::cout << "Wprowadz swoj ruch: ";
			std::cin >> move;
			if (Board::IsMoveValid(board.squares, board.size, move)) {
				board.squares[move] = 1;
				move_made = true;
				board.x_placed_count = board.x_placed_count + 1;
			}
			else {
				std::cout << "Ruch niepoprawny! Wprowadz poprawny ruch" << std::endl;
			}
		}
	}
	else {
		std::cout << "Game is drawn" << std::endl;
	}
	delete[] free_cells;
}

int* Board::GenerateValidMoves(int* squares, int board_size) {
	int count_moves = Board::CountMoves(squares, board_size);
	int* free_cells = new int [board_size * board_size - count_moves + 1];
	int counter = 0;

	free_cells[0] = 0;
	for (int i = 0; i < board_size * board_size; ++i) {
		if (Board::IsMoveValid(squares, board_size, i)) {
			counter = counter + 1;
			//std::cout << "Move is still possible: " << i << std::endl;
			//PrintBoard(squares, board_size);
			free_cells[counter] = i;
		}
	}
	free_cells[0] = counter;

	return free_cells;
}

bool Board::IsMoveValid(int* squares, int board_size, int move) {
	if (IsGameFinished(squares, board_size) == 0) {
		if (move < board_size * board_size) {
			if (squares[move] == 0) {
				return true;
			}
		}
	}
	return false;
}

void Board::CheckWhoWon(Board board) {
	char symbol = Board::CheckWhoseMove(board);
	if (symbol == 'x') {
		std::cout << "Wygral gracz O!" << std::endl;
	}
	else {
		std::cout << "Wygral gracz X!" << std::endl;
	}
}

int Board::CountMoves(int* squares, int size) {
	int counter = 0;
	for (int i = 0; i < size * size; ++i) {
		if (squares[i] != 0) {
			++counter;
		}
	}
	return counter;
}