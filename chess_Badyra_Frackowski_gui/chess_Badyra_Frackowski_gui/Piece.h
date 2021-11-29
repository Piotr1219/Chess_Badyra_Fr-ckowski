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

using namespace std;

enum ChessPieceColor
{
    White,
    Black
};

//#endregion

//#region ChessPieceType enum

enum ChessPieceType
{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    None
};

//#endregion

//#endregion


class Piece
{public:
    //#region InternalMembers

    ChessPieceColor PieceColor;
    ChessPieceType PieceType;

    short PieceValue;
    short PieceActionValue;

    short AttackedValue;
    short DefendedValue;

    int LastValidMoveCount;
    bool Moved;

    bool Selected;

    list<char> ValidMoves;

    Piece();

    Piece(const Piece& piece);

    Piece(ChessPieceType chessPiece, ChessPieceColor chessPieceColor);


    static string GetPieceTypeShort(ChessPieceType pieceType);

    short CalculatePieceValue(ChessPieceType pieceType);

    short CalculatePieceActionValue(ChessPieceType pieceType);

    string ChessPieceType_to_string(ChessPieceType c);

    string ChessPieceColor_to_string(ChessPieceColor c);

    string ToString();

};