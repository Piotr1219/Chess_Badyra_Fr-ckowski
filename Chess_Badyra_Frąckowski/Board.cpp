#include <string>
#include <list>
#include <stack>
#include "Engine.h"
#include "Board.h"
#include "Book.h"
#include "main.h"
#include "functions.h"
#include "Piece.h"
#include "Square.h"

class Board
{
public:
    Square[] Squares;

    bool InsufficientMaterial;

    int Score;

    unsigned long long int ZobristHash;

    //Game Over Flags
    bool BlackCheck;
    bool BlackMate;
    bool WhiteCheck;
    bool WhiteMate;
    bool StaleMate;

    byte HalfMoveClock;
    byte RepeatedMove;

    bool BlackCastled;
    bool WhiteCastled;

    bool BlackCanCastle;
    bool WhiteCanCastle;

    bool EndGamePhase;

    MoveContent LastMove;

    byte WhiteKingPosition;
    byte BlackKingPosition;

    bool BlackAttackBoard [64];
    bool WhiteAttackBoard [64];

    //Who initated En Passant
    ChessPieceColor EnPassantColor;
    //Positions liable to En Passant
    byte EnPassantPosition;

    ChessPieceColor WhoseMove;

    int MoveCount;

    //constructors

    //Default Constructor

    Board(string fen)
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

        if (fen.find("w") != std::string::npos)
        {
            WhoseMove = ChessPieceColor::White;
        }
        if (fen.find("b") != std::string::npos)
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
                    index = (byte)((int)index+1);
                }
                else if (c == '2' && (int)index < 62)
                {
                    index = (byte)((int)index + 2);
                }
                else if (c == '3' && (int)index < 61)
                {
                    index = (byte)((int)index + 3);
                }
                else if (c == '4' && (int)index < 60)
                {
                    index = (byte)((int)index + 4);
                }
                else if (c == '5' && (int)index < 59)
                {
                    index = (byte)((int)index + 5);
                }
                else if (c == '6' && (int)index < 58)
                {
                    index = (byte)((int)index + 6);
                }
                else if (c == '7' && (int)index < 57)
                {
                    index = (byte)((int)index + 7);
                }
                else if (c == '8' && (int)index < 56)
                {
                    index = (byte)((int)index + 8);
                }
                else if (c == 'P')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Pawn, ChessPieceColor::White);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'N')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Knight, ChessPieceColor::White);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'B')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Bishop, ChessPieceColor::White);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'R')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Rook, ChessPieceColor::White);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'Q')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Queen, ChessPieceColor::White);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'K')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::King, ChessPieceColor::White);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'p')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Pawn, ChessPieceColor::Black);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'n')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Knight, ChessPieceColor::Black);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'b')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Bishop, ChessPieceColor::Black);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'r')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Rook, ChessPieceColor::Black);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'q')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::Queen, ChessPieceColor::Black);
                    Squares[index].Piece.Moved = true;
                    index = (byte)((int)index + 1);
                }
                else if (c == 'k')
                {
                    Squares[index].Piece = new Piece(ChessPieceType::King, ChessPieceColor::Black);
                    Squares[index].Piece.Moved = true;
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
                    if (Squares[60].Piece != NULL)
                    {
                        if (Squares[60].Piece.PieceType == ChessPieceType::King)
                        {
                            Squares[60].Piece.Moved = false;
                        }
                    }

                    if (Squares[63].Piece != NULL)
                    {
                        if (Squares[63].Piece.PieceType == ChessPieceType::Rook)
                        {
                            Squares[63].Piece.Moved = false;
                        }
                    }

                    WhiteCastled = false;

                }
                else if (c == 'Q')
                {
                    if (Squares[60].Piece != NULL)
                    {
                        if (Squares[60].Piece.PieceType == ChessPieceType::King)
                        {
                            Squares[60].Piece.Moved = false;
                        }
                    }

                    if (Squares[56].Piece != NULL)
                    {
                        if (Squares[56].Piece.PieceType == ChessPieceType::Rook)
                        {
                            Squares[56].Piece.Moved = false;
                        }
                    }

                    WhiteCastled = false;
                }
                else if (c == 'k')
                {
                    if (Squares[4].Piece != NULL)
                    {
                        if (Squares[4].Piece.PieceType == ChessPieceType::King)
                        {
                            Squares[4].Piece.Moved = false;
                        }
                    }

                    if (Squares[7].Piece != NULL)
                    {
                        if (Squares[7].Piece.PieceType == ChessPieceType::Rook)
                        {
                            Squares[7].Piece.Moved = false;
                        }
                    }

                    BlackCastled = false;
                }
                else if (c == 'q')
                {
                    if (Squares[4].Piece != NULL)
                    {
                        if (Squares[4].Piece.PieceType == ChessPieceType::King)
                        {
                            Squares[4].Piece.Moved = false;
                        }
                    }

                    if (Squares[0].Piece != NULL)
                    {
                        if (Squares[0].Piece.PieceType == ChessPieceType::Rook)
                        {
                            Squares[0].Piece.Moved = false;
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

    Board()
    {
        Squares = new Square[64];

        for (int i = 0; i < 64; i++)
        {
            Squares[i] = new Square();
        }

        LastMove = new MoveContent();

        BlackCanCastle = true;
        WhiteCanCastle = true;

        //WhiteAttackBoard = new bool[64];
        //BlackAttackBoard = new bool[64];

    }

    Board(Square[] squares)
    {
        Squares = Square[64];

        for (int x = 0; x < 64; x++)
        {
            if (squares[x].Piece != NULL)
            {
                Squares[x].Piece = new Piece(squares[x].Piece);
            }
        }

        //WhiteAttackBoard = new bool[64];
        //BlackAttackBoard = new bool[64];

    };

        //Constructor
    Board(int score):Board()
    {
        Score = score;

        //WhiteAttackBoard = new bool[64];
        //BlackAttackBoard = new bool[64];

    }
    public:
        //Copy Constructor
    Board(const Board &board)
    {
        Squares = new Square[64];

        for (int x = 0; x < 64; x++)
        {
            if (board.Squares[x].Piece != NULL)
            {
                Squares[x] = new Square(board.Squares[x].Piece);
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

        LastMove = new MoveContent(board.LastMove);

        MoveCount = board.MoveCount;
    }

    //private methods

    private:
    bool PromotePawns(Board board, Piece piece, byte dstPosition, ChessPieceType promoteToPiece)
    {
        if (piece.PieceType == ChessPieceType::Pawn)
        {
            if (dstPosition < (byte)8)
            {
                board.Squares[dstPosition].Piece.PieceType = promoteToPiece;
                board.Squares[dstPosition].Piece.PieceValue = piece.CalculatePieceValue(promoteToPiece);
                board.Squares[dstPosition].Piece.PieceActionValue = piece.CalculatePieceActionValue(promoteToPiece);
                return true;
            }
            if (dstPosition > (byte)55)
            {
                board.Squares[dstPosition].Piece.PieceType = promoteToPiece;
                board.Squares[dstPosition].Piece.PieceValue = piece.CalculatePieceValue(promoteToPiece);
                board.Squares[dstPosition].Piece.PieceActionValue = piece.CalculatePieceActionValue(promoteToPiece);
                return true;
            }
        }

        return false;
    }

    void RecordEnPassant(ChessPieceColor pcColor, ChessPieceType pcType, Board board, byte srcPosition, byte dstPosition)
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

    bool SetEnpassantMove(Board board, byte srcPosition, byte dstPosition, ChessPieceColor pcColor)
    {
        if (board.EnPassantPosition != dstPosition)
        {
            return false;
        }

        if (pcColor == board.EnPassantColor)
        {
            return false;
        }

        if (board.Squares[srcPosition].Piece.PieceType != ChessPieceType::Pawn)
        {
            return false;
        }

        int pieceLocationOffset = 8;

        if (board.EnPassantColor == ChessPieceColor::White)
        {
            pieceLocationOffset = -8;
        }

        dstPosition = (byte)((int)dstPosition + pieceLocationOffset);

        Square sqr = board.Squares[dstPosition];

        board.LastMove.TakenPiece = PieceTaken(sqr.Piece.PieceColor, sqr.Piece.PieceType, sqr.Piece.Moved, dstPosition);

        board.Squares[dstPosition].Piece = NULL;

        //Reset HalfMoveClockCount if capture
        board.HalfMoveClock = (byte)0;

        return true;

    }

    void KingCastle(Board board, Piece piece, byte srcPosition, byte dstPosition)
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
                if (board.Squares[63].Piece != NULL)
                {
                    board.Squares[61].Piece = board.Squares[63].Piece;
                    board.Squares[63].Piece = NULL;
                    board.WhiteCastled = true;
                    board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[61].Piece.PieceColor, board.Squares[61].Piece.PieceType, board.Squares[61].Piece.Moved, 63, 61);
                    board.Squares[61].Piece.Moved = true;
                    return;
                }
            }
            //Castle Left
            else if (dstPosition == (byte)58)
            {
                //Ok we are casteling we need to move the Rook
                if (board.Squares[56].Piece != NULL)
                {
                    board.Squares[59].Piece = board.Squares[56].Piece;
                    board.Squares[56].Piece = NULL;
                    board.WhiteCastled = true;
                    board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[59].Piece.PieceColor, board.Squares[59].Piece.PieceType, board.Squares[59].Piece.Moved, 56, 59);
                    board.Squares[59].Piece.Moved = true;
                    return;
                }
            }
        }
        else if (piece.PieceColor == ChessPieceColor::Black && srcPosition == (byte)4)
        {
            if (dstPosition == (byte)6)
            {
                //Ok we are casteling we need to move the Rook
                if (board.Squares[7].Piece != NULL)
                {
                    board.Squares[5].Piece = board.Squares[7].Piece;
                    board.Squares[7].Piece = NULL;
                    board.BlackCastled = true;
                    board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[5].Piece.PieceColor, board.Squares[5].Piece.PieceType, board.Squares[5].Piece.Moved, 7, 5);
                    board.Squares[5].Piece.Moved = true;
                    return;
                }
            }
            //Castle Left
        else if (dstPosition == (byte)2)
        {
                //Ok we are casteling we need to move the Rook
                if (board.Squares[0].Piece != NULL)
                {
                    board.Squares[3].Piece = board.Squares[0].Piece;
                    board.Squares[0].Piece = NULL;
                    board.BlackCastled = true;
                    board.LastMove.MovingPieceSecondary = PieceMoving(board.Squares[3].Piece.PieceColor, board.Squares[3].Piece.PieceType, board.Squares[3].Piece.Moved, 0, 3);
                    board.Squares[3].Piece.Moved = true;
                    return;
                }
            }
        }

        return;
    }

    //region internal methods

            //Fast Copy
    public:
    Board FastCopy()
    {
        //Board* clonedBoard = new Board(Squares);
        Board cloneBoard(Squares);

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

    MoveContent MovePiece(Board board, byte srcPosition, byte dstPosition, ChessPieceType promoteToPiece)
    {
        Piece piece = board.Squares[srcPosition].Piece;

        //Record my last move
        board.LastMove = new MoveContent();



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
            Square sqr = board.Squares[dstPosition];

            if (sqr.Piece != NULL)
            {
                board.LastMove.TakenPiece = PieceTaken(sqr.Piece.PieceColor, sqr.Piece.PieceType,
                                                            sqr.Piece.Moved, dstPosition);
                board.HalfMoveClock = (byte)0;
            }
            else
            {
                board.LastMove.TakenPiece = PieceTaken(ChessPieceColor::White, ChessPieceType::None, false,
                                                            dstPosition);

            }
        }

        board.LastMove.MovingPiecePrimary = new PieceMoving(piece.PieceColor, piece.PieceType, piece.Moved, srcPosition, dstPosition);

        //Delete the piece in its source position
        board.Squares[srcPosition].Piece = NULL;

        //Add the piece to its new position
        piece.Moved = true;
        piece.Selected = false;
        board.Squares[dstPosition].Piece = piece;

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

    private:
    static string GetColumnFromByte(byte column)
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

    public:
    string ToString()
    {
        return Fen(false, *this);
    }
    bool isSlash(char c)
    {
        return c == ':';
    }
    static string Fen(bool boardOnly, Board board)
    {
        string output = "";
        byte blankSquares = (byte)0;

        for (int x = 0; x < 64; x++)
        {
            byte index = (byte)x;

            if (board.Squares[index].Piece != NULL)
            {
                if (blankSquares > (byte)0)
                {
                    output += std::to_string((int)blankSquares);
                    blankSquares = (byte)0;
                }
                if (board.Squares[index].Piece.PieceColor == ChessPieceColor::Black)
                {
                    output += Piece::GetPieceTypeShort(board.Squares[index].Piece.PieceType).ToLower();
                }
                else
                {
                    output += Piece::GetPieceTypeShort(board.Squares[index].Piece.PieceType);
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
            if (board.Squares[60].Piece != NULL)
            {
                if (board.Squares[60].Piece.Moved == false)
                {
                    if (board.Squares[63].Piece != NULL)
                    {
                        if (board.Squares[63].Piece.Moved == false)
                        {
                            castle += "K";
                        }
                    }
                    if (board.Squares[56].Piece != NULL)
                    {
                        if (board.Squares[56].Piece.Moved == false)
                        {
                            castle += "Q";
                        }
                    }
                }
            }
        }

        if (board.BlackCastled == false)
        {
            if (board.Squares[4].Piece != NULL)
            {
                if (board.Squares[4].Piece.Moved == false)
                {
                    if (board.Squares[7].Piece != NULL)
                    {
                        if (board.Squares[7].Piece.Moved == false)
                        {
                            castle += "k";
                        }
                    }
                    if (board.Squares[0].Piece != NULL)
                    {
                        if (board.Squares[0].Piece.Moved == false)
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

};
