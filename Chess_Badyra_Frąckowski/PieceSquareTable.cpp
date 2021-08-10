#include <string>
#include <list>
#include <stack>
#include "PieceSquareTable.h"
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"
//#include "Square.h"

using namespace std;

int PieceSquareTable::EvaluatePiecePosition(ChessPieceType PieceType,
                                            ChessPieceColor PieceColor,
                                            byte position, bool endGame)
{
    switch (PieceColor)
    {
    case ChessPieceColor::White:
            if (PieceType == ChessPieceType::Pawn)
            {
                if (endGame)
                {
                    return PawnTableEndGame[(short)position];
                }

                return PawnTable[(short)position];
            }
            if (PieceType == ChessPieceType::Knight)
            {
                return KnightTable[(short)position];
            }
            if (PieceType == ChessPieceType::Bishop)
            {
                return BishopTable[(short)position];
            }
            if (PieceType == ChessPieceType::Rook)
            {
                return RookTable[(short)position];
            }
            if (PieceType == ChessPieceType::Queen)
            {
                return QueenTable[(short)position];
            }
            if (PieceType == ChessPieceType::King)
            {
                if (endGame)
                {
                    return KingEndGameTable[(short)position];
                }

                return KingMiddleGameTable[(short)position];
            }
            break;
    case ChessPieceColor::Black:

            byte index = (byte)((((short)position + 56)) - (((short)position / 8) * 16));

            if (PieceType == ChessPieceType::Pawn)
            {
                if (endGame)
                {
                    return PawnTableEndGame[(short)index];
                }

                return PawnTable[(short)index];
            }
            if (PieceType == ChessPieceType::Knight)
            {
                return KnightTable[(short)index];
            }
            if (PieceType == ChessPieceType::Bishop)
            {
                return BishopTable[(short)index];
            }
            if (PieceType == ChessPieceType::Rook)
            {
                return RookTable[(short)index];
            }
            if (PieceType == ChessPieceType::Queen)
            {
                return QueenTable[(short)index];
            }
            if (PieceType == ChessPieceType::King)
            {
                if (endGame)
                {
                    return KingEndGameTable[(short)index];
                }

                return KingMiddleGameTable[(short)index];
            }
            break;
    }

    return 0;
}



int PieceSquareTable::EvaluatePawnWhitePosition(byte position, bool endGame)
{
    if (endGame)
    {
        return PawnTableEndGame[(short)position];
    }

    return PawnTable[(short)position];
}

int PieceSquareTable::EvaluatePawnBlackPosition(byte position, bool endGame)
{
    byte index = (byte)((((short)position + 56)) - (((short)position / 8) * 16));

    if (endGame)
    {
        return PawnTableEndGame[(short)index];
    }

    return PawnTable[(short)index];
}
