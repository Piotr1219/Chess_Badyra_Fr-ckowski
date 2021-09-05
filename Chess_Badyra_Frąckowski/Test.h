#pragma once
#include <string>
#include <list>
#include <stack>
#include <assert.h>
#include <ctime>
#include "Engine.h"
///#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
#include "Evaluations.h"
#include "Evaluations2.h"
//#include "Square.h"
#include "ResultBoards.h"
#include "PieceValidMoves.h"
//#include "Search.h"

using namespace std;

class CorrectnessTest
{
public:
	void RunAllCorrectnessTests();

	//[Test]
	void TestBlankBoard();

	//[Test]
	void TestStandardBoardShortFEN();

	//[Test]
	void TestStandardBoardFullFEN();

	//[Test]
	void TestBoardOrientation();

	//[Test]
	void TestNotation();

	//[Test]
	void TestValidMoves();

	//[Test]
	void TestSimpleMoves();

	//[Test]
	void Test50MoveRule();

	//[Test]
	void TestRealGame();

	//[Test]
	void TestAI();
};

class PerformanceTest
{
	struct PerformanceResult
	{
	public:
		int Depth;
		long Nodes;
		time_t TimeSpan;
	};
private:
	//ResultBoards resultBoards = ResultBoards();
	//resultBoards.Positions = list<Board>();

	static ChessPieceColor GetOppositeColor(ChessPieceColor color);

	static int SideToMoveScore(int score, ChessPieceColor color);

	static PerformanceResult RunPerfTest(int depth, Board board);

	static long Performance(int depth, Board board, ChessPieceColor color);

	static ResultBoards GetPossibleBoards(ChessPieceColor movingSide, Board examineBoard);

};
