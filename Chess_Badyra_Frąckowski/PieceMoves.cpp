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
#include "PieceMoves.h"
//#include "Evaluations.h"
//#include "PGN.h"

using namespace std;


PieceMoveSet::PieceMoveSet(list<char> moves)
{
    Moves = moves;
}
PieceMoveSet::PieceMoveSet()
{
}


char PieceMoves::Position(char col, char row)
{
    return (col + (row * 8));
}

//#region IntitiateMotionMethods

void PieceMoves::InitiateChessPieceMotion()
{
    if (Initiated)
    {
        return;
    }

    Initiated = true;
    /*
    MoveArrays.WhitePawnMoves = new PieceMoveSet[64];
    MoveArrays.WhitePawnTotalMoves = new char[64];

    MoveArrays.BlackPawnMoves = new PieceMoveSet[64];
    MoveArrays.BlackPawnTotalMoves = new char[64];

    MoveArrays.KnightMoves = new PieceMoveSet[64];
    MoveArrays.KnightTotalMoves = new char[64];

    MoveArrays.BishopMoves1 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves1 = new char[64];

    MoveArrays.BishopMoves2 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves2 = new char[64];

    MoveArrays.BishopMoves3 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves3 = new char[64];

    MoveArrays.BishopMoves4 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves4 = new char[64];

    MoveArrays.RookMoves1 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves1 = new char[64];

    MoveArrays.RookMoves2 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves2 = new char[64];

    MoveArrays.RookMoves3 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves3 = new char[64];

    MoveArrays.RookMoves4 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves4 = new char[64];

    MoveArrays.QueenMoves1 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves1 = new char[64];

    MoveArrays.QueenMoves2 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves2 = new char[64];

    MoveArrays.QueenMoves3 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves3 = new char[64];

    MoveArrays.QueenMoves4 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves4 = new char[64];

    MoveArrays.QueenMoves5 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves5 = new char[64];

    MoveArrays.QueenMoves6 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves6 = new char[64];

    MoveArrays.QueenMoves7 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves7 = new char[64];

    MoveArrays.QueenMoves8 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves8 = new char[64];

    MoveArrays.KingMoves = new PieceMoveSet[64];
    MoveArrays.KingTotalMoves = new char[64];
    */

    SetMovesWhitePawn();
    SetMovesBlackPawn();
    SetMovesKnight();
    SetMovesBishop();
    SetMovesRook();
    SetMovesQueen();
    SetMovesKing();
}

void PieceMoves::SetMovesBlackPawn()
{
    for (short index = 8; index <= 55; index++)
    {
        PieceMoveSet moveset = PieceMoveSet(list<char>());

        char x = (index % 8);
        char y = (index / 8);

        //Diagonal Kill
        if ((short)y < 7 && (short)x < 7)
        {
            moveset.Moves.push_back((index + 8 + 1));
            MoveArrays::BlackPawnTotalMoves[index] = (MoveArrays::BlackPawnTotalMoves[index] + 1);
        }
        if ((short)x > 0 && (short)y < 7)
        {
            moveset.Moves.push_back(index + 8 - 1);
            MoveArrays::BlackPawnTotalMoves[index] = (MoveArrays::BlackPawnTotalMoves[index] + 1);
        }

        //One Forward
        moveset.Moves.push_back((index + 8));
        MoveArrays::BlackPawnTotalMoves[index] = (MoveArrays::BlackPawnTotalMoves[index] + 1);

        //Starting Position we can jump 2
        if ((short)y == 1)
        {
            moveset.Moves.push_back(index + 16);
            MoveArrays::BlackPawnTotalMoves[index] = (MoveArrays::BlackPawnTotalMoves[index] + 1);
        }

        MoveArrays::BlackPawnMoves[index] = moveset;
    }
}

void PieceMoves::SetMovesWhitePawn()
{
    for (short index = 8; index <= 55; index++)
    {
        char x = (index % 8);
        char y = (index / 8);

        PieceMoveSet moveset = PieceMoveSet(list<char>());

        //Diagonal Kill
        if (x < 7 && y > 0)
        {
            moveset.Moves.push_back(index - 8 + 1);
            MoveArrays::WhitePawnTotalMoves[index] = (MoveArrays::WhitePawnTotalMoves[index] + 1);
        }
        if (x > 0 && y > 0)
        {
            moveset.Moves.push_back(index - 8 - 1);
            MoveArrays::WhitePawnTotalMoves[index] = (MoveArrays::WhitePawnTotalMoves[index] + 1);
        }

        //One Forward
        moveset.Moves.push_back((index - 8));
        MoveArrays::WhitePawnTotalMoves[index] = (MoveArrays::WhitePawnTotalMoves[index] + 1);

        //Starting Position we can jump 2
        if (y == 6)
        {
            moveset.Moves.push_back(index - 16);
            MoveArrays::WhitePawnTotalMoves[index] = (MoveArrays::WhitePawnTotalMoves[index] + 1);
        }

        MoveArrays::WhitePawnMoves[index] = moveset;
    }
}

void PieceMoves::SetMovesKnight()
{
    for (short y = 0; y < 8; y++)
    {
        for (short x = 0; x < 8; x++)
        {
            short index = (y + (x * 8));

            PieceMoveSet moveset = PieceMoveSet(list<char>());

            char move;

            if (y < 6 && x > 0)
            {
                move = Position((y + 2), (x - 1));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 1 && x < 7)
            {
                move = Position((y - 2), (x + 1));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 1 && x > 0)
            {
                move = Position((y - 2), (x - 1));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y < 6 && x < 7)
            {
                move = Position((y + 2), (x + 1));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 0 && x < 6)
            {
                move = Position((y - 1), (x + 2));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y < 7 && x > 1)
            {
                move = Position((y + 1), (x - 2));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 0 && x > 1)
            {
                move = Position((y - 1), (x - 2));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y < 7 && x < 6)
            {
                move = Position((y + 1), (x + 2));

                if (move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            MoveArrays::KnightMoves[index] = moveset;
        }
    }
}

void PieceMoves::SetMovesBishop()
{
    for (short y = 0; y < 8; y++)
    {
        for (short x = 0; x < 8; x++)
        {
            short index = (y + (x * 8));

            PieceMoveSet moveset = PieceMoveSet(list<char>());
            char move;

            short row = x;
            short col = y;

            while (row < 7 && col < 7)
            {
                row++;
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves1[index] = (MoveArrays::BishopTotalMoves1[index] + 1);
            }

            MoveArrays::BishopMoves1[index] = moveset;
            // PieceMoveSet moveset = PieceMoveSet(list<char>());
            moveset = PieceMoveSet(list<char>());

            row = x;
            col = y;

            while (row < 7 && col > 0)
            {
                row++;
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves2[index] = (MoveArrays::BishopTotalMoves2[index] + 1);
            }

            MoveArrays::BishopMoves2[index] = moveset;
            moveset = PieceMoveSet(list<char>());

            row = x;
            col = y;

            while (row > 0 && col < 7)
            {
                row--;
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves3[index] = (MoveArrays::BishopTotalMoves3[index] + 1);
            }

            MoveArrays::BishopMoves3[index] = moveset;
            moveset = PieceMoveSet(list<char>());

            row = x;
            col = y;

            while (row > 0 && col > 0)
            {
                row--;
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves4[index] = (MoveArrays::BishopTotalMoves4[index] + 1);
            }

            MoveArrays::BishopMoves4[index] = moveset;
        }
    }
}

void PieceMoves::SetMovesRook()
{
    for (short y = 0; y < 8; y++)
    {
        for (short x = 0; x < 8; x++)
        {
            short index = (y + (x * 8));

            PieceMoveSet moveset = PieceMoveSet(list<char>());
            char move;

            short row = x;
            short col = y;

            while (row < 7)
            {
                row++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves1[index] = (MoveArrays::RookTotalMoves1[index] + 1);
            }

            MoveArrays::RookMoves1[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (row > 0)
            {
                row--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves2[index] = (MoveArrays::RookTotalMoves2[index] + 1);
            }

            MoveArrays::RookMoves2[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (col > 0)
            {
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves3[index] = (MoveArrays::RookTotalMoves3[index] + 1);
            }

            MoveArrays::RookMoves3[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (col < 7)
            {
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves4[index] = (MoveArrays::RookTotalMoves4[index] + 1);
            }

            MoveArrays::RookMoves4[index] = moveset;
        }
    }
}

void PieceMoves::SetMovesQueen()
{
    for (short y = 0; y < 8; y++)
    {
        for (short x = 0; x < 8; x++)
        {
            short index = (y + (x * 8));

            PieceMoveSet moveset = PieceMoveSet(list<char>());
            char move;

            short row = x;
            short col = y;

            while (row < 7)
            {
                row++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves1[index] = (MoveArrays::QueenTotalMoves1[index] + 1);
            }

            MoveArrays::QueenMoves1[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (row > 0)
            {
                row--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves2[index] = (MoveArrays::QueenTotalMoves2[index] + 1);
            }

            MoveArrays::QueenMoves2[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (col > 0)
            {
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves3[index] = (MoveArrays::QueenTotalMoves3[index] + 1);
            }

            MoveArrays::QueenMoves3[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (col < 7)
            {
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves4[index] = (MoveArrays::QueenTotalMoves4[index] + 1);
            }

            MoveArrays::QueenMoves4[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (row < 7 && col < 7)
            {
                row++;
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves5[index] = (MoveArrays::QueenTotalMoves5[index] + 1);
            }

            MoveArrays::QueenMoves5[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (row < 7 && col > 0)
            {
                row++;
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves6[index] = (MoveArrays::QueenTotalMoves6[index] + 1);
            }

            MoveArrays::QueenMoves6[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (row > 0 && col < 7)
            {
                row--;
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves7[index] = (MoveArrays::QueenTotalMoves7[index] + 1);
            }

            MoveArrays::QueenMoves7[index] = moveset;

            moveset = PieceMoveSet(list<char>());
            row = x;
            col = y;

            while (row > 0 && col > 0)
            {
                row--;
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves8[index] = (MoveArrays::QueenTotalMoves8[index] + 1);
            }

            MoveArrays::QueenMoves8[index] = moveset;
        }
    }
}

void PieceMoves::SetMovesKing()
{
    for (short y = 0; y < 8; y++)
    {
        for (short x = 0; x < 8; x++)
        {
            short index = (y + (x * 8));

            PieceMoveSet moveset = PieceMoveSet(list<char>());
            char move;

            short row = x;
            short col = y;

            if (row < 7)
            {
                row++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row > 0)
            {
                row--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (col > 0)
            {
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (col < 7)
            {
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row < 7 && col < 7)
            {
                row++;
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row < 7 && col > 0)
            {
                row++;
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row > 0 && col < 7)
            {
                row--;
                col++;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }


            row = x;
            col = y;

            if (row > 0 && col > 0)
            {
                row--;
                col--;

                move = Position(col, row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (MoveArrays::KingTotalMoves[index] + 1);
            }

            MoveArrays::KingMoves[index] = moveset;
        }
    }
}

//#endregion

