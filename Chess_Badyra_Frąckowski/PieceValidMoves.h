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
    static void AnalyzeMovePawn(Board board, byte dstPos, Piece pcMoving);

    static bool AnalyzeMove(Board board, byte dstPos, Piece pcMoving);

    static void CheckValidMovesPawn(list<byte> moves, Piece pcMoving, byte srcPosition,
        Board board, byte count);

    static void GenerateValidMovesKing(Piece piece, Board board, byte srcPosition);

    static void GenerateValidMovesKingCastle(Board board, Piece king);

    static void GenerateValidMoves(Board board);
};
