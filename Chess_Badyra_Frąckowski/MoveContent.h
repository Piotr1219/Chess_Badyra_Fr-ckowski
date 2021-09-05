#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Board.h"
#include "Piece.h"
#include "Square.h"

using namespace std;


class PieceMoving
{
public:
    char DstPosition;
    bool Moved;
    ChessPieceColor PieceColor;
    ChessPieceType PieceType;
    char SrcPosition;

    PieceMoving(ChessPieceColor pieceColor, ChessPieceType pieceType, bool moved,
        char srcPosition, char dstPosition);

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
    char Position;

    PieceTaken(ChessPieceColor pieceColor, ChessPieceType pieceType, bool moved,
        char position);

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

    static bool ParseAN(string move, char* sourceColumn, char* sourceRow, char* destinationColumn, char* destinationRow);

    string GetPureCoordinateNotation();

    string ToString();

    //string GeneratePGNString(Board board);
    string GeneratePGNString(Square squares[]);

private:
    char GetBoardIndex(int col, int row);

    string GetColumnFromInt(int column);

    static int GetIntFromColumn(char column);

    ChessPieceType GetPieceType(char c);

    string GetPgnMove(ChessPieceType pieceType);
};