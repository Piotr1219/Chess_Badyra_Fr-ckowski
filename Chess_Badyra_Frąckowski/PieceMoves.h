#include <string>
#include <list>
#include <stack>
#include "Engine.h"
#include "Board.h"
#include "Book.h"
#include "main.h"
#include "functions.h"
#include "MoveContent.h"
#include "Piece.h"
#include "Evaluations.h"
#include "PGN.h"

using namespace std;

struct PieceMoveSet {
    list<byte> Moves;
    PieceMoveSet(list<byte> moves);
    //PieceMoveSet();
};

struct MoveArrays
{
    static PieceMoveSet BishopMoves1[64];
    static byte BishopTotalMoves1[64];

    static PieceMoveSet BishopMoves2[64];
    static byte BishopTotalMoves2[64];

    static PieceMoveSet BishopMoves3[64];
    static byte BishopTotalMoves3[64];

    static PieceMoveSet BishopMoves4[64];
    static byte BishopTotalMoves4[64];

    static PieceMoveSet BlackPawnMoves[64];
    static byte BlackPawnTotalMoves[64];

    static PieceMoveSet WhitePawnMoves[64];
    static byte WhitePawnTotalMoves[64];

    static PieceMoveSet KnightMoves[64];
    static byte KnightTotalMoves[64];

    static PieceMoveSet QueenMoves1[64];
    static byte QueenTotalMoves1[64];
    static PieceMoveSet QueenMoves2[64];
    static byte QueenTotalMoves2[64];
    static PieceMoveSet QueenMoves3[64];
    static byte QueenTotalMoves3[64];
    static PieceMoveSet QueenMoves4[64];
    static byte QueenTotalMoves4[64];
    static PieceMoveSet QueenMoves5[64];
    static byte QueenTotalMoves5[64];
    static PieceMoveSet QueenMoves6[64];
    static byte QueenTotalMoves6[64];
    static PieceMoveSet QueenMoves7[64];
    static byte QueenTotalMoves7[64];
    static PieceMoveSet QueenMoves8[64];
    static byte QueenTotalMoves8[64];

    static PieceMoveSet RookMoves1[64];
    static byte RookTotalMoves1[64];
    static PieceMoveSet RookMoves2[64];
    static byte RookTotalMoves2[64];
    static PieceMoveSet RookMoves3[64];
    static byte RookTotalMoves3[64];
    static PieceMoveSet RookMoves4[64];
    static byte RookTotalMoves4[64];

    static PieceMoveSet KingMoves[64];
    static byte KingTotalMoves[64];
};

class PieceMoves
{
    static bool Initiated;

    static byte Position(byte col, byte row);

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