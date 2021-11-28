# pragma once
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <device_functions.h>
#include "Square.h"
#include "Piece.h"
#include "Board.h"
#include "Position.h"
#include "Evaluations2.h"
#include <stdio.h>
#include <list>
#include <stack>


__global__ void evaluate_moves_kernel(Square* squares, int* each_square_possible_moves, Position* moves);


namespace EvaluateMoves {
	list<Position> EvaluateMovesCuda(Board& examineBoard, char depth);
}
