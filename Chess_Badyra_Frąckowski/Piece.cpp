#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
#include "Piece.h"

using namespace std;

//#region Enums

//#region ChessPieceColor enum

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

    list<byte> ValidMoves;

    //#endregion

    //#region Constructors

    // pusty konstruktor zeby tworzyc obiekt jedynie do wywolania metod z klasy

    Piece() = default;

    Piece(const Piece &piece)
    {
        PieceColor = piece.PieceColor;
        PieceType = piece.PieceType;
        Moved = piece.Moved;
        PieceValue = piece.PieceValue;
        PieceActionValue = piece.PieceActionValue;

        if (!piece.ValidMoves.empty())
            LastValidMoveCount = piece.ValidMoves.size();
    }

    Piece(ChessPieceType chessPiece, ChessPieceColor chessPieceColor)
    {
        PieceType = chessPiece;
        PieceColor = chessPieceColor;

        if (PieceType == ChessPieceType::Pawn || PieceType == ChessPieceType::Knight)
        {
            LastValidMoveCount = 2;
        }
        else
        {
            LastValidMoveCount = 0;
        }

        list<byte> temp_stack;
        ValidMoves = temp_stack;
        ValidMoves.push_back((byte)LastValidMoveCount);

        PieceValue = CalculatePieceValue(PieceType);
        PieceActionValue = CalculatePieceActionValue(PieceType);
    }

    //#endregion

    //#region InternalMembers

    static string GetPieceTypeShort(ChessPieceType pieceType)
    {
        switch (pieceType)
        {
        case ChessPieceType::Pawn:
                {
                    return "P";
                }
        case ChessPieceType::Knight:
                {
                    return "N";
                }
        case ChessPieceType::Bishop:
                {
                    return "B";
                }
        case ChessPieceType::Rook:
                {
                    return "R";
                }

        case ChessPieceType::Queen:
                {
                    return "Q";
                }

        case ChessPieceType::King:
                {
                    return "K";
                }
        default:
                {
                    return "P";
                }
        }
    }

    short CalculatePieceValue(ChessPieceType pieceType)
    {
        switch (pieceType)
        {
        case ChessPieceType::Pawn:
                {
                    return 100;

                }
        case ChessPieceType::Knight:
                {
                    return 320;
                }
        case ChessPieceType::Bishop:
                {
                    return 325;
                }
        case ChessPieceType::Rook:
                {
                    return 500;
                }

        case ChessPieceType::Queen:
                {
                    return 975;
                }

        case ChessPieceType::King:
                {
                    return 32767;
                }
        default:
                {
                    return 0;
                }
        }
    }

    short CalculatePieceActionValue(ChessPieceType pieceType)
    {
        switch (pieceType)
        {
        case ChessPieceType::Pawn:
                {
                    return 6;

                }
        case ChessPieceType::Knight:
                {
                    return 3;
                }
        case ChessPieceType::Bishop:
                {
                    return 3;
                }
        case ChessPieceType::Rook:
                {
                    return 2;
                }

        case ChessPieceType::Queen:
                {
                    return 1;
                }

        case ChessPieceType::King:
                {
                    return 1;
                }
        default:
                {
                    return 0;
                }
        }
    }

    //#endregion
    string ChessPieceType_to_string(ChessPieceType c) {
        switch (c)
        {
            case King: return "King";
            case Queen: return "Queen";
            case Rook: return "Rook";
            case Bishop: return "Bishop";
            case Knight: return "Knight";
            case Pawn: return "Pawn";
            case None: return "None";
        }
    }

    string ChessPieceColor_to_string(ChessPieceColor c) {
        switch (c)
        {
            case White: return "White";
            case Black: return "Black";
        }
    }

    string ToString()
    {
        return ChessPieceType_to_string(PieceType) + " " + ChessPieceColor_to_string(PieceColor) + " " + to_string(PieceValue) + " " + to_string(PieceActionValue) + " " + to_string(ValidMoves.size()) + " " + to_string(AttackedValue) + " " + to_string(DefendedValue);

    }

};
