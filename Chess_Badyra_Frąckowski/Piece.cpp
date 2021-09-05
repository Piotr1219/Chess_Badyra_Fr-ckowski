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


Piece::Piece() = default;

Piece::Piece(const Piece &piece)
{
    PieceColor = piece.PieceColor;
    PieceType = piece.PieceType;
    Moved = piece.Moved;
    PieceValue = piece.PieceValue;
    PieceActionValue = piece.PieceActionValue;
    AttackedValue = piece.AttackedValue;
    DefendedValue = piece.DefendedValue;
    Selected = piece.Selected;

    if (!piece.ValidMoves.empty())
        LastValidMoveCount = piece.ValidMoves.size();

    ValidMoves = piece.ValidMoves;
}

Piece::Piece(ChessPieceType chessPiece, ChessPieceColor chessPieceColor)
{
    PieceType = chessPiece;
    PieceColor = chessPieceColor;
    AttackedValue = 0;
    DefendedValue = 0;
    Moved = false;
    Selected = false;

    if (PieceType == ChessPieceType::Pawn || PieceType == ChessPieceType::Knight)
    {
        LastValidMoveCount = 2;
    }
    else
    {
        LastValidMoveCount = 0;
    }

    list<char> temp_stack;
    ValidMoves = temp_stack;
    ValidMoves.push_back(LastValidMoveCount);

    PieceValue = CalculatePieceValue(PieceType);
    PieceActionValue = CalculatePieceActionValue(PieceType);
}

//#endregion

//#region InternalMembers

string Piece::GetPieceTypeShort(ChessPieceType pieceType)
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

short Piece::CalculatePieceValue(ChessPieceType pieceType)
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

short Piece::CalculatePieceActionValue(ChessPieceType pieceType)
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
string Piece::ChessPieceType_to_string(ChessPieceType c) {
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

string Piece::ChessPieceColor_to_string(ChessPieceColor c) {
    switch (c)
    {
        case White: return "White";
        case Black: return "Black";
    }
}

string Piece::ToString()
{
    return ChessPieceType_to_string(PieceType) + " " + ChessPieceColor_to_string(PieceColor) + " " + to_string(PieceValue) + " " + to_string(PieceActionValue) + " " + to_string(ValidMoves.size()) + " " + to_string(AttackedValue) + " " + to_string(DefendedValue);

}
