#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"

using namespace std;

struct PieceMoveSet {
    list<char> Moves;
    PieceMoveSet(list<char> moves);

    PieceMoveSet();
};

struct MoveArrays
{
    inline static PieceMoveSet BishopMoves1[64];
    inline static char BishopTotalMoves1[64];

    inline static PieceMoveSet BishopMoves2[64];
    inline static char BishopTotalMoves2[64];

    inline static PieceMoveSet BishopMoves3[64];
    inline static char BishopTotalMoves3[64];

    inline static PieceMoveSet BishopMoves4[64];
    inline static char BishopTotalMoves4[64];

    inline static PieceMoveSet BlackPawnMoves[64];
    inline static char BlackPawnTotalMoves[64];

    inline static PieceMoveSet WhitePawnMoves[64];
    inline static char WhitePawnTotalMoves[64];

    inline static PieceMoveSet KnightMoves[64];
    inline static char KnightTotalMoves[64];

    inline static PieceMoveSet QueenMoves1[64];
    inline static char QueenTotalMoves1[64];
    inline static PieceMoveSet QueenMoves2[64];
    inline static char QueenTotalMoves2[64];
    inline static PieceMoveSet QueenMoves3[64];
    inline static char QueenTotalMoves3[64];
    inline static PieceMoveSet QueenMoves4[64];
    inline static char QueenTotalMoves4[64];
    inline static PieceMoveSet QueenMoves5[64];
    inline static char QueenTotalMoves5[64];
    inline static PieceMoveSet QueenMoves6[64];
    inline static char QueenTotalMoves6[64];
    inline static PieceMoveSet QueenMoves7[64];
    inline static char QueenTotalMoves7[64];
    inline static PieceMoveSet QueenMoves8[64];
    inline static char QueenTotalMoves8[64];

    inline static PieceMoveSet RookMoves1[64];
    inline static char RookTotalMoves1[64];
    inline static PieceMoveSet RookMoves2[64];
    inline static char RookTotalMoves2[64];
    inline static PieceMoveSet RookMoves3[64];
    inline static char RookTotalMoves3[64];
    inline static PieceMoveSet RookMoves4[64];
    inline static char RookTotalMoves4[64];

    inline static PieceMoveSet KingMoves[64];
    inline static char KingTotalMoves[64];
};

class PieceMoves
{
public:
    inline static bool Initiated;

    static char Position(char col, char row);

    //#region IntitiateMotionMethods

    static void InitiateChessPieceMotion();

    static void SetMovesBlackPawn();
    
private:
    static void SetMovesWhitePawn();

    static void SetMovesKnight();

    static void SetMovesBishop();

    static void SetMovesRook();

    static void SetMovesQueen();

    static void SetMovesKing();

    //#endregion
};