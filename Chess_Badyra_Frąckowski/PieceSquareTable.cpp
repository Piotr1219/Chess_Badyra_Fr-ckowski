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
#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"
//#include "Square.h"

using namespace std;


    const short BishopTable[64] = 
    {
            -40, -20, -20, -20, -20, -20, -20, -40 ,
            -20,   0,   0,   0,   0,   0,   0, -20 ,
            -20,   0,  10,  20,  20,  10,   0, -20 ,
            -20,  10,  10,  20,  20,  10,  10, -20 ,
            -20,   0,  20,  20,  20,  20,   0, -20 ,
            -20,  20,  20,  20,  20,  20,  20, -20 ,
            -20,  10,   0,   0,   0,   0,  10, -20 ,
            -40, -20, -20, -20, -20, -20, -20, -40
    };

    const short KingEndGameTable[64] = 
    {
        -175,-175,-175,-175,-175,-175,-175,-175,
        -175, -50, -50, -50, -50, -50, -50,-175,
        -175, -50,  50,  50,  50,  50, -50,-175,
        -175, -50,  50, 150, 150,  50, -50,-175,
        -175, -50,  50, 100, 100,  50, -50,-175,
        -175, -50,  50,  50,  50,  50, -50,-175,
        -175, -50, -50, -50, -50, -50, -50,-175,
        -175,-175,-175,-175,-175,-175,-175,-175
    };

    const short KingMiddleGameTable[64] = 
    {
            -60, -80, -80, -2, -20, -80, -80, -60 ,
            -60, -80, -80, -2, -20, -80, -80, -60 ,
            -60, -80, -80, -2, -20, -80, -80, -60 ,
            -60, -80, -80, -2, -20, -80, -80, -60 ,
            -40, -60, -60, -8, -80, -60, -60, -40 ,
            -20, -40, -40, -40,-40, -40, -40, -20 ,
            40,  40,   0,   0,  0,   0,  40,  40 ,
            40,  60,  20,   0,  0,  20,  60,  40
    };

    const short KnightTable[64] = 
    {
            -20, -80, -60, -60, -60, -60, -80, -20 ,
            -80, -40,   0,   0,   0,   0, -40, -80 ,
            -60,   0,  20,  30,  30,  20,   0, -60 ,
            -60,  10,  30,  40,  40,  30,  10, -60 ,
            -60,   0,  30,  40,  40,  30,   0, -60 ,
            -60,  10,  20,  30,  30,  30,   1, -60 ,
            -80, -40,   0,  10,  10,   0,  -4, -80 ,
            -20, -80, -60, -60, -60, -60, -80, -20 ,
    };

    const short PawnTable[64] = 
    {
        9000,9000,9000,9000,9000,9000,9000,9000 ,
            200, 200, 200, 200, 200, 200, 200, 200 ,
            100, 100, 100, 100, 100, 100, 100, 100 ,
            40,  40,  90, 100, 100,  90,  40,  40 ,
            20,  20,  20, 100, 150,  20,  20,  20 ,
            2,   4,   0,  15,   4,   0,   4,   2 ,
            -10, -10, -10, -20, -35, -10, -10, -10 ,
            0,   0,   0,   0,   0,   0,   0,   0
    };

    const short PawnTableEndGame[64] = 
    {
            9000,9000,9000,9000,9000,9000,9000,9000 ,
            500, 500, 500, 500, 500, 500, 500, 500 ,
            300, 300, 300, 300, 300, 300, 300, 300 ,
            90,  90,  90, 100, 100,  90,  90,  90 ,
            70,  70,  70,  85,  85,  70,  70,  70 ,
            20,  20,  20,  20,  20,  20,  20,  20 ,
            -10, -10, -10, -10, -10, -10, -10, -10 ,
            0,   0,   0,   0,   0,   0,   0,   0
    };

    const short QueenTable[64] = 
    {
            -40, -20, -20, -10, -10, -20, -20, -40 ,
            -20,   0,   0,   0,   0,   0,   0, -20 ,
            -20,   0,  10,  10,  10,  10,   0, -20 ,
            -10,   0,  10,  10,  10,  10,   0, -10 ,
            0,   0,  10,  10,  10,  10,   0, -10 ,
            -20,  10,  10,  10,  10,  10,   0, -20 ,
            -20,   0,  10,   0,   0,   0,   0, -20 ,
            -40, -20, -20, -10, -10, -20, -20, -40
    };

    const short RookTable[64] = 
    {
            0,  0,  0,  0,  0,  0,  0,   0 ,
            10, 20, 20, 20, 20, 20, 20,  10 ,
            -10,  0,  0,  0,  0,  0,  0, -10 ,
            -10,  0,  0,  0,  0,  0,  0, -10 ,
            -10,  0,  0,  0,  0,  0,  0, -10 ,
            -10,  0,  0,  0,  0,  0,  0, -10 ,
            -10,  0,  0,  0,  0,  0,  0, -10 ,
            -30, 30, 40, 10, 10,  0,  0, -30
    };
class PieceSquareTable
{
    static int EvaluatePiecePosition(ChessPieceType PieceType,
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



    static int EvaluatePawnWhitePosition(byte position, bool endGame)
    {
        if (endGame)
        {
            return PawnTableEndGame[(short)position];
        }

        return PawnTable[(short)position];
    }

    static int EvaluatePawnBlackPosition(byte position, bool endGame)
    {
        byte index = (byte)((((short)position + 56)) - (((short)position / 8) * 16));

        if (endGame)
        {
            return PawnTableEndGame[(short)index];
        }

        return PawnTable[(short)index];
    }
};