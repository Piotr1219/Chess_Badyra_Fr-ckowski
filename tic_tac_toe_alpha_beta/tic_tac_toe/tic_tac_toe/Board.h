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
	int* GenerateValidMoves(Board board);
	char CountWhoseMove(Board board);
	int CountMoves(int* squares, int size);

private:

	void CheckWhoWon(Board board);
	bool IsMoveValid(Board board, int move);

};