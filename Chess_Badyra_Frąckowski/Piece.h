#pragma once
#include <string>
#include <list>
#include <stack>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace std;

__device__ __host__ enum ChessPieceColor
{
    White,
    Black
};

//#endregion

//#region ChessPieceType enum

__device__ __host__ enum ChessPieceType
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

    __device__ __host__ Piece();

    __host__ Piece(const Piece& piece);

    __device__ __host__ Piece(ChessPieceType chessPiece, ChessPieceColor chessPieceColor);


    static string GetPieceTypeShort(ChessPieceType pieceType);

    short CalculatePieceValue(ChessPieceType pieceType);

    short CalculatePieceActionValue(ChessPieceType pieceType);

    string ChessPieceType_to_string(ChessPieceType c);

    string ChessPieceColor_to_string(ChessPieceColor c);

    string ToString();

};