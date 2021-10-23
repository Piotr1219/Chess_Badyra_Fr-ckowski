#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Search.h"

#include <stdio.h>

typedef int* (*pointFunctionGenerateValidMoves)(int*, int);
typedef int (*pointFunctionCountMoves)(int*, int);

__device__ int CountMovesGPU(int* squares, int size);
__device__ int* GenerateValidMovesGPU(int* squares, int board_size);
__device__ bool IsMoveValidGPU(int* squares, int board_size, int move);
__device__ int IsGameFinishedGPU(int* squares, int board_size);

namespace Test {
	void test(void);
	void GenerateTree(int* board, int &depth, int board_size, Node* root);
}