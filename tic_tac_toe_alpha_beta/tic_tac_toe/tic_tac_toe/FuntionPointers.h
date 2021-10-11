#pragma once
#include "Board.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

typedef int* (*pointFunctionGenerateValidMoves)(int*, int);
typedef int (*pointFunctionCountMoves)(int*, int);

//extern __device__ pointFunctionCountMoves CountMovesPointer = Board::CountMoves;
//extern pointFunctionCountMoves host_CountMovesPointer;

extern __device__ pointFunctionGenerateValidMoves GenerateValidMovesPointer = Board::GenerateValidMoves;
extern pointFunctionGenerateValidMoves host_GenerateValidMovesPointer;
