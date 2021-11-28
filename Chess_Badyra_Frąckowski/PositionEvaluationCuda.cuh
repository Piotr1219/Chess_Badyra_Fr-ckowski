# pragma once
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <device_functions.h>
#include "Square.h"
#include "Piece.h"
#include "Board.h"
#include "Evaluations2.h"
#include <stdio.h>

__global__ void evaluate_board_kernel(Square* squares, bool endGamePhase, int* score);
__global__ void evaluate_board_kernel_v2(bool endGamePhase, int* score, short* Kings, short* Queens, short* Rooks, short* Bishops, short* Knights, short* Pawns);

namespace EvaluatePieces {
	void EvaluatePiecesCuda(Board& board);
}