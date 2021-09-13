#include <iostream>
#include "Board.h"

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

bool Board::IsGameFinished(Board board) {
	int test_sum_row = 0;

	for (int i = 0; i < board.size; ++i) {
		for (int j = 0; j < board.size; ++j) {
			if (board.squares[i * board.size + j] == 1 and test_sum_row >= 0) {
				++test_sum_row;
			}
			else if (board.squares[i * board.size + j] == -1 and test_sum_row <= 0) {
				--test_sum_row;
			}
			else {
				test_sum_row = 0;
			}

			if (test_sum_row == 3 || test_sum_row == -3) {
				return true;
			}
		}
	}

	int test_sum_col = 0;

	for (int j = 0; j < board.size; ++j) {
		for (int i = 0; i < board.size; ++i) {
			if (board.squares[i * board.size + j] == 1 and test_sum_col >= 0) {
				++test_sum_col;
			}
			else if (board.squares[i * board.size + j] == -1 and test_sum_col <= 0) {
				--test_sum_col;
			}
			else {
				test_sum_col = 0;
			}

			if (test_sum_col == 3 || test_sum_col == -3) {
				return true;
			}
		}
	}

	int test_sum_diagonal = 0;

	for (int i = 0; i < board.size; ++i) {
		if (board.squares[i * board.size + i] == 1 and test_sum_diagonal >= 0) {
			++test_sum_diagonal;
		}
		else if (board.squares[i * board.size + i] == -1 and test_sum_diagonal <= 0) {
			--test_sum_diagonal;
		}
		else {
			test_sum_diagonal = 0;
		}

		if (test_sum_diagonal == 3 || test_sum_diagonal == -3) {
			return true;
		}
	}

	test_sum_diagonal = 0;

	for (int i = 0; i < board.size; ++i) {
		if (board.squares[i * board.size + (board.size - 1 - i)] == 1 and test_sum_diagonal >= 0) {
			++test_sum_diagonal;
		}
		else if (board.squares[i * board.size + (board.size - 1 - i)] == -1 and test_sum_diagonal <= 0) {
			--test_sum_diagonal;
		}
		else {
			test_sum_diagonal = 0;
		}

		if (test_sum_diagonal == 3 || test_sum_diagonal == -3) {
			return true;
		}
	}

	return 0;
}

char Board::CheckWhoseMove(Board board) {
	//std::cout << "X: " << board.x_placed_count << ", O: " << board.o_placed_count << std::endl;
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

void Board::ComputerMove(Board &board) {
	char symbol = Board::CheckWhoseMove(board);

	// further implementation of choosing best move

	int *free_cells = Board::GenerateValidMoves(board);
	if (sizeof(free_cells) > 0) {
		int move = free_cells[1];

		board.squares[move] = -1;
		board.o_placed_count = board.o_placed_count + 1;
	}
	else {
		std::cout << "Game is drawn" << std::endl;
	}
}

void Board::HumanMove(Board& board) {
	bool move_made = false;
	int move;
	while (!move_made) {
		std::cout << "Wprowadz swoj ruch: ";
		std::cin >> move;
		if (Board::IsMoveValid(board, move)) {
			board.squares[move] = 1;
			move_made = true;
			board.x_placed_count = board.x_placed_count + 1;
		}
		else {
			std::cout << "Ruch niepoprawny! Wprowadz poprawny ruch" << std::endl;
		}
	}
}

int* Board::GenerateValidMoves(Board board) {
	int* free_cells = new int[board.size * board.size - board.x_placed_count - board.o_placed_count + 1];
	int counter = 0;

	for (int i = 0; i < board.size * board.size; ++i) {
		if (board.squares[i] == 0) {
			free_cells[counter+1] = i;
			++counter;
		}
	}
	free_cells[0] = counter;
	return free_cells;
}

bool Board::IsMoveValid(Board board, int move) {
	if (board.squares[move] == 0) {
		return true;
	}
	return false;
}

void Board::CheckWhoWon(Board board) {
	char symbol = Board::CheckWhoseMove(board);
	if (symbol == 'x') {
		std::cout << "Wygral gracz X!" << std::endl;
	}
	else {
		std::cout << "Wygral gracz O!" << std::endl;
	}
}

char Board::CountWhoseMove(Board board) {
	int count_x = 0;
	int count_o = 0;

	for (int i = 0; i < board.size * board.size; ++i) {
		if (board.squares[i] == 1) {
			++count_x;
		}
		else if (board.squares[i] == -1) {
			++count_o;
		}
	}
	if (board.human_starts) {
		if (count_x == count_o) {
			return 'x';
		}
		return 'o';
	}
	else {
		if (count_x == count_o) {
			return 'o';
		}
		return 'x';
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