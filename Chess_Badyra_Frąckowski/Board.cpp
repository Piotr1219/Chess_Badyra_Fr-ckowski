#include <string>
#include <list>
#include <stack>
#include <algorithm>
#include <iostream>
//#include "Engine.h"
#include "Board.h"
//#include "Book.h"
//#include "main.h"
///#include "functions.h"
//#include "Piece.h"
///#include "MoveContent.h"
///#include "Square.h"


    //Default Constructor

Board::Board(string fen)
{
    byte index = (byte)0;
    byte spc = (byte)0;

    WhiteCastled = true;
    BlackCastled = true;

    byte spacers = (byte)0;

    WhoseMove = ChessPieceColor::White;

    if (fen.find("a3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)40;
    }
    else if (fen.find("b3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)41;
    }
    else if (fen.find("c3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)42;
    }
    else if (fen.find("d3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)43;
    }
    else if (fen.find("e3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)44;
    }
    else if (fen.find("f3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)45;
    }
    else if (fen.find("g3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)46;
    }
    else if (fen.find("h3") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::White;
        EnPassantPosition = (byte)47;
    }


    if (fen.find("a6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)16;
    }
    else if (fen.find("b6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)17;
    }
    else if (fen.find("c6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)18;
    }
    else if (fen.find("d6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)19;
    }
    else if (fen.find("e6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)20;
    }
    else if (fen.find("f6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)21;
    }
    else if (fen.find("g6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)22;
    }
    else if (fen.find("h6") != std::string::npos)
    {
        EnPassantColor = ChessPieceColor::Black;
        EnPassantPosition = (byte)23;
    }

    if (fen.find(" w ") != std::string::npos)
    {
        WhoseMove = ChessPieceColor::White;
    }
    if (fen.find(" b ") != std::string::npos)
    {
        WhoseMove = ChessPieceColor::Black;
    }

    //foreach(char c in fen)
    for (auto& c : fen)
    {

        if ((int)index < 64 && (int)spc == 0)
        {
            if (c == '1' && (int)index < 63)
            {
                for (int i = 0; i < 1; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index+1);
            }
            else if (c == '2' && (int)index < 62)
            {
                for (int i = 0; i < 2; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 2);
            }
            else if (c == '3' && (int)index < 61)
            {
                for (int i = 0; i < 3; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 3);
            }
            else if (c == '4' && (int)index < 60)
            {
                for (int i = 0; i < 4; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 4);
            }
            else if (c == '5' && (int)index < 59)
            {
                for (int i = 0; i < 5; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 5);
            }
            else if (c == '6' && (int)index < 58)
            {
                for (int i = 0; i < 6; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 6);
            }
            else if (c == '7' && (int)index < 57)
            {
                for (int i = 0; i < 7; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 7);
            }
            else if (c == '8' && (int)index < 56)
            {
                for (int i = 0; i < 8; i++) {
                    Squares[(short)index + i].Piece1 = Piece(ChessPieceType::None, ChessPieceColor::White);
                }
                index = (byte)((int)index + 8);
            }
            else if (c == 'P')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Pawn, ChessPieceColor::White);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'N')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Knight, ChessPieceColor::White);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'B')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Bishop, ChessPieceColor::White);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'R')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Rook, ChessPieceColor::White);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'Q')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Queen, ChessPieceColor::White);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'K')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::King, ChessPieceColor::White);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'p')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Pawn, ChessPieceColor::Black);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'n')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Knight, ChessPieceColor::Black);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'b')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Bishop, ChessPieceColor::Black);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'r')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Rook, ChessPieceColor::Black);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'q')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::Queen, ChessPieceColor::Black);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == 'k')
            {
                Squares[(short)index].Piece1 = Piece(ChessPieceType::King, ChessPieceColor::Black);
                Squares[(short)index].Piece1.Moved = true;
                index = (byte)((int)index + 1);
            }
            else if (c == '/')
            {
                continue;
            }
            else if (c == ' ')
            {
                spc = (byte)((int)spc + 1);
            }
        }
        else
        {

            if (c == 'K')
            {
                if (Squares[60].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[60].Piece1.PieceType == ChessPieceType::King)
                    {
                        Squares[60].Piece1.Moved = false;
                    }
                }

                if (Squares[63].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[63].Piece1.PieceType == ChessPieceType::Rook)
                    {
                        Squares[63].Piece1.Moved = false;
                    }
                }

                WhiteCastled = false;

            }
            else if (c == 'Q')
            {
                if (Squares[60].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[60].Piece1.PieceType == ChessPieceType::King)
                    {
                        Squares[60].Piece1.Moved = false;
                    }
                }

                if (Squares[56].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[56].Piece1.PieceType == ChessPieceType::Rook)
                    {
                        Squares[56].Piece1.Moved = false;
                    }
                }

                WhiteCastled = false;
            }
            else if (c == 'k')
            {
                if (Squares[4].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[4].Piece1.PieceType == ChessPieceType::King)
                    {
                        Squares[4].Piece1.Moved = false;
                    }
                }

                if (Squares[7].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[7].Piece1.PieceType == ChessPieceType::Rook)
                    {
                        Squares[7].Piece1.Moved = false;
                    }
                }

                BlackCastled = false;
            }
            else if (c == 'q')
            {
                if (Squares[4].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[4].Piece1.PieceType == ChessPieceType::King)
                    {
                        Squares[4].Piece1.Moved = false;
                    }
                }

                if (Squares[0].Piece1.PieceType != ChessPieceType::None)
                {
                    if (Squares[0].Piece1.PieceType == ChessPieceType::Rook)
                    {
                        Squares[0].Piece1.Moved = false;
                    }
                }

                BlackCastled = false;
            }
            else if (c == ' ')
            {
                spacers = (byte)((int)spacers + 1);
            }
            else if (c == '1' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 1);
            }
            else if (c == '2' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 2);
            }
            else if (c == '3' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 3);
            }
            else if (c == '4' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 4);
            }
            else if (c == '5' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 5);
            }
            else if (c == '6' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 6);
            }
            else if (c == '7' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 7);
            }
            else if (c == '8' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 8);
            }
            else if (c == '9' && spacers == (byte)4)
            {
                HalfMoveClock = (byte)(((int)HalfMoveClock * 10) + 9);
            }
            else if (c == '0' && spacers == (byte)4)
            {
                MoveCount = ((MoveCount * 10) + 0);
            }
            else if (c == '1' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 1);
            }
            else if (c == '2' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 2);
            }
            else if (c == '3' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 3);
            }
            else if (c == '4' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 4);
            }
            else if (c == '5' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 5);
            }
            else if (c == '6' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 6);
            }
            else if (c == '7' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 7);
            }
            else if (c == '8' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 8);
            }
            else if (c == '9' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 9);
            }
            else if (c == '0' && spacers == (byte)5)
            {
                MoveCount = ((MoveCount * 10) + 0);
            }

        }
    }
    
}


Board::Board()
{
    //Squares = new Square[64];

    for (int i = 0; i < 64; i++)
    {
        Squares[i] = Square();
    }

    LastMove = MoveContent();

    BlackCanCastle = true;
    WhiteCanCastle = true;

    //WhiteAttackBoard = new bool[64];
    //BlackAttackBoard = new bool[64];

}

bool Board::isEmpty() {
    bool result = true;
    for (int i = 0; i < 64; i++)
    {
        if (Squares[i].Piece1.PieceType != ChessPieceType::None) {
            result = false;
        }
    }
    return result;
}

Board::Board(Square squares[])
{
    //Squares = Square[64];

    for (int x = 0; x < 64; x++)
    {
        if (squares[x].Piece1.PieceType != ChessPieceType::None)
        {
            Squares[x].Piece1 = Piece(squares[x].Piece1);
        }
    }

    //WhiteAttackBoard = new bool[64];
    //BlackAttackBoard = new bool[64];

};

        //Constructor
Board::Board(int score):Board()
{
    Score = score;

    //WhiteAttackBoard = new bool[64];
    //BlackAttackBoard = new bool[64];

}
    //public:
        //Copy Constructor
Board::Board(const Board &board)
{
    //Squares = new Square[64];

    for (int x = 0; x < 64; x++)
    {
        if (board.Squares[x].Piece1.PieceType != ChessPieceType::None)
        {
            Squares[x] = Square(board.Squares[x].Piece1);
        }
    }

    //WhiteAttackBoard = new bool[64];
    //BlackAttackBoard = new bool[64];

    for (int x = 0; x < 64; x++)
    {
        WhiteAttackBoard[x] = board.WhiteAttackBoard[x];
        BlackAttackBoard[x] = board.BlackAttackBoard[x];
    }

    EndGamePhase = board.EndGamePhase;

    HalfMoveClock = board.HalfMoveClock;
    RepeatedMove = board.RepeatedMove;

    WhiteCastled = board.WhiteCastled;
    BlackCastled = board.BlackCastled;

    WhiteCanCastle = board.WhiteCanCastle;
    BlackCanCastle = board.BlackCanCastle;

    WhiteKingPosition = board.WhiteKingPosition;
    BlackKingPosition = board.BlackKingPosition;

    BlackCheck = board.BlackCheck;
    WhiteCheck = board.WhiteCheck;
    StaleMate = board.StaleMate;
    WhiteMate = board.WhiteMate;
    BlackMate = board.BlackMate;
    WhoseMove = board.WhoseMove;
    EnPassantPosition = board.EnPassantPosition;
    EnPassantColor = board.EnPassantColor;

    ZobristHash = board.ZobristHash;

    Score = board.Score;

    LastMove = MoveContent(board.LastMove);

    MoveCount = board.MoveCount;
}

    //private methods

    //private:
bool Board::PromotePawns(Board board, Piece piece, byte dstPosition, ChessPieceType promoteToPiece)
{
    if (piece.PieceType == ChessPieceType::Pawn)
    {
        if (dstPosition < (byte)8)
        {
            board.Squares[(short)dstPosition].Piece1.PieceType = promoteToPiece;
            board.Squares[(short)dstPosition].Piece1.PieceValue = piece.CalculatePieceValue(promoteToPiece);
            board.Squares[(short)dstPosition].Piece1.PieceActionValue = piece.CalculatePieceActionValue(promoteToPiece);
            return true;
        }
        if (dstPosition > (byte)55)
        {
            board.Squares[(short)dstPosition].Piece1.PieceType = promoteToPiece;
            board.Squares[(short)dstPosition].Piece1.PieceValue = piece.CalculatePieceValue(promoteToPiece);
            board.Squares[(short)dstPosition].Piece1.PieceActionValue = piece.CalculatePieceActionValue(promoteToPiece);
            return true;
        }
    }

    return false;
}

void Board::RecordEnPassant(ChessPieceColor pcColor, ChessPieceType pcType, Board board, byte srcPosition, byte dstPosition)
{
    //Record En Passant if Pawn Moving
    if (pcType == ChessPieceType::Pawn)
    {
        //Reset HalfMoveClockCount if pawn moved
        board.HalfMoveClock = (byte)0;

        int difference = (int)srcPosition - (int)dstPosition;

        if (difference == 16 || difference == -16)
        {
            board.EnPassantPosition = (byte)((int)dstPosition + (difference / 2));
            board.EnPassantColor = pcColor;
        }
    }
}

bool Board::SetEnpassantMove(Board board, byte srcPosition, byte dstPosition, ChessPieceColor pcColor)
{
    if (board.EnPassantPosition != dstPosition)
    {
        return false;
    }

    if (pcColor == board.EnPassantColor)
    {
        return false;
    }

    if (board.Squares[(short)srcPosition].Piece1.PieceType != ChessPieceType::Pawn)
    {
        return false;
    }

    int pieceLocationOffset = 8;

    if (board.EnPassantColor == ChessPieceColor::White)
    {
        pieceLocationOffset = -8;
    }

    dstPosition = (byte)((int)dstPosition + pieceLocationOffset);

    Square sqr = board.Squares[(short)dstPosition];

    board.LastMove.TakenPiece = PieceTaken(sqr.Piece1.PieceColor, sqr.Piece1.PieceType, sqr.Piece1.Moved, dstPosition);

    board.Squares[(short)dstPosition].Piece1.PieceType = ChessPieceType::None;

    //Reset HalfMoveClockCount if capture
    board.HalfMoveClock = (byte)0;

    return true;

}

void Board::KingCastle(Board board, Piece piece, byte srcPosition, byte dstPosition)
{
    if (piece.PieceType != ChessPieceType::King)
    {
        return;
    }

    //Lets see if this is a casteling move.
    if (piece.PieceColor == ChessPieceColor::White && srcPosition == (byte)60)
    {
        //Castle Right
        if (dstPosition == (byte)62)
        {
            //Ok we are casteling we need to move the Rook
            if (board.Squares[63].Piece1.PieceType != ChessPieceType::None)
            {
                board.Squares[61].Piece1 = board.Squares[63].Piece1;
                board.Squares[63].Piece1.PieceType = ChessPieceType::None;
                board.WhiteCastled = true;
                board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[61].Piece1.PieceColor, board.Squares[61].Piece1.PieceType, board.Squares[61].Piece1.Moved, (byte)63, (byte)61);
                board.Squares[61].Piece1.Moved = true;
                return;
            }
        }
        //Castle Left
        else if (dstPosition == (byte)58)
        {
            //Ok we are casteling we need to move the Rook
            if (board.Squares[56].Piece1.PieceType != ChessPieceType::None)
            {
                board.Squares[59].Piece1 = board.Squares[56].Piece1;
                board.Squares[56].Piece1.PieceType = ChessPieceType::None;
                board.WhiteCastled = true;
                board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[59].Piece1.PieceColor, board.Squares[59].Piece1.PieceType, board.Squares[59].Piece1.Moved, (byte)56, (byte)59);
                board.Squares[59].Piece1.Moved = true;
                return;
            }
        }
    }
    else if (piece.PieceColor == ChessPieceColor::Black && srcPosition == (byte)4)
    {
        if (dstPosition == (byte)6)
        {
            //Ok we are casteling we need to move the Rook
            if (board.Squares[7].Piece1.PieceType != ChessPieceType::None)
            {
                board.Squares[5].Piece1 = board.Squares[7].Piece1;
                board.Squares[7].Piece1.PieceType = ChessPieceType::None;
                board.BlackCastled = true;
                board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[5].Piece1.PieceColor, board.Squares[5].Piece1.PieceType, board.Squares[5].Piece1.Moved, (byte)7, (byte)5);
                board.Squares[5].Piece1.Moved = true;
                return;
            }
        }
        //Castle Left
    else if (dstPosition == (byte)2)
    {
            //Ok we are casteling we need to move the Rook
            if (board.Squares[0].Piece1.PieceType != ChessPieceType::None)
            {
                board.Squares[3].Piece1 = board.Squares[0].Piece1;
                board.Squares[0].Piece1.PieceType = ChessPieceType::None;
                board.BlackCastled = true;
                board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[3].Piece1.PieceColor, board.Squares[3].Piece1.PieceType, board.Squares[3].Piece1.Moved, (byte)0, (byte)3);
                board.Squares[3].Piece1.Moved = true;
                return;
            }
        }
    }

    return;
}

    //region internal methods

            //Fast Copy
    //public:
Board Board::FastCopy()
{
    //Board* clonedBoard = new Board(Squares);
    Board clonedBoard(Squares);

    clonedBoard.EndGamePhase = EndGamePhase;
    clonedBoard.WhoseMove = WhoseMove;
    clonedBoard.MoveCount = MoveCount;
    clonedBoard.HalfMoveClock = HalfMoveClock;
    clonedBoard.ZobristHash = ZobristHash;
    clonedBoard.BlackCastled = BlackCastled;
    clonedBoard.WhiteCastled = WhiteCastled;

    clonedBoard.WhiteCanCastle = WhiteCanCastle;
    clonedBoard.BlackCanCastle = BlackCanCastle;

    //WhiteAttackBoard = new bool[64];
    //BlackAttackBoard = new bool[64];

    return clonedBoard;
}

MoveContent Board::MovePiece(Board board, byte srcPosition, byte dstPosition, ChessPieceType promoteToPiece)
{
    Piece piece = board.Squares[(short)srcPosition].Piece1;

    //Record my last move
    board.LastMove = MoveContent();



    if (piece.PieceColor == ChessPieceColor::Black)
    {
        board.MoveCount++;
    }
    //Add One to HalfMoveClockCount to check for 50 move limit.
    board.HalfMoveClock = (byte)((int)board.HalfMoveClock+1);

    //En Passant
    if (board.EnPassantPosition > (byte)0)
    {
        board.LastMove.EnPassantOccured = SetEnpassantMove(board, srcPosition, dstPosition, piece.PieceColor);
    }

    if (!board.LastMove.EnPassantOccured)
    {
        Square sqr = board.Squares[(short)dstPosition];

        if (sqr.Piece1.PieceType != ChessPieceType::None)
        {
            board.LastMove.TakenPiece = PieceTaken(sqr.Piece1.PieceColor, sqr.Piece1.PieceType,
                                                        sqr.Piece1.Moved, dstPosition);
            board.HalfMoveClock = (byte)0;
        }
        else
        {
            board.LastMove.TakenPiece = PieceTaken(ChessPieceColor::White, ChessPieceType::None, false,
                                                        dstPosition);

        }
    }

    board.LastMove.MovingPiecePrimary = PieceMoving(piece.PieceColor, piece.PieceType, piece.Moved, srcPosition, dstPosition);

    //Delete the piece in its source position
    board.Squares[(short)srcPosition].Piece1.PieceType = ChessPieceType::None;

    //Add the piece to its new position
    piece.Moved = true;
    piece.Selected = false;
    board.Squares[(short)dstPosition].Piece1 = piece;

    //Reset EnPassantPosition
    board.EnPassantPosition = (byte)0;

    //Record En Passant if Pawn Moving
    if (piece.PieceType == ChessPieceType::Pawn)
    {
        board.HalfMoveClock = (byte)0;
        RecordEnPassant(piece.PieceColor, piece.PieceType, board, srcPosition, dstPosition);
    }

    board.WhoseMove = board.WhoseMove == ChessPieceColor::White ? ChessPieceColor::Black : ChessPieceColor::White;

    KingCastle(board, piece, srcPosition, dstPosition);

    //Promote Pawns 
    if (PromotePawns(board, piece, dstPosition, promoteToPiece))
    {
        board.LastMove.PawnPromotedTo = promoteToPiece;
    }
    else
    {
        board.LastMove.PawnPromotedTo = ChessPieceType::None;
    }

    if (board.HalfMoveClock >= (byte)100)
    {
        board.StaleMate = true;
    }

    return board.LastMove;
}

//private:
string Board::GetColumnFromByte(byte column)
{
    switch (column)
    {
        case (byte)0:
            return "a";
        case (byte)1:
            return "b";
        case (byte)2:
            return "c";
        case (byte)3:
            return "d";
        case (byte)4:
            return "e";
        case (byte)5:
            return "f";
        case (byte)6:
            return "g";
        case (byte)7:
            return "h";
        default:
            return "a";
    }
}

//public:
string Board::ToString()
{
    return Fen(false, *this);
}
bool Board::isSlash(char c)
{
    return c == ':';
}
string Board::Fen(bool boardOnly, Board board)
{
    string output = "";
    byte blankSquares = (byte)0;

    for (int x = 0; x < 64; x++)
    {
        byte index = (byte)x;

        if (board.Squares[(short)index].Piece1.PieceType != ChessPieceType::None)
        {
            if (blankSquares > (byte)0)
            {
                output += std::to_string((int)blankSquares);
                blankSquares = (byte)0;
            }
            if (board.Squares[(short)index].Piece1.PieceColor == ChessPieceColor::Black)
            {
                string p = Piece::GetPieceTypeShort(board.Squares[(short)index].Piece1.PieceType);
                for_each(p.begin(), p.end(), [](char& c) {
                    c = ::tolower(c);
                });
                output += p;
            }
            else
            {
                output += Piece::GetPieceTypeShort(board.Squares[(short)index].Piece1.PieceType);
            }
        }
        else
        {
            blankSquares = (byte)((int)blankSquares + 1);
        }

        if (x % 8 == 7)
        {
            if (blankSquares > (byte)0)
            {
                output += std::to_string((int)blankSquares);
                output += "/";
                blankSquares = (byte)0;
            }
            else
            {
                if (x > 0 && x != 63)
                {
                    output += "/";
                }
            }
        }
    }
    string end = "/";
    if (output.compare(output.length() - end.length(), end.length(), end))
    {
        //output = output.TrimEnd('/');
        output = output.substr(0, output.size() - 1);
    }

    if (board.WhoseMove == ChessPieceColor::White)
    {
        output += " w ";
    }
    else
    {
        output += " b ";
    }

    string castle = "-";

    if (board.WhiteCastled == false)
    {
        if (board.Squares[60].Piece1.PieceType != ChessPieceType::None)
        {
            if (board.Squares[60].Piece1.Moved == false)
            {
                if (board.Squares[63].Piece1.PieceType != ChessPieceType::None)
                {
                    if (board.Squares[63].Piece1.Moved == false)
                    {
                        castle += "K";
                    }
                }
                if (board.Squares[56].Piece1.PieceType != ChessPieceType::None)
                {
                    if (board.Squares[56].Piece1.Moved == false)
                    {
                        castle += "Q";
                    }
                }
            }
        }
    }

    if (board.BlackCastled == false)
    {
        if (board.Squares[4].Piece1.PieceType != ChessPieceType::None)
        {
            if (board.Squares[4].Piece1.Moved == false)
            {
                if (board.Squares[7].Piece1.PieceType != ChessPieceType::None)
                {
                    if (board.Squares[7].Piece1.Moved == false)
                    {
                        castle += "k";
                    }
                }
                if (board.Squares[0].Piece1.PieceType != ChessPieceType::None)
                {
                    if (board.Squares[0].Piece1.Moved == false)
                    {
                        castle += "q";
                    }
                }
            }
        }
    }

    if (castle != "-")
    {
        while (castle.at(0) == '-' || castle.at(0) == '-') {
            castle.erase(0, 1);
        }
        //castle = castle.TrimStart('-');
    }
    output += castle;

    if (board.EnPassantPosition != (byte)0)
    {
        output += " " + Board::GetColumnFromByte((byte)((int)board.EnPassantPosition % 8)) + "" + to_string((8 - ((int)board.EnPassantPosition / 8))) + " ";
    }
    else
    {
        output += " - ";
    }

    if (!boardOnly)
    {
        output += (char)board.HalfMoveClock + " ";
        output += (char)board.MoveCount;
    }
    //return output.Trim();
    return trim(output);
}

