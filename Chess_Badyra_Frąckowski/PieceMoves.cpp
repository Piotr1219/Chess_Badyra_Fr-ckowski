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


PieceMoveSet::PieceMoveSet(list<byte> moves)
{
    Moves = moves;
}
//PieceMoveSet() {    }


byte PieceMoves::Position(byte col, byte row)
{
    return (byte)((short)col + ((short)row * 8));
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
    MoveArrays.WhitePawnTotalMoves = new byte[64];

    MoveArrays.BlackPawnMoves = new PieceMoveSet[64];
    MoveArrays.BlackPawnTotalMoves = new byte[64];

    MoveArrays.KnightMoves = new PieceMoveSet[64];
    MoveArrays.KnightTotalMoves = new byte[64];

    MoveArrays.BishopMoves1 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves1 = new byte[64];

    MoveArrays.BishopMoves2 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves2 = new byte[64];

    MoveArrays.BishopMoves3 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves3 = new byte[64];

    MoveArrays.BishopMoves4 = new PieceMoveSet[64];
    MoveArrays.BishopTotalMoves4 = new byte[64];

    MoveArrays.RookMoves1 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves1 = new byte[64];

    MoveArrays.RookMoves2 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves2 = new byte[64];

    MoveArrays.RookMoves3 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves3 = new byte[64];

    MoveArrays.RookMoves4 = new PieceMoveSet[64];
    MoveArrays.RookTotalMoves4 = new byte[64];

    MoveArrays.QueenMoves1 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves1 = new byte[64];

    MoveArrays.QueenMoves2 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves2 = new byte[64];

    MoveArrays.QueenMoves3 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves3 = new byte[64];

    MoveArrays.QueenMoves4 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves4 = new byte[64];

    MoveArrays.QueenMoves5 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves5 = new byte[64];

    MoveArrays.QueenMoves6 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves6 = new byte[64];

    MoveArrays.QueenMoves7 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves7 = new byte[64];

    MoveArrays.QueenMoves8 = new PieceMoveSet[64];
    MoveArrays.QueenTotalMoves8 = new byte[64];

    MoveArrays.KingMoves = new PieceMoveSet[64];
    MoveArrays.KingTotalMoves = new byte[64];
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
        PieceMoveSet moveset = PieceMoveSet(list<byte>());

        byte x = (byte)(index % 8);
        byte y = (byte)((index / 8));

        //Diagonal Kill
        if ((short)y < 7 && (short)x < 7)
        {
            moveset.Moves.push_back((byte)(index + 8 + 1));
            MoveArrays::BlackPawnTotalMoves[index] = (byte)((int)MoveArrays::BlackPawnTotalMoves[index] + 1);
        }
        if ((short)x > 0 && (short)y < 7)
        {
            moveset.Moves.push_back((byte)(index + 8 - 1));
            MoveArrays::BlackPawnTotalMoves[index] = (byte)((int)MoveArrays::BlackPawnTotalMoves[index] + 1);
        }

        //One Forward
        moveset.Moves.push_back((byte)(index + 8));
        MoveArrays::BlackPawnTotalMoves[index] = (byte)((int)MoveArrays::BlackPawnTotalMoves[index] + 1);

        //Starting Position we can jump 2
        if ((short)y == 1)
        {
            moveset.Moves.push_back((byte)(index + 16));
            MoveArrays::BlackPawnTotalMoves[index] = (byte)((int)MoveArrays::BlackPawnTotalMoves[index] + 1);
        }

        MoveArrays::BlackPawnMoves[index] = moveset;
    }
}

void PieceMoves::SetMovesWhitePawn()
{
    for (short index = 8; index <= 55; index++)
    {
        byte x = (byte)(index % 8);
        byte y = (byte)((index / 8));

        PieceMoveSet moveset = PieceMoveSet(list<byte>());

        //Diagonal Kill
        if ((short)x < 7 && (short)y > 0)
        {
            moveset.Moves.push_back((byte)(index - 8 + 1));
            MoveArrays::WhitePawnTotalMoves[index] = (byte)((int)MoveArrays::WhitePawnTotalMoves[index] + 1);
        }
        if ((short)x > 0 && (short)y > 0)
        {
            moveset.Moves.push_back((byte)(index - 8 - 1));
            MoveArrays::WhitePawnTotalMoves[index] = (byte)((int)MoveArrays::WhitePawnTotalMoves[index] + 1);
        }

        //One Forward
        moveset.Moves.push_back((byte)(index - 8));
        MoveArrays::WhitePawnTotalMoves[index] = (byte)((int)MoveArrays::WhitePawnTotalMoves[index] + 1);

        //Starting Position we can jump 2
        if ((short)y == 6)
        {
            moveset.Moves.push_back((byte)(index - 16));
            MoveArrays::WhitePawnTotalMoves[index] = (byte)((int)MoveArrays::WhitePawnTotalMoves[index] + 1);
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

            PieceMoveSet moveset = PieceMoveSet(list<byte>());

            byte move;

            if (y < 6 && x > 0)
            {
                move = Position((byte)(y + 2), (byte)(x - 1));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 1 && x < 7)
            {
                move = Position((byte)(y - 2), (byte)(x + 1));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 1 && x > 0)
            {
                move = Position((byte)(y - 2), (byte)(x - 1));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y < 6 && x < 7)
            {
                move = Position((byte)(y + 2), (byte)(x + 1));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 0 && x < 6)
            {
                move = Position((byte)(y - 1), (byte)(x + 2));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y < 7 && x > 1)
            {
                move = Position((byte)(y + 1), (byte)(x - 2));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y > 0 && x > 1)
            {
                move = Position((byte)(y - 1), (byte)(x - 2));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
                }
            }

            if (y < 7 && x < 6)
            {
                move = Position((byte)(y + 1), (byte)(x + 2));

                if ((short)move < 64)
                {
                    moveset.Moves.push_back(move);
                    MoveArrays::KnightTotalMoves[index] = (byte)((int)MoveArrays::KnightTotalMoves[index] + 1);
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

            PieceMoveSet moveset = PieceMoveSet(list<byte>());
            byte move;

            short row = x;
            short col = y;

            while (row < 7 && col < 7)
            {
                row++;
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves1[index] = (byte)((int)MoveArrays::BishopTotalMoves1[index] + 1);
            }

            MoveArrays::BishopMoves1[index] = moveset;
            // PieceMoveSet moveset = PieceMoveSet(list<byte>());
            moveset = PieceMoveSet(list<byte>());

            row = x;
            col = y;

            while (row < 7 && col > 0)
            {
                row++;
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves2[index] = (byte)((int)MoveArrays::BishopTotalMoves2[index] + 1);
            }

            MoveArrays::BishopMoves2[index] = moveset;
            moveset = PieceMoveSet(list<byte>());

            row = x;
            col = y;

            while (row > 0 && col < 7)
            {
                row--;
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves3[index] = (byte)((int)MoveArrays::BishopTotalMoves3[index] + 1);
            }

            MoveArrays::BishopMoves3[index] = moveset;
            moveset = PieceMoveSet(list<byte>());

            row = x;
            col = y;

            while (row > 0 && col > 0)
            {
                row--;
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::BishopTotalMoves4[index] = (byte)((int)MoveArrays::BishopTotalMoves4[index] + 1);
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

            PieceMoveSet moveset = PieceMoveSet(list<byte>());
            byte move;

            short row = x;
            short col = y;

            while (row < 7)
            {
                row++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves1[index] = (byte)((int)MoveArrays::RookTotalMoves1[index] + 1);
            }

            MoveArrays::RookMoves1[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (row > 0)
            {
                row--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves2[index] = (byte)((int)MoveArrays::RookTotalMoves2[index] + 1);
            }

            MoveArrays::RookMoves2[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (col > 0)
            {
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves3[index] = (byte)((int)MoveArrays::RookTotalMoves3[index] + 1);
            }

            MoveArrays::RookMoves3[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (col < 7)
            {
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::RookTotalMoves4[index] = (byte)((int)MoveArrays::RookTotalMoves4[index] + 1);
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

            PieceMoveSet moveset = PieceMoveSet(list<byte>());
            byte move;

            short row = x;
            short col = y;

            while (row < 7)
            {
                row++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves1[index] = (byte)((int)MoveArrays::QueenTotalMoves1[index] + 1);
            }

            MoveArrays::QueenMoves1[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (row > 0)
            {
                row--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves2[index] = (byte)((int)MoveArrays::QueenTotalMoves2[index] + 1);
            }

            MoveArrays::QueenMoves2[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (col > 0)
            {
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves3[index] = (byte)((int)MoveArrays::QueenTotalMoves3[index] + 1);
            }

            MoveArrays::QueenMoves3[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (col < 7)
            {
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves4[index] = (byte)((int)MoveArrays::QueenTotalMoves4[index] + 1);
            }

            MoveArrays::QueenMoves4[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (row < 7 && col < 7)
            {
                row++;
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves5[index] = (byte)((int)MoveArrays::QueenTotalMoves5[index] + 1);
            }

            MoveArrays::QueenMoves5[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (row < 7 && col > 0)
            {
                row++;
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves6[index] = (byte)((int)MoveArrays::QueenTotalMoves6[index] + 1);
            }

            MoveArrays::QueenMoves6[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (row > 0 && col < 7)
            {
                row--;
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves7[index] = (byte)((int)MoveArrays::QueenTotalMoves7[index] + 1);
            }

            MoveArrays::QueenMoves7[index] = moveset;

            moveset = PieceMoveSet(list<byte>());
            row = x;
            col = y;

            while (row > 0 && col > 0)
            {
                row--;
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::QueenTotalMoves8[index] = (byte)((int)MoveArrays::QueenTotalMoves8[index] + 1);
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

            PieceMoveSet moveset = PieceMoveSet(list<byte>());
            byte move;

            short row = x;
            short col = y;

            if (row < 7)
            {
                row++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row > 0)
            {
                row--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (col > 0)
            {
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (col < 7)
            {
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row < 7 && col < 7)
            {
                row++;
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row < 7 && col > 0)
            {
                row++;
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            row = x;
            col = y;

            if (row > 0 && col < 7)
            {
                row--;
                col++;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }


            row = x;
            col = y;

            if (row > 0 && col > 0)
            {
                row--;
                col--;

                move = Position((byte)col, (byte)row);
                moveset.Moves.push_back(move);
                MoveArrays::KingTotalMoves[index] = (byte)((int)MoveArrays::KingTotalMoves[index] + 1);
            }

            MoveArrays::KingMoves[index] = moveset;
        }
    }
}

//#endregion

