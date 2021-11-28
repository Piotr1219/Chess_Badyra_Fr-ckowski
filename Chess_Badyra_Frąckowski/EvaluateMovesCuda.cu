#include "EvaluateMovesCuda.cuh"
#include <assert.h>
//#include <stdio.h>
#include <chrono>


#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char* file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}


__global__ void evaluate_moves_kernel(Square* squares, int* each_square_possible_moves, Position* moves) {
	int block_index = blockIdx.x;
	int cell_index = blockIdx.x * blockDim.x + threadIdx.x;

	if (squares[block_index].Piece1.PieceType != ChessPieceType::None) {
		if (each_square_possible_moves[cell_index] > 0 && each_square_possible_moves[cell_index] < 64) {
			//moves[cell_index] = Position();

			moves[cell_index].SrcPosition = block_index;
			moves[cell_index].DstPosition = each_square_possible_moves[cell_index];

			//Piece pieceAttacked = squares[moves[cell_index].DstPosition].Piece1;
			//moves[cell_index].Score += pieceAttacked.PieceValue - squares[block_index].Piece1.PieceValue;

			// move.Score += squares[move.DstPosition].Piece1.Moved
			//moves[cell_index].Score += squares[block_index].Piece1.PieceActionValue;
			//printf("Move from %d to %d\n", block_index, each_square_possible_moves[cell_index]);
		}
		else {
			moves[cell_index].SrcPosition = -1;
		}
	}
	else {
		moves[cell_index].SrcPosition = -1;
	}
}


namespace EvaluateMoves {
	list<Position> EvaluateMovesCuda(Board& examineBoard, char depth) {
		// first we need to copy all moves from each piece lists to array
		std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
		int* each_squares_possible_moves = new int[64 * 32];

		for (int i = 0; i < 64; ++i) {
			Piece piece = examineBoard.Squares[i].Piece1;
			if (piece.PieceType == ChessPieceType::None)
				continue;

			//Make sure the color is the same color as the one we are moving.
			if (piece.PieceColor != examineBoard.WhoseMove)
				continue;
			std::copy(piece.ValidMoves.begin(), piece.ValidMoves.end(), each_squares_possible_moves + 32 * i);
		}
		std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
		std::cout << "Time for list to array conversion: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[µs]" << std::endl;

		std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
		Square* d_squares;
		int* d_each_square_possible_moves;
		Position* d_moves;
		Position* moves = (Position*)malloc(64 * 32 * sizeof(Position));

		cudaMalloc(&d_squares, 64 * sizeof(Square));
		cudaMalloc(&d_each_square_possible_moves, 64 * 32 * sizeof(int));
		cudaMalloc(&d_moves, 64 * 32 * sizeof(Position));

		cudaMemcpy(d_squares, examineBoard.Squares, 64 * sizeof(Square), cudaMemcpyHostToDevice);
		cudaMemcpy(d_each_square_possible_moves, each_squares_possible_moves, 64 * 32 * sizeof(int), cudaMemcpyHostToDevice);
		std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
		std::cout << "Time for data upload: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[µs]" << std::endl;

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		evaluate_moves_kernel << <64, 32 >> > (d_squares, d_each_square_possible_moves, d_moves);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "Time for cuda kernel only: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
		cudaMemcpy(moves, d_moves, 64 * 32 * sizeof(Position), cudaMemcpyDeviceToHost);
		cudaDeviceSynchronize();
		cudaFree(d_squares), cudaFree(d_each_square_possible_moves), cudaFree(d_moves);
		
		list<Position> positions = list<Position>();
		for (int i = 0; i < 64 * 32; ++i) {
			if (moves[i].SrcPosition != -1) {
				positions.push_back(moves[i]);
			}
		}

		return positions;
	}
}
