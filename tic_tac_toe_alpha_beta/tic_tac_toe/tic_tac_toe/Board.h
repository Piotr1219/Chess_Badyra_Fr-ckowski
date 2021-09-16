#pragma once
#include <iostream>

class Board {

public:

	int size;
	int *squares;
	int x_placed_count;
	int o_placed_count;
	bool human_starts;
	
	//constructor

	Board(int size);

	bool IsGameFinished(Board board);
	char CheckWhoseMove(Board board);
	void ComputerMove(Board &board);
	void HumanMove(Board& board);
	void CheckWhoWon(Board board);
	
	static int CountMoves(int* squares, int size);
	static int* GenerateValidMoves(int* squares, int board_size);
	static bool IsMoveValid(int* squares, int board_size, int move);

};