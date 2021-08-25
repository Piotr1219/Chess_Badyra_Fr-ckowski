#pragma once
#include "Book.h"
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
///#include "Board.h"
//#include "main.h"
//#include "functions.h"
///#include "MoveContent.h"
//#include "Piece.h"
#include "Evaluations.h"
//#include "Square.h"
#include "ResultBoards.h"
#include "PieceValidMoves.h"

using namespace std;

struct Position
{
    byte SrcPosition;
    byte DstPosition;
    int Score;
    //internal bool TopSort;
    string Move;
public:
    string ToString();
};

bool Sort(Position s2, Position s1);

static class Search
{
    static int progress;

private:
    static int piecesRemaining;




private:
    //static Position KillerMove[][] = Position[3,20];
    static Position KillerMove[3][20];
    static int kIndex;

//    struct sortComparator {
  //      bool operator () (Board& s2, Board& s1);
    //};
    //bool Sort(Board & s2, Board & s1);

    static int SideToMoveScore(int score, ChessPieceColor color);
public:
    static MoveContent IterativeSearch(Board examineBoard, byte depth, int* nodesSearched, int* nodesQuiessence, string pvLine, byte* plyDepthReached, byte* rootMovesSearched, list<OpeningMove> currentGameBook);

private:
    static ResultBoards GetSortValidMoves(Board examineBoard);

    static int AlphaBeta(Board examineBoard, byte depth, int alpha, int beta, int* nodesSearched, int* nodesQuiessence, list<Position>* pvLine, bool extended);

    static int Quiescence(Board examineBoard, int alpha, int beta, int* nodesSearched);

    static list<Position> EvaluateMoves(Board examineBoard, byte depth);

    static list<Position> EvaluateMovesQ(Board examineBoard);
public:
    static bool SearchForMate(ChessPieceColor movingSide, Board examineBoard, bool* blackMate, bool* whiteMate, bool* staleMate);
private:
    static byte ModifyDepth(byte depth, int possibleMoves);

    static int StaticExchangeEvaluation(Square examineSquare);

};

