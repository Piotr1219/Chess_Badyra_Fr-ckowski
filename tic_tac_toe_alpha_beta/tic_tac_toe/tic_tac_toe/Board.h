#pragma once
#include <iostream>
#include "device_launch_parameters.h"

class Board {

public:

	int size;
	int *squares;
	int x_placed_count;
	int o_placed_count;
	bool human_starts;
	
	//constructor

	Board(int size);

	char CheckWhoseMove(Board board);
	void ComputerMove(Board &board);
	void HumanMove(Board& board);
	void CheckWhoWon(Board board);
	
	__host__ __device__ static int CountMoves(int* squares, int size);
	__host__ __device__ static int* GenerateValidMoves(int* squares, int board_size);
	__host__ __device__ static bool IsMoveValid(int* squares, int board_size, int move);

};

int IsGameFinished(int* squares, int board_size);