#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
#include "MoveContent.h"
//#include "Piece.h"

using namespace std;


PieceMoving::PieceMoving(ChessPieceColor pieceColor, ChessPieceType pieceType, bool moved,
    char srcPosition, char dstPosition)
{
    PieceColor = pieceColor;
    PieceType = pieceType;
    SrcPosition = srcPosition;
    DstPosition = dstPosition;
    Moved = moved;
}

PieceMoving::PieceMoving(const PieceMoving& pieceMoving)
{
    PieceColor = pieceMoving.PieceColor;
    PieceType = pieceMoving.PieceType;
    SrcPosition = pieceMoving.SrcPosition;
    DstPosition = pieceMoving.DstPosition;
    Moved = pieceMoving.Moved;
}

PieceMoving::PieceMoving(ChessPieceType pieceType)
{
    PieceType = pieceType;
    PieceColor = ChessPieceColor::White;
    SrcPosition = 0;
    DstPosition = 0;
    Moved = false;
}

PieceMoving::PieceMoving() {
    ;
}



PieceTaken::PieceTaken(ChessPieceColor pieceColor, ChessPieceType pieceType, bool moved,
    char position)
{
    PieceColor = pieceColor;
    PieceType = pieceType;
    Position = position;
    Moved = moved;
}

PieceTaken::PieceTaken(ChessPieceType pieceType)
{
    PieceColor = ChessPieceColor::White;
    PieceType = pieceType;
    Position = 0;
    Moved = false;
}
PieceTaken::PieceTaken() {
    ;
}


MoveContent::MoveContent()
{
    PieceMoving MovingPiecePrimary = PieceMoving(ChessPieceType::None);
    PieceMoving MovingPieceSecondary = PieceMoving(ChessPieceType::None);
    PieceTaken TakenPiece = PieceTaken(ChessPieceType::None);
}

MoveContent::MoveContent(const MoveContent &moveContent)
{
    //PieceMoving MovingPiecePrimary(moveContent.MovingPiecePrimary);
    MovingPiecePrimary = moveContent.MovingPiecePrimary;
    //PieceMoving MovingPieceSecondary(moveContent.MovingPieceSecondary);
    MovingPieceSecondary = moveContent.MovingPieceSecondary;

    //PieceTaken TakenPiece(moveContent.TakenPiece.PieceColor,
     //                           moveContent.TakenPiece.PieceType,
     //                           moveContent.TakenPiece.Moved,
     //                           moveContent.TakenPiece.Position);
    TakenPiece.PieceColor = moveContent.TakenPiece.PieceColor;
    TakenPiece.PieceType = moveContent.TakenPiece.PieceType;
    TakenPiece.Moved = moveContent.TakenPiece.Moved;
    TakenPiece.Position = moveContent.TakenPiece.Position;

    EnPassantOccured = moveContent.EnPassantOccured;
    PawnPromotedTo = moveContent.PawnPromotedTo;
}

MoveContent::MoveContent(string move) : MoveContent()
{

    int srcCol = -1;

    bool comment = false;
    bool srcFound = false;

    if (move.find("=Q") != std::string::npos)
    {
        PawnPromotedTo = ChessPieceType::Queen;
    }
    else if (move.find("=N") != std::string::npos)
    {
        PawnPromotedTo = ChessPieceType::Knight;
    }
    else if (move.find("=R") != std::string::npos)
    {
        PawnPromotedTo = ChessPieceType::Rook;
    }
    else if (move.find("=B") != std::string::npos)
    {
        PawnPromotedTo = ChessPieceType::Bishop;
    }

    for (auto& c : move)
    {
        if (c == '{')
        {
            comment = true;
            continue;
        }
        if (c == '}')
        {
            comment = false;
            continue;
        }

        if (comment)
        {
            continue;
        }

        if (MovingPiecePrimary.PieceType == ChessPieceType::None)
        {
            //Get Piece Type
            MovingPiecePrimary.PieceType = GetPieceType(c);

            if (MovingPiecePrimary.PieceType == ChessPieceType::None)
            {
                MovingPiecePrimary.PieceType = ChessPieceType::Pawn;

                //This is a column character
                srcCol = GetIntFromColumn(c);
            }
            continue;
        }
        if (srcCol < 0)
        {
            srcCol = GetIntFromColumn(c);
            continue;
        }
        if (srcCol >= 0)
        {
            std::string s(1, c);
            int srcRow = stoi(s);

            if (!srcFound)
            {
                MovingPiecePrimary.SrcPosition = GetBoardIndex(srcCol, 8 - srcRow);
                srcFound = true;
            }
            else
            {
                MovingPiecePrimary.DstPosition = GetBoardIndex(srcCol, 8 - srcRow);
            }

            srcCol = -1;
            continue;
        }
    }
}

bool MoveContent::ParseAN(string move, char* sourceColumn, char* sourceRow, char* destinationColumn, char* destinationRow)
{
    if (move.length() != 4) return false;
    *sourceColumn = GetIntFromColumn(move[0]);
    *sourceRow = (8 - stoi(string("") + move[1]));
    *destinationColumn = GetIntFromColumn(move[2]);
    *destinationRow = (8 - stoi(string("") + move[3]));
    return true;
}

string MoveContent::GetPureCoordinateNotation()
{
    char srcCol = (MovingPiecePrimary.SrcPosition % 8);
    char srcRow = (8 - (MovingPiecePrimary.SrcPosition / 8));
    char dstCol = (MovingPiecePrimary.DstPosition % 8);
    char dstRow = (8 - (MovingPiecePrimary.DstPosition / 8));

    std::string result = string("") + (char)('a' + (char)srcCol) + ((char)srcRow)+(char)('a' + (char)dstCol) + ((char)dstRow);
    if (PawnPromotedTo == ChessPieceType::Queen)
    {
        result += "=Q";
    }
    else if (PawnPromotedTo == ChessPieceType::Rook)
    {
        result += "=R";
    }
    else if (PawnPromotedTo == ChessPieceType::Bishop)
    {
        result += "=B";
    }
    else if (PawnPromotedTo == ChessPieceType::Knight)
    {
        result += "=N";
    }
    return result;
}

string MoveContent::ToString()
{
    if (PgnMove != "")
    {
        return PgnMove;
    }

    char srcCol = (MovingPiecePrimary.SrcPosition % 8);
    char srcRow = (8 - (MovingPiecePrimary.SrcPosition / 8));
    char dstCol = (MovingPiecePrimary.DstPosition % 8);
    char dstRow = (8 - (MovingPiecePrimary.DstPosition / 8));

    if (MovingPieceSecondary.PieceType == ChessPieceType::Rook)
    {
        if (MovingPieceSecondary.PieceColor == ChessPieceColor::Black)
        {
            if (MovingPieceSecondary.SrcPosition == 7)
            {
                PgnMove += "O-O";
            }
            else if (MovingPieceSecondary.SrcPosition == 0)
            {
                PgnMove += "O-O-O";
            }
        }
        else if (MovingPieceSecondary.PieceColor == ChessPieceColor::White)
        {
            if (MovingPieceSecondary.SrcPosition == 63)
            {
                PgnMove += "O-O";
            }
            else if (MovingPieceSecondary.SrcPosition == 56)
            {
                PgnMove += "O-O-O";
            }
        }
    }
    else
    {
        PgnMove += GetPgnMove(MovingPiecePrimary.PieceType);

        switch (MovingPiecePrimary.PieceType)
        {
            case ChessPieceType::Knight:
                PgnMove += GetColumnFromInt(srcCol);
                PgnMove += (char)srcRow;
                break;
            case ChessPieceType::Rook:
                PgnMove += GetColumnFromInt(srcCol);
                PgnMove += (char)srcRow;
                break;
            case ChessPieceType::Pawn:
                if (srcCol != dstCol)
                {
                    PgnMove += GetColumnFromInt(srcCol);
                }
                break;
        }

        if (TakenPiece.PieceType != ChessPieceType::None)
        {
            PgnMove += "x";
        }

        PgnMove += GetColumnFromInt(dstCol);

        PgnMove += (char)dstRow;

        if (PawnPromotedTo == ChessPieceType::Queen)
        {
            PgnMove += "=Q";
        }
        else if (PawnPromotedTo == ChessPieceType::Rook)
        {
            PgnMove += "=R";
        }
        else if (PawnPromotedTo == ChessPieceType::Bishop)
        {
            PgnMove += "=B";
        }
        else if (PawnPromotedTo == ChessPieceType::Knight)
        {
            PgnMove += "=N";
        }
    }

    return PgnMove;
}

//string MoveContent::GeneratePGNString(Board board)
string MoveContent::GeneratePGNString(Square squares[])
{
    if (PgnMove != "")
    {
        return PgnMove;
    }

    bool doubleColumn = false;
    bool doubleRow = false;


    bool doubleDestination = false;

    char srcCol = (MovingPiecePrimary.SrcPosition % 8);
    char srcRow = (8 - (MovingPiecePrimary.SrcPosition / 8));
    char dstCol = (MovingPiecePrimary.DstPosition % 8);
    char dstRow = (8 - (MovingPiecePrimary.DstPosition / 8));

    PgnMove = "";

    for (int x = 0; x < 64; x++)
    {
        if (x == MovingPiecePrimary.DstPosition)
            continue;

        //Square square = board.Squares[x];
        Square square = squares[x];

        if (square.Piece1.PieceType != ChessPieceType::None)
            continue;


        if (square.Piece1.PieceType == MovingPiecePrimary.PieceType)
        {
            if (square.Piece1.PieceColor == MovingPiecePrimary.PieceColor)
            {
                for(char&move : square.Piece1.ValidMoves)
                {
                    if (move == MovingPiecePrimary.DstPosition)
                    {
                        doubleDestination = true;

                        char col = (x % 8);
                        char row = (8 - (x / 8));

                        if (col == srcCol)
                        {
                            doubleColumn = true;
                        }

                        if (row == srcRow)
                        {
                            doubleRow = true;
                        }

                        break;
                    }
                }


            }
        }
    }


    if (MovingPieceSecondary.PieceType == ChessPieceType::Rook)
    {
        if (MovingPieceSecondary.PieceColor == ChessPieceColor::Black)
        {
            if (MovingPieceSecondary.SrcPosition == 7)
            {
                PgnMove += "O-O";
            }
            else if (MovingPieceSecondary.SrcPosition == 0)
            {
                PgnMove += "O-O-O";
            }
        }
        else if (MovingPieceSecondary.PieceColor == ChessPieceColor::White)
        {
            if (MovingPieceSecondary.SrcPosition == 63)
            {
                PgnMove += "O-O";
            }
            else if (MovingPieceSecondary.SrcPosition == 56)
            {
                PgnMove += "O-O-O";
            }
        }
    }
    else
    {
        PgnMove += GetPgnMove(MovingPiecePrimary.PieceType);

        switch (MovingPiecePrimary.PieceType)
        {
        case ChessPieceType::Knight:
                {
                    if (doubleDestination)
                    {
                        if (!doubleColumn)
                        {
                            PgnMove += GetColumnFromInt(srcCol);
                        }
                        else
                        {
                            if (doubleRow)
                            {
                                PgnMove += GetColumnFromInt(srcCol);
                            }

                            PgnMove += (char)srcRow;
                        }
                    }
                    break;
                }
        case ChessPieceType::Bishop:
                {
                    if (doubleDestination)
                    {
                        if (!doubleColumn)
                        {
                            PgnMove += GetColumnFromInt(srcCol);
                        }
                        else
                        {
                            if (doubleRow)
                            {
                                PgnMove += GetColumnFromInt(srcCol);
                            }

                            PgnMove += (char)srcRow;
                        }
                    }
                    break;
                }
        case ChessPieceType::Rook:
                {
                    if (doubleDestination)
                    {
                        if (!doubleColumn)
                        {
                            PgnMove += GetColumnFromInt(srcCol);
                        }
                        else
                        {
                            if (doubleRow)
                            {
                                PgnMove += GetColumnFromInt(srcCol);
                            }

                            PgnMove += (char)srcRow;
                        }
                    }
                    break;
                }
        case ChessPieceType::Queen:
                {
                    if (doubleDestination)
                    {
                        if (!doubleColumn)
                        {
                            PgnMove += GetColumnFromInt(srcCol);
                        }
                        else
                        {
                            if (doubleRow)
                            {
                                PgnMove += GetColumnFromInt(srcCol);
                            }

                            PgnMove += (char)srcRow;
                        }
                    }
                    break;
                }
        case ChessPieceType::Pawn:
                {
                    if (doubleDestination && srcCol != dstCol)
                    {
                        PgnMove += GetColumnFromInt(srcCol);
                    }
                    else if (TakenPiece.PieceType != ChessPieceType::None)
                    {
                        PgnMove += GetColumnFromInt(srcCol);
                    }
                    break;
                }
        }

        if (TakenPiece.PieceType != ChessPieceType::None)
        {

            PgnMove += "x";
        }

        PgnMove += GetColumnFromInt(dstCol);

        PgnMove += (char)dstRow;

        if (PawnPromotedTo == ChessPieceType::Queen)
        {
            PgnMove += "=Q";
        }
        else if (PawnPromotedTo == ChessPieceType::Rook)
        {
            PgnMove += "=R";
        }
        else if (PawnPromotedTo == ChessPieceType::Bishop)
        {
            PgnMove += "=B";
        }
        else if (PawnPromotedTo == ChessPieceType::Knight)
        {
            PgnMove += "=N";
        }
    }

    return PgnMove;
}

//private:
char MoveContent::GetBoardIndex(int col, int row)
{
    return (col + (row * 8));
}

string MoveContent::GetColumnFromInt(int column)
{
    switch (column)
    {
        case 0:
            return "a";
        case 1:
            return "b";
        case 2:
            return "c";
        case 3:
            return "d";
        case 4:
            return "e";
        case 5:
            return "f";
        case 6:
            return "g";
        case 7:
            return "h";
        default:
            return "Unknown";
    }
}

int MoveContent::GetIntFromColumn(char column)
{
    switch (column)
    {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        default:
            return -1;
    }
}

ChessPieceType MoveContent::GetPieceType(char c)
{
    switch (c)
    {
        case 'B':
            return ChessPieceType::Bishop;
        case 'K':
            return ChessPieceType::King;
        case 'N':
            return ChessPieceType::Knight;
        case 'Q':
            return ChessPieceType::Queen;
        case 'R':
            return ChessPieceType::Rook;
        default:
            return ChessPieceType::None;
    }
}

string MoveContent::GetPgnMove(ChessPieceType pieceType)
{
    switch (pieceType)
    {
        case ChessPieceType::Bishop:
            return "B";

        case ChessPieceType::King:
            return "K";

        case ChessPieceType::Knight:
            return "N";

        case ChessPieceType::Queen:
            return "Q";

        case ChessPieceType::Rook:
            return "R";
        default:
            return "";
    }
}

