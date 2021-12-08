#include <cuda.h>
#include <device_functions.h>
#include <cuda_runtime_api.h>
#include "PositionEvaluationCuda.cuh"
#include <assert.h>
//#include <stdio.h>
#include <chrono>
#ifndef __CUDACC__  
	#define __CUDACC__
#endif

extern long time_cuda = 0;
extern long count_positions = 0;
extern long min_time = 1000000000;
extern long max_time = 0;

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char* file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}

__global__ void sum_matrix(int* result) {
	__shared__ int score[64];

	int index = threadIdx.x;
	score[index] = result[index];

	__syncthreads();
	{
		//printf("Score from index %d is %d\n", index, score[index]);
		for (int stride = 32; stride > 0; stride >>= 1) {
			//__syncthreads();
			if (index < stride) {
				score[index] = score[index] + score[index + stride];
				//printf("Score from index %d is %d\n", index, score[index]);
			}
			__syncthreads();
		}

		result[0] = score[0];
	}
}

// square is a whole board
// 64 threads
// position is same thing as index, wont be needed
// endGamePhase is also same for all positions, neverhteless not sure if use it here, many ifs
// insufficientMaterial wyrzucamy, bardzo du¿o wystêpuje, lepiej zawsze dla roota to sprawdzaæ
// many things including pawns, but leaving it unchanged for now
// also bishop count and knigh count wont work, cannot iterate over board for it!!!
// same thing for pawns count

__device__ static short PawnTableGPU[64] =
{
		0,  0,  0,  0,  0,  0,  0,  0,
		50, 50, 50, 50, 50, 50, 50, 50,
		20, 20, 30, 40, 40, 30, 20, 20,
		5,  5, 10, 30, 30, 10,  5,  5,
		0,  0,  0, 25, 25,  0,  0,  0,
		5, -5,-10,  0,  0,-10, -5,  5,
		5, 10, 10,-30,-30, 10, 10,  5,
		0,  0,  0,  0,  0,  0,  0,  0
};
__device__ static short KnightTableGPU[64] =
{
	-50,-40,-30,-30,-30,-30,-40,-50,
	-40,-20,  0,  0,  0,  0,-20,-40,
	-30,  0, 10, 15, 15, 10,  0,-30,
	-30,  5, 15, 20, 20, 15,  5,-30,
	-30,  0, 15, 20, 20, 15,  0,-30,
	-30,  5, 10, 15, 15, 10,  5,-30,
	-40,-20,  0,  5,  5,  0,-20,-40,
	-50,-30,-20,-30,-30,-20,-30,-50,
};

__device__ static short BishopTableGPU[64] =
{
	-20,-10,-10,-10,-10,-10,-10,-20,
	-10,  0,  0,  0,  0,  0,  0,-10,
	-10,  0,  5, 10, 10,  5,  0,-10,
	-10,  5,  5, 10, 10,  5,  5,-10,
	-10,  0, 10, 10, 10, 10,  0,-10,
	-10, 10, 10, 10, 10, 10, 10,-10,
	-10,  5,  0,  0,  0,  0,  5,-10,
	-20,-10,-40,-10,-10,-40,-10,-20,
};

__device__ static short KingTableGPU[64] =
{
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-20, -30, -30, -40, -40, -30, -30, -20,
	-10, -20, -20, -20, -20, -20, -20, -10,
	20,  20,   0,   0,   0,   0,  20,  20,
	20,  30,  10,   0,   0,  10,  30,  20
};

__device__ static short KingTableEndGameGPU[64] =
{
	-50,-40,-30,-20,-20,-30,-40,-50,
	-30,-20,-10,  0,  0,-10,-20,-30,
	-30,-10, 20, 30, 30, 20,-10,-30,
	-30,-10, 30, 40, 40, 30,-10,-30,
	-30,-10, 30, 40, 40, 30,-10,-30,
	-30,-10, 20, 30, 30, 20,-10,-30,
	-30,-30,  0,  0,  0,  0,-30,-30,
	-50,-30,-30,-30,-30,-30,-30,-50
};
/*
__host__ __device__ static short Kings[64];
__host__ __device__ static short Queens[64];
__host__ __device__ static short Rooks[64];
__host__ __device__ static short Bishops[64];
__host__ __device__ static short Knights[64];
__host__ __device__ static short Pawns[64];
*/


__global__ void evaluate_board_kernel(Square* squares, bool endGamePhase, int* result) 
{	
	/*
	__shared__ short PawnTable[64];
	__shared__ short KnightTable[64];
	__shared__ short BishopTable[64];
	__shared__ short KingTable[64];
	__shared__ short KingTableEndGame[64];
	*/
		__shared__ int score[64];

		int index = threadIdx.x;
		int position = index;
		/*
		PawnTable[index] = PawnTableGPU[index];
		KnightTable[index] = KnightTableGPU[index];
		BishopTable[index] = BishopTableGPU[index];
		KingTable[index] = KingTableGPU[index];
		KingTableEndGame[index] = KingTableEndGameGPU[index];
		*/
	{
		if (squares[index].Piece1.PieceColor == ChessPieceColor::Black)
		{
			position = (63 - index);
		}

		if (squares[index].Piece1.PieceType == ChessPieceType::None)
		{
			score[index] = 0;
			//printf("Assigned to index %d value %d\n", index, score[index]);
		}
		else {

			//Calculate Piece Values
			score[index] += squares[index].Piece1.PieceValue;
			//printf("first assignment: %d\n", score[index]);
			score[index] += squares[index].Piece1.DefendedValue;
			//printf("second assignment: %d\n", score[index]);
			score[index] -= squares[index].Piece1.AttackedValue;
			//printf("third assignment: %d\n", score[index]);

			//Double Penalty for Hanging Pieces
			if (squares[index].Piece1.DefendedValue < squares[index].Piece1.AttackedValue)
			{
				score[index] -= ((squares[index].Piece1.AttackedValue - squares[index].Piece1.DefendedValue) * 10);
				//printf("forth assignment: %d\n", score[index]);
			}

			//Add Points for Mobility
			/*
			if (!squares[index].Piece1.ValidMoves.empty())
			{
				score[index] += squares[index].Piece1.ValidMoves.size();
			}
			*/

			// LastValidMoveCount is not always initialized!!!! So it gives error somethimes
			//score[index] += squares[index].Piece1.LastValidMoveCount;
			//printf("fifth assignment: %d\n", score[index]);

			if (squares[index].Piece1.PieceType == ChessPieceType::Pawn)
			{

				if (index % 8 == 0 || index % 8 == 7)
				{
					//Rook Pawns are worth 15% less because they can only attack one way
					score[index] -= 15;
					//printf("sixht assignment: %d\n", score[index]);
				}

				//Calculate Position Values
				score[index] += PawnTableGPU[position];
				//printf("seventh assignment: %d\n", score[index]);
			}
			else if (squares[index].Piece1.PieceType == ChessPieceType::Knight)
			{
				//*knightCount = (knightCount);

				score[index] += KnightTableGPU[position];

				//In the end game remove a few points for Knights since they are worth less
				if (endGamePhase)
				{
					score[index] -= 10;
				}

			}
			else if (squares[index].Piece1.PieceType == ChessPieceType::Bishop)
			{
				//In the end game Bishops are worth more
				if (endGamePhase)
				{
					score[index] += 10;
				}

				score[index] += BishopTableGPU[position];
			}
			else if (squares[index].Piece1.PieceType == ChessPieceType::Queen)
			{
				if (squares[index].Piece1.Moved && !endGamePhase)
				{
					score[index] -= 10;
				}
			}
			else if (squares[index].Piece1.PieceType == ChessPieceType::King)
			{
				/*
				if (!squares[index].Piece1.ValidMoves.empty())
				{
					if (squares[index].Piece1.ValidMoves.size() < 2)
					{
						score[index] -= 5;
					}
				}
				*/
				if (squares[index].Piece1.LastValidMoveCount < 2)
				{
					score[index] -= 5;
				}

				if (endGamePhase)
				{
					score[index] += KingTableEndGameGPU[position];
				}
				else
				{
					score[index] += KingTableGPU[position];
				}
			}
			if (squares[index].Piece1.PieceColor == ChessPieceColor::Black) {
				score[index] = -score[index];
			}
		}
		//printf("Ended node: %d\n", index);
	}

	//__shared__ int results[64];
	//results[index] = score[index];
	__syncthreads();
	/*
	{
		//printf("Score from index %d is %d\n", index, score[index]);
		for (int stride = 32; stride > 0; stride >>= 1) {
			//__syncthreads();
			if (index < stride) {
				score[index] = score[index] + score[index + stride];
				//printf("Score from index %d is %d\n", index, score[index]);
			}
			__syncthreads();
		}

		result[0] = score[0];

	}
	*/
	
	sum_matrix << <1, 64 >> >(score);

}

__global__ void evaluate_board_kernel_v2(int endGamePhase, int* score, short* Kings, short* Queens, short* Rooks, short* Bishops, short* Knights, short* Pawns)
{
	__shared__ short PawnScore[64];
	__shared__ short KnightScore[64];
	__shared__ short BishopScore[64];
	__shared__ short RookScore[64];
	__shared__ short QueenScore[64];
	__shared__ short KingScore[64];
	__shared__ short KingScoreEndGame[64];

	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int position_w = index;
	int position_b = 63 - index;

	
	PawnScore[index] = Pawns[position_w];
	PawnScore[index] -= Pawns[position_b];
	PawnScore[index] = PawnScore[index] * Pawns[index];

	KnightScore[index] = Knights[position_w];
	KnightScore[index] -= Knights[position_b];
	KnightScore[index] = KnightScore[index] * Knights[index];

	BishopScore[index] = Bishops[position_w];
	BishopScore[index] -= Bishops[position_b];
	BishopScore[index] = BishopScore[index] * Bishops[index];

	RookScore[index] = Rooks[index];

	QueenScore[index] = Queens[index];

	KingScore[index] = Kings[position_w];
	KingScore[index] -= Kings[position_b];
	KingScore[index] = KingScore[index] * Kings[index];
	/*
	KingScoreEndGame[index] = Kings[position_w];
	KingScoreEndGame[index] -= Kings[position_b];
	KingScoreEndGame[index] = KingScoreEndGame[index] * Kings[index] * endGamePhase;


	score[index] = PawnScore[index] + KnightScore[index] + BishopScore[index] + RookScore[index] + QueenScore[index] + KingScore[index] + KingScoreEndGame[index];


	/*
	if (squares[index].Piece1.PieceType == ChessPieceType::None)
	{
		score[index] = 0;
	}
	else {

		//Calculate Piece Values
		score[index] += squares[index].Piece1.PieceValue;
		//printf("first assignment: %d\n", score[index]);
		score[index] += squares[index].Piece1.DefendedValue;
		//printf("second assignment: %d\n", score[index]);
		score[index] -= squares[index].Piece1.AttackedValue;
		//printf("third assignment: %d\n", score[index]);

		//Double Penalty for Hanging Pieces
		if (squares[index].Piece1.DefendedValue < squares[index].Piece1.AttackedValue)
		{
			score[index] -= ((squares[index].Piece1.AttackedValue - squares[index].Piece1.DefendedValue) * 10);
			//printf("forth assignment: %d\n", score[index]);
		}

		//Add Points for Mobility
		/*
		if (!squares[index].Piece1.ValidMoves.empty())
		{
			score[index] += squares[index].Piece1.ValidMoves.size();
		}
		*/

		// LastValidMoveCount is not always initialized!!!! So it gives error somethimes
		//score[index] += squares[index].Piece1.LastValidMoveCount;
		//printf("fifth assignment: %d\n", score[index]);
		/*
		if (squares[index].Piece1.PieceType == ChessPieceType::Pawn)
		{

			if (index % 8 == 0 || index % 8 == 7)
			{
				//Rook Pawns are worth 15% less because they can only attack one way
				score[index] -= 15;
				//printf("sixht assignment: %d\n", score[index]);
			}

			//Calculate Position Values
			score[index] += PawnTable[position];
			//printf("seventh assignment: %d\n", score[index]);
		}
		else if (squares[index].Piece1.PieceType == ChessPieceType::Knight)
		{
			//*knightCount = (knightCount);

			score[index] += KnightTable[position];

			//In the end game remove a few points for Knights since they are worth less
			if (endGamePhase)
			{
				score[index] -= 10;
			}

		}
		else if (squares[index].Piece1.PieceType == ChessPieceType::Bishop)
		{
			//In the end game Bishops are worth more
			if (endGamePhase)
			{
				score[index] += 10;
			}

			score[index] += BishopTable[position];
		}
		else if (squares[index].Piece1.PieceType == ChessPieceType::Queen)
		{
			if (squares[index].Piece1.Moved && !endGamePhase)
			{
				score[index] -= 10;
			}
		}
		else if (squares[index].Piece1.PieceType == ChessPieceType::King)
		{
			/*
			if (!squares[index].Piece1.ValidMoves.empty())
			{
				if (squares[index].Piece1.ValidMoves.size() < 2)
				{
					score[index] -= 5;
				}
			}
			*/
			/*
			if (squares[index].Piece1.LastValidMoveCount < 2)
			{
				score[index] -= 5;
			}

			if (endGamePhase)
			{
				score[index] += KingTableEndGame[position];
			}
			else
			{
				score[index] += KingTable[position];
			}
		}
		if (squares[index].Piece1.PieceColor == ChessPieceColor::Black) {
			score[index] = -score[index];
		}
	}
	*/
	//printf("Ended node: %d\n", index);
	

}

namespace EvaluatePieces {

	void EvaluatePiecesCuda(Board& board) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		//Black Score - 
		//White Score +
		/*
		short Kings[64];
		short Queens[64];
		short Rooks[64];
		short Bishops[64];
		short Knights[64];
		short Pawns[64];

		for (int i = 0; i < 64; ++i) {
			Kings[i] = 0;
			Queens[i] = 0;
			Rooks[i] = 0;
			Bishops[i] = 0;
			Knights[i] = 0;
			Pawns[i] = 0;

			switch (board.Squares[i].Piece1.PieceType) {
			case ChessPieceType::King:
				Kings[i] = board.Squares[i].Piece1.PieceValue / abs(board.Squares[i].Piece1.PieceValue);
				break;
			case ChessPieceType::Queen:
				Queens[i] = board.Squares[i].Piece1.PieceValue / abs(board.Squares[i].Piece1.PieceValue);
				break;
			case ChessPieceType::Rook:
				Rooks[i] = board.Squares[i].Piece1.PieceValue / abs(board.Squares[i].Piece1.PieceValue);
				break;
			case ChessPieceType::Bishop:
				Bishops[i] = board.Squares[i].Piece1.PieceValue / abs(board.Squares[i].Piece1.PieceValue);
				break;
			case ChessPieceType::Knight:
				Knights[i] = board.Squares[i].Piece1.PieceValue / abs(board.Squares[i].Piece1.PieceValue);
				break;
			case ChessPieceType::Pawn:
				Pawns[i] = board.Squares[i].Piece1.PieceValue / abs(board.Squares[i].Piece1.PieceValue);
				break;
			}
		}
		*/

		board.Score = 0;
		board.InsufficientMaterial = false;             // temporary, until not fixed how to assume if it is true
		
		/*

		char blackBishopCount = 0;
		char whiteBishopCount = 0;

		char blackKnightCount = 0;
		char whiteKnightCount = 0;


		char knightCount = 0;
		*/

		//fill_n(blackPawnCount, 8, 0);
		//blackPawnCount = new short[8];
		//whitePawnCount = new short[8];

		// for now also not including pawns computations until we find a way that does not include iterating over whole board (or we may add it later on CPU only)

		/*

		short blackPawnCount[8];
		short whitePawnCount[8];
		for (int i = 0; i < 8; i++) {
			blackPawnCount[i] = 0;
			whitePawnCount[i] = 0;
		}

		*/

		// add cuda below

		// needed structures and objects:
		// Square class needs in fact Piece class, and two enum types ChessPieceColor, ChessPieceType
		// board score propably will be replaced as 64 element int pointer for score, and bool for EndGamePhase, after cuda we will assign each board its score
		// EvaluatePieceScore2 seems to have only regular data types
		// CheckPawnWall functions have to many if instructions, for now will not include them in evaluation results

		/*
		for (int x = 0; x < 64; x++)
		{
			Square square = board.Squares[x];

			if (square.Piece1.PieceType == ChessPieceType::None)
			{
				continue;       // TODO: is it really necessary here? Does nothing i guess
			}


			if (square.Piece1.PieceColor == ChessPieceColor::White)
			{
				board.Score += EvaluatePieceScore2(square, x, board.EndGamePhase,
					whiteKnightCount, whiteBishopCount, insufficientMaterial, blackPawnCount, whitePawnCount);

				if (square.Piece1.PieceType == ChessPieceType::King)
				{
					if (x != 59 && x != 60)
					{
						int pawnPos = x - 8;

						board.Score += CheckPawnWall2(board, pawnPos, x);

						pawnPos = x - 7;

						board.Score += CheckPawnWall2(board, pawnPos, x);

						pawnPos = x - 9;

						board.Score += CheckPawnWall2(board, pawnPos, x);
					}
				}
			}
			else if (square.Piece1.PieceColor == ChessPieceColor::Black)
			{
				board.Score -= EvaluatePieceScore2(square, x, board.EndGamePhase,
					blackKnightCount, blackBishopCount, insufficientMaterial, blackPawnCount, whitePawnCount);


				if (square.Piece1.PieceType == ChessPieceType::King)
				{
					if (x != 3 && x != 4)
					{
						int pawnPos = x + 8;

						board.Score -= CheckPawnWall2(board, pawnPos, x);

						pawnPos = x + 7;

						board.Score -= CheckPawnWall2(board, pawnPos, x);

						pawnPos = x + 9;

						board.Score -= CheckPawnWall2(board, pawnPos, x);
					}

				}

			}

			if (square.Piece1.PieceType == ChessPieceType::Knight)
			{
				knightCount = (knightCount + 1);

				if (knightCount > 1)
				{
					insufficientMaterial = false;
				}
			}

			if ((blackBishopCount + whiteBishopCount) > 1)
			{
				insufficientMaterial = false;
			}
			else if ((blackBishopCount + blackKnightCount) > 1)
			{
				insufficientMaterial = false;
			}
			else if ((whiteBishopCount + whiteKnightCount) > 1)
			{
				insufficientMaterial = false;
			}

		}

		// until that point
		*/

		// not including insufficientMaterial for now, gotta calculate it outside GPU
		/*
		if (insufficientMaterial)
		{
			board.Score = 0;
			board.StaleMate = true;
			board.InsufficientMaterial = true;
			return;
		}
		*/
		int* d_score;
		int* score = (int*)malloc(sizeof(int));
		/*
		short* d_Kings;
		short* d_Queens;
		short* d_Rooks;
		short* d_Bishops;
		short* d_Knights;
		short* d_Pawns;
		*/
		//short* d_PawnTable;
		Square* d_squares;
		

		cudaMalloc(&d_score, sizeof(int));
		cudaMalloc(&d_squares, sizeof(board.Squares));
		/*
		cudaMalloc(&d_Kings, 64 * sizeof(short));
		cudaMalloc(&d_Queens, 64 * sizeof(short));
		cudaMalloc(&d_Rooks, 64 * sizeof(short));
		cudaMalloc(&d_Bishops, 64 * sizeof(short));
		cudaMalloc(&d_Knights, 64 * sizeof(short));
		cudaMalloc(&d_Pawns, 64 * sizeof(short));
		*/

		cudaMemcpy(d_squares, board.Squares, sizeof(board.Squares), cudaMemcpyHostToDevice);
		/*
		cudaMemcpy(d_Kings, Kings, 64 * sizeof(short), cudaMemcpyHostToDevice);
		cudaMemcpy(d_Queens, Queens, 64 * sizeof(short), cudaMemcpyHostToDevice);
		cudaMemcpy(d_Rooks, Rooks, 64 * sizeof(short), cudaMemcpyHostToDevice);
		cudaMemcpy(d_Bishops, Bishops, 64 * sizeof(short), cudaMemcpyHostToDevice);
		cudaMemcpy(d_Knights, Knights, 64 * sizeof(short), cudaMemcpyHostToDevice);
		cudaMemcpy(d_Pawns, Pawns, 64 * sizeof(short), cudaMemcpyHostToDevice);
		*/

		/*
		int late_game = 0;
		if (board.EndGamePhase) {
			late_game = 1;
		}
		*/

		evaluate_board_kernel << <1, 64 >> > (d_squares, board.EndGamePhase, d_score);
		//evaluate_board_kernel_v2 << <1, 64 >> > (late_game, d_score, d_Kings, d_Queens, d_Rooks, d_Bishops, d_Knights, d_Pawns);
		cudaMemcpy(score, d_score, sizeof(int), cudaMemcpyDeviceToHost);
		cudaDeviceSynchronize();
		if (board.StaleMate)
		{
			return;
		}
		if (board.HalfMoveClock >= 100)
		{
			return;
		}
		if (board.RepeatedMove >= 3)
		{
			return;
		}
		if (board.BlackMate)
		{
			board.Score = 32767;
			return;
		}
		if (board.WhiteMate)
		{
			board.Score = -32767;
			return;
		}
		if (board.BlackCheck)
		{
			board.Score += 70;
			if (board.EndGamePhase)
				board.Score += 10;
		}
		else if (board.WhiteCheck)
		{
			board.Score -= 70;
			if (board.EndGamePhase)
				board.Score -= 10;
		}
		if (board.BlackCastled)
		{
			board.Score -= 50;
		}
		if (board.WhiteCastled)
		{
			board.Score += 50;
		}
		//Add a small bonus for tempo (turn)
		if (board.WhoseMove == ChessPieceColor::White)
		{
			board.Score += 10;
		}
		else
		{
			board.Score -= 10;
		}
		if (board.EndGamePhase)
		{
			if (board.BlackCheck)
			{
				board.Score += 10;
			}
			else if (board.WhiteCheck)
			{
				board.Score -= 10;
			}
		}
		else
		{
			if (!board.WhiteCanCastle && !board.WhiteCastled)
			{
				board.Score -= 50;
			}
			if (!board.BlackCanCastle && !board.BlackCastled)
			{
				board.Score += 50;
			}
		}
		//board.Score = *score;
		//for (int i = 0; i < 64; ++i) {
			//board.Score += score[i];
			//printf("Score from i: %d is: %d\n", i, score[i]);
		//}
		board.Score = *score;
		/*
		//Black Isolated Pawns
		if (blackPawnCount[0] >= 1 && blackPawnCount[1] == 0)
		{
			board.Score += 12;
		}
		if (blackPawnCount[1] >= 1 && blackPawnCount[0] == 0 &&
			blackPawnCount[2] == 0)
		{
			board.Score += 14;
		}
		if (blackPawnCount[2] >= 1 && blackPawnCount[1] == 0 &&
			blackPawnCount[3] == 0)
		{
			board.Score += 16;
		}
		if (blackPawnCount[3] >= 1 && blackPawnCount[2] == 0 &&
			blackPawnCount[4] == 0)
		{
			board.Score += 20;
		}
		if (blackPawnCount[4] >= 1 && blackPawnCount[3] == 0 &&
			blackPawnCount[5] == 0)
		{
			board.Score += 20;
		}
		if (blackPawnCount[5] >= 1 && blackPawnCount[4] == 0 &&
			blackPawnCount[6] == 0)
		{
			board.Score += 16;
		}
		if (blackPawnCount[6] >= 1 && blackPawnCount[5] == 0 &&
			blackPawnCount[7] == 0)
		{
			board.Score += 14;
		}
		if (blackPawnCount[7] >= 1 && blackPawnCount[6] == 0)
		{
			board.Score += 12;
		}

		//White Isolated Pawns
		if (whitePawnCount[0] >= 1 && whitePawnCount[1] == 0)
		{
			board.Score -= 12;
		}
		if (whitePawnCount[1] >= 1 && whitePawnCount[0] == 0 &&
			whitePawnCount[2] == 0)
		{
			board.Score -= 14;
		}
		if (whitePawnCount[2] >= 1 && whitePawnCount[1] == 0 &&
			whitePawnCount[3] == 0)
		{
			board.Score -= 16;
		}
		if (whitePawnCount[3] >= 1 && whitePawnCount[2] == 0 &&
			whitePawnCount[4] == 0)
		{
			board.Score -= 20;
		}
		if (whitePawnCount[4] >= 1 && whitePawnCount[3] == 0 &&
			whitePawnCount[5] == 0)
		{
			board.Score -= 20;
		}
		if (whitePawnCount[5] >= 1 && whitePawnCount[4] == 0 &&
			whitePawnCount[6] == 0)
		{
			board.Score -= 16;
		}
		if (whitePawnCount[6] >= 1 && whitePawnCount[5] == 0 &&
			whitePawnCount[7] == 0)
		{
			board.Score -= 14;
		}
		if (whitePawnCount[7] >= 1 && whitePawnCount[6] == 0)
		{
			board.Score -= 12;
		}

		//Black Passed Pawns
		if (blackPawnCount[0] >= 1 && whitePawnCount[0] == 0)
		{
			board.Score -= blackPawnCount[0];
		}
		if (blackPawnCount[1] >= 1 && whitePawnCount[1] == 0)
		{
			board.Score -= blackPawnCount[1];
		}
		if (blackPawnCount[2] >= 1 && whitePawnCount[2] == 0)
		{
			board.Score -= blackPawnCount[2];
		}
		if (blackPawnCount[3] >= 1 && whitePawnCount[3] == 0)
		{
			board.Score -= blackPawnCount[3];
		}
		if (blackPawnCount[4] >= 1 && whitePawnCount[4] == 0)
		{
			board.Score -= blackPawnCount[4];
		}
		if (blackPawnCount[5] >= 1 && whitePawnCount[5] == 0)
		{
			board.Score -= blackPawnCount[5];
		}
		if (blackPawnCount[6] >= 1 && whitePawnCount[6] == 0)
		{
			board.Score -= blackPawnCount[6];
		}
		if (blackPawnCount[7] >= 1 && whitePawnCount[7] == 0)
		{
			board.Score -= blackPawnCount[7];
		}

		//White Passed Pawns
		if (whitePawnCount[0] >= 1 && blackPawnCount[1] == 0)
		{
			board.Score += whitePawnCount[0];
		}
		if (whitePawnCount[1] >= 1 && blackPawnCount[1] == 0)
		{
			board.Score += whitePawnCount[1];
		}
		if (whitePawnCount[2] >= 1 && blackPawnCount[2] == 0)
		{
			board.Score += whitePawnCount[2];
		}
		if (whitePawnCount[3] >= 1 && blackPawnCount[3] == 0)
		{
			board.Score += whitePawnCount[3];
		}
		if (whitePawnCount[4] >= 1 && blackPawnCount[4] == 0)
		{
			board.Score += whitePawnCount[4];
		}
		if (whitePawnCount[5] >= 1 && blackPawnCount[5] == 0)
		{
			board.Score += whitePawnCount[5];
		}
		if (whitePawnCount[6] >= 1 && blackPawnCount[6] == 0)
		{
			board.Score += whitePawnCount[6];
		}
		if (whitePawnCount[7] >= 1 && blackPawnCount[7] == 0)
		{
			board.Score += whitePawnCount[7];
		}
		*/
		//std::cout << "Score from cuda evaluation is : " << board.Score << std::endl;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		time_cuda = time_cuda + std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		count_positions = count_positions + 1;
		if (min_time > std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) {
			min_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		}
		if (max_time < std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() && std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() < 160000) {
			max_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		}
		std::cout << "Time difference gpu = " << time_cuda << "[µs], positions counted: " << count_positions << ", min time: " << min_time << ", max time: " << max_time << " board score: " << board.Score << std::endl;
		cudaFree(d_squares), cudaFree(d_score); 
		//cudaFree(d_Kings), cudaFree(d_Queens), cudaFree(d_Rooks), cudaFree(d_Bishops), cudaFree(d_Knights), cudaFree(d_Pawns);
		//cudaFree(d_PawnTable);
	}
}