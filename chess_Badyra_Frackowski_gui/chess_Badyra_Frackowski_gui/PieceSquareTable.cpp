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
                                            char position, bool endGame)
{
    switch (PieceColor)
    {
    case ChessPieceColor::White:
            if (PieceType == ChessPieceType::Pawn)
            {
                if (endGame)
                {
                    return PawnTableEndGame[position];
                }

                return PawnTable[position];
            }
            if (PieceType == ChessPieceType::Knight)
            {
                return KnightTable[position];
            }
            if (PieceType == ChessPieceType::Bishop)
            {
                return BishopTable[position];
            }
            if (PieceType == ChessPieceType::Rook)
            {
                return RookTable[position];
            }
            if (PieceType == ChessPieceType::Queen)
            {
                return QueenTable[position];
            }
            if (PieceType == ChessPieceType::King)
            {
                if (endGame)
                {
                    return KingEndGameTable[position];
                }

                return KingMiddleGameTable[position];
            }
            break;
    case ChessPieceColor::Black:

            char index = (((position + 56)) - ((position / 8) * 16));

            if (PieceType == ChessPieceType::Pawn)
            {
                if (endGame)
                {
                    return PawnTableEndGame[index];
                }

                return PawnTable[index];
            }
            if (PieceType == ChessPieceType::Knight)
            {
                return KnightTable[index];
            }
            if (PieceType == ChessPieceType::Bishop)
            {
                return BishopTable[index];
            }
            if (PieceType == ChessPieceType::Rook)
            {
                return RookTable[index];
            }
            if (PieceType == ChessPieceType::Queen)
            {
                return QueenTable[index];
            }
            if (PieceType == ChessPieceType::King)
            {
                if (endGame)
                {
                    return KingEndGameTable[index];
                }

                return KingMiddleGameTable[index];
            }
            break;
    }

    return 0;
}



int PieceSquareTable::EvaluatePawnWhitePosition(char position, bool endGame)
{
    if (endGame)
    {
        return PawnTableEndGame[position];
    }

    return PawnTable[position];
}

int PieceSquareTable::EvaluatePawnBlackPosition(char position, bool endGame)
{
    char index = (((position + 56)) - ((position / 8) * 16));

    if (endGame)
    {
        return PawnTableEndGame[index];
    }

    return PawnTable[index];
}
