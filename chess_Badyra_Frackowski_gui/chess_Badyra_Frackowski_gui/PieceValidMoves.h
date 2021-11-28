#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
#include "PieceMoves.h"
#include "Board.h"


using namespace std;

class PieceValidMoves
{
public:
    static void AnalyzeMovePawn(Board& board, char dstPos, Piece& pcMoving);

    static bool AnalyzeMove(Board& board, char dstPos, Piece& pcMoving);

    static void CheckValidMovesPawn(list<char> moves, Piece& pcMoving, char srcPosition,
        Board& board, char count);

    static void GenerateValidMovesKing(Piece& piece, Board& board, char srcPosition);

    static void GenerateValidMovesKingCastle(Board& board, Piece& king);

    static void GenerateValidMoves(Board& board);
};
