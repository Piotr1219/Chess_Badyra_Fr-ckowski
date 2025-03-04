#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
#include "Square.h"

using namespace std;

//short blackPawnCount[8];
//short whitePawnCount[8];

const short PawnTable[64] =
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

const short KnightTable[64] =
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

const short BishopTable[64] =
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

const short KingTable[64] =
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

const short KingTableEndGame[64] =
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

int EvaluatePieceScore2(Square square, char position, bool endGamePhase,
    char& knightCount, char& bishopCount, bool& insufficientMaterial, short (&blackPawnCount)[8], short (&whitePawnCount)[8]);

void EvaluateBoardScore2(Board& board);

int CheckPawnWall2(Board board, int pawnPos, int kingPos);
