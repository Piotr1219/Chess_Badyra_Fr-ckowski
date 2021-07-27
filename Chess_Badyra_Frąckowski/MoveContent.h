#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
#include "Piece.h"

using namespace std;


class PieceMoving
{
public:
    byte DstPosition;
    bool Moved;
    ChessPieceColor PieceColor;
    ChessPieceType PieceType;
    byte SrcPosition;

    PieceMoving(ChessPieceColor pieceColor, ChessPieceType pieceType, bool moved,
        byte srcPosition, byte dstPosition);

    PieceMoving(const PieceMoving &pieceMoving);

    PieceMoving(ChessPieceType pieceType);
    PieceMoving();
};

class PieceTaken
{
public:
    bool Moved;
    ChessPieceColor PieceColor;
    ChessPieceType PieceType;
    byte Position;

    PieceTaken(ChessPieceColor pieceColor, ChessPieceType pieceType, bool moved,
        byte position);

    PieceTaken(ChessPieceType pieceType);
    PieceTaken();
};

class MoveContent
{
public:
    bool EnPassantOccured;
    PieceMoving MovingPiecePrimary;
    PieceMoving MovingPieceSecondary;
    ChessPieceType PawnPromotedTo;
    PieceTaken TakenPiece;

    bool DoubleRowQueen;
    bool DoubleColQueen;

    bool DoubleRowRook;
    bool DoubleColRook;

    bool DoubleRowKnight;
    bool DoubleColKnight;

    string PgnMove;


    MoveContent();

    MoveContent(const MoveContent &moveContent);

    MoveContent(string move);

    bool ParseAN(string move, byte* sourceColumn, byte* sourceRow, byte* destinationColumn, byte* destinationRow);

    string GetPureCoordinateNotation();

    string ToString();

    string GeneratePGNString(Board board);

private:
    byte GetBoardIndex(int col, int row);

    string GetColumnFromInt(int column);

    int GetIntFromColumn(char column);

    ChessPieceType GetPieceType(char c);

    string GetPgnMove(ChessPieceType pieceType);
};