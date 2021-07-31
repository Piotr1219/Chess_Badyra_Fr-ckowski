#include <string>
#include <list>
#include <stack>
#include "Engine.h"
//#include "Board.h"
#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
#include "Evaluations.h"
//#include "PGN.h"
#include "PieceMoves.h"
#include "PieceTaken.h"
//#include "PieceSquareTable.h"
#include "PieceValidMoves.h"
//#include "Square.h"
#include "FileIO.h"
#include "ResultBoards.h"
#include "Search.h"


using namespace std;


class Engine
{
public:
    list<OpeningMove> CurrentGameBook;
    list<OpeningMove> UndoGameBook;

private:
    static Board ChessBoard;
    Board PreviousChessBoard;
    Board UndoChessBoard;

    list<MoveContent> MoveHistory;
    list<OpeningMove> OpeningBook;

    string pvLine;
public:
    enum Difficulty
    {
        Easy,
        Medium,
        Hard,
        VeryHard
    };

    enum TimeSettings
    {
        Moves40In5Minutes,
        Moves40In10Minutes,
        Moves40In20Minutes,
        Moves40In30Minutes,
        Moves40In40Minutes,
        Moves40In60Minutes,
        Moves40In90Minutes,
    };
    
public:
    ChessPieceType PromoteToPieceType = ChessPieceType::Queen;

    PiecesTaken PiecesTakenCount = PiecesTaken();

    //State Variables
    static ChessPieceColor HumanPlayer;
    bool Thinking;
    bool TrainingMode;

    //Stats
    int NodesSearched;
    int NodesQuiessence;
    byte PlyDepthSearched;
    byte PlyDepthReached;
    byte RootMovesSearched;

    TimeSettings GameTimeSettings;

    string FEN()
    {
        return Board::Fen(false, ChessBoard);
    }

    MoveContent LastMove()
    {
        return ChessBoard.LastMove;
    }

    Difficulty GameDifficulty()
    {
        if (PlyDepthSearched == (byte)3)
        {
            return Difficulty::Easy;
        }
        else if (PlyDepthSearched == (byte)5)
        {
            return Difficulty::Medium;
        }
        else if (PlyDepthSearched == (byte)6)
        {
            return Difficulty::Hard;
        }
        else if (PlyDepthSearched == (byte)7)
        {
            return Difficulty::VeryHard;
        }

        return Difficulty::Medium;
    }
    void setGameDifficulty(Difficulty value)
    {
        if (value == Difficulty::Easy)
        {
            PlyDepthSearched = (byte)3;
            GameTimeSettings = TimeSettings::Moves40In10Minutes;
        }
        else if (value == Difficulty::Medium)
        {
            PlyDepthSearched = (byte)5;
            GameTimeSettings = TimeSettings::Moves40In20Minutes;
        }
        else if (value == Difficulty::Hard)
        {
            PlyDepthSearched = (byte)6;
            GameTimeSettings = TimeSettings::Moves40In60Minutes;
        }
        else if (value == Difficulty::VeryHard)
        {
            PlyDepthSearched = (byte)7;
            GameTimeSettings = TimeSettings::Moves40In90Minutes;
        }
    }

    static ChessPieceColor WhoseMove()
    {
        return ChessBoard.WhoseMove;
    }
    void serWhoseMove(ChessPieceColor value)
    {
        ChessBoard.WhoseMove = value;
    }

    bool StaleMate()
    {
        return ChessBoard.StaleMate;
    }
    void setStaleMate(bool value) {
        ChessBoard.StaleMate = value;
    }
    bool RepeatedMove()
    {
        if ((short)ChessBoard.RepeatedMove >= 3)
        {
            return true;
        }

        return false;
    }

    string PvLine()
    {
        return pvLine;
    }

    bool FiftyMove()
    {
        if ((short)ChessBoard.HalfMoveClock >= 100)
        {
            return true;
        }

        return false;
    }

    bool InsufficientMaterial()
    {
        return ChessBoard.InsufficientMaterial;
    }


    Engine()
    {
        InitiateEngine();
        InitiateBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    Engine(string fen)
    {
        InitiateEngine();
        InitiateBoard(fen);
    }

    void NewGame()
    {
        InitiateEngine();
        InitiateBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    void InitiateBoard(string fen)
    {
        ChessBoard = Board(fen);

        if (fen != "")
        {
            PieceValidMoves::GenerateValidMoves(ChessBoard);
            Evaluation eva1 = Evaluation();
            eva1.EvaluateBoardScore(ChessBoard);
        }
    }

    void InitiateEngine()
    {
        setGameDifficulty(Difficulty::Medium);

        MoveHistory = list<MoveContent>();
        HumanPlayer = ChessPieceColor::White;
        OpeningBook = list<OpeningMove>();
        CurrentGameBook = list<OpeningMove>();
        PieceMoves::InitiateChessPieceMotion();
        LoadOpeningBook();
    }

    void SetChessPieceSelection(byte boardColumn, byte boardRow,
                                        bool selection)
    {
        byte index = GetBoardIndex(boardColumn, boardRow);

        if (ChessBoard.Squares[(short)index].Piece1.PieceType != ChessPieceType::None)
        {
            return;
        }
        if (ChessBoard.Squares[(short)index].Piece1.PieceColor != HumanPlayer)
        {
            return;
        }
        if (ChessBoard.Squares[(short)index].Piece1.PieceColor != WhoseMove())
        {
            return;
        }
        ChessBoard.Squares[(short)index].Piece1.Selected = selection;
    }

    int ValidateOpeningBook()
    {
        return Book::ValidateOpeningBook(OpeningBook);
    }

    private:
    bool CheckForMate(ChessPieceColor whosTurn, Board chessBoard)
    {
        Search::SearchForMate(whosTurn, chessBoard, &chessBoard.BlackMate,
                                &chessBoard.WhiteMate, &chessBoard.StaleMate);

        if (chessBoard.BlackMate || chessBoard.WhiteMate || chessBoard.StaleMate)
        {
            return true;
        }

        return false;
    }

    bool FindPlayBookMove(MoveContent* bestMove, Board chessBoard, list<OpeningMove> openingBook)
    {
        //Get the Hash for the current Board;
        string boardFen = Board::Fen(true, chessBoard);

        //Check the Opening Move Book
        //for (OpeningMove move = openingBook.begin(); move != openingBook.end(); move++)
        for (OpeningMove & move : openingBook)
        {
            //if (move.StartingFEN.Contains(boardFen))
            if(move.StartingFEN.find(boardFen) != std::string::npos)
            {
                int index = 0;

                //bestMove = move.Moves[(short)index];
                list<MoveContent>::iterator it = move.Moves.begin();
                advance(it, index);
                *bestMove = *it;
                return true;
            }
        }

        return false;
    }

    public:
    void Undo()
    {
        if (!UndoChessBoard.isEmpty())
        {
            PieceTakenRemove(ChessBoard.LastMove);
            PieceTakenRemove(PreviousChessBoard.LastMove);

            ChessBoard = Board(UndoChessBoard);
            CurrentGameBook = list<OpeningMove>(UndoGameBook);

            PieceValidMoves::GenerateValidMoves(ChessBoard);
            Evaluation eva1;
            eva1.EvaluateBoardScore(ChessBoard);
        }
    }

    private:
    byte GetBoardIndex(byte boardColumn, byte boardRow)
    {
        return (byte)((int)boardColumn + ((int)boardRow * 8));
    }

    public:
    byte* GetEnPassantMoves()
    {
        if (ChessBoard.isEmpty())
        {
            return NULL;
        }

        byte* returnArray = new byte[2];

        returnArray[0] = (byte)((short)ChessBoard.EnPassantPosition % 8);
        returnArray[1] = (byte)((short)ChessBoard.EnPassantPosition / 8);

        return returnArray;
    }

    bool GetBlackMate()
    {
        if (ChessBoard.isEmpty())
        {
            return false;
        }

        return ChessBoard.BlackMate;
    }

    bool GetWhiteMate()
    {
        return ChessBoard.WhiteMate;
    }

    bool GetBlackCheck()
    {
        return ChessBoard.BlackCheck;
    }

    bool GetWhiteCheck()
    {
        return ChessBoard.WhiteCheck;
    }

    byte GetRepeatedMove()
    {
        return ChessBoard.RepeatedMove;
    }

    byte GetHalfMoveClock()
    {
        return ChessBoard.HalfMoveClock;
    }

    list<MoveContent> GetMoveHistory()
    {
        return MoveHistory;
    }

    ChessPieceType GetPieceTypeAt(byte boardColumn, byte boardRow)
    {
        byte index = GetBoardIndex(boardColumn, boardRow);

        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return ChessPieceType::None;
        }

        return ChessBoard.Squares[(short)index].Piece1.PieceType;
    }

    ChessPieceType GetPieceTypeAt(byte index)
    {
        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return ChessPieceType::None;
        }

        return ChessBoard.Squares[(short)index].Piece1.PieceType;
    }

    ChessPieceColor GetPieceColorAt(byte boardColumn, byte boardRow)
    {
        byte index = GetBoardIndex(boardColumn, boardRow);

        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return ChessPieceColor::White;
        }
        return ChessBoard.Squares[(short)index].Piece1.PieceColor;
    }

    ChessPieceColor GetPieceColorAt(byte index)
    {
        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return ChessPieceColor::White;
        }
        return ChessBoard.Squares[(short)index].Piece1.PieceColor;
    }

    bool GetChessPieceSelected(byte boardColumn, byte boardRow)
    {
        byte index = GetBoardIndex(boardColumn, boardRow);

        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return false;
        }

        return ChessBoard.Squares[(short)index].Piece1.Selected;
    }

    void GenerateValidMoves()
    {
        PieceValidMoves::GenerateValidMoves(ChessBoard);
    }

    int EvaluateBoardScore()
    {
        Evaluation eva1;
        eva1.EvaluateBoardScore(ChessBoard);
        return ChessBoard.Score;
    }

    byte** GetValidMoves(byte boardColumn, byte boardRow)
    {
        byte index = GetBoardIndex(boardColumn, boardRow);

        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return NULL;
        }

        //byte** returnArray = byte[ChessBoard.Squares[(short)index].Piece1.ValidMoves.size()][3];
        byte** returnArray = new byte* [2]; // each element is a pointer to an array.
        for (size_t i = 0; i < 2; ++i)
            returnArray[i] = new byte[ChessBoard.Squares[(short)index].Piece1.ValidMoves.size()]; // build rows

        int counter = 0;

        for (auto& square : ChessBoard.Squares[(short)index].Piece1.ValidMoves)
        //foreach(byte square in ChessBoard.Squares[index].Piece.ValidMoves)
        {
            //returnArray[counter] = new byte[2];
            returnArray[0][counter] = (byte)((short)square % 8);
            returnArray[1][counter] = (byte)((short)square / 8);
            counter++;
        }

        return returnArray;
    }

    int GetScore()
    {
        return ChessBoard.Score;
    }

    byte FindSourcePositon(ChessPieceType chessPieceType, ChessPieceColor chessPieceColor, byte dstPosition, bool capture, int forceCol, int forceRow)
    {
        Square square;

        if (dstPosition == ChessBoard.EnPassantPosition && chessPieceType == ChessPieceType::Pawn)
        {
            if (chessPieceColor == ChessPieceColor::White)
            {
                square = ChessBoard.Squares[(int)dstPosition + 7];

                if (square.Piece1.PieceType != ChessPieceType::None)
                {
                    if (square.Piece1.PieceType == ChessPieceType::Pawn)
                    {
                        if (square.Piece1.PieceColor == chessPieceColor)
                        {
                            if (((int)dstPosition + 7) % 8 == forceCol || forceCol == -1)
                            {
                                return (byte)((int)dstPosition + 7);
                            }

                        }
                    }
                }

                square = ChessBoard.Squares[(int)dstPosition + 9];

                if (square.Piece1.PieceType != ChessPieceType::None)
                {
                    if (square.Piece1.PieceType == ChessPieceType::Pawn)
                    {
                        if (square.Piece1.PieceColor == chessPieceColor)
                        {
                            if (((int)dstPosition + 9) % 8 == forceCol || forceCol == -1)
                            {
                                return (byte)((int)dstPosition + 9);
                            }
                        }
                    }
                }
            }
            else
            {
                if ((int)dstPosition - 7 >= 0)
                {
                    square = ChessBoard.Squares[(int)dstPosition - 7];

                    if (square.Piece1.PieceType != ChessPieceType::None)
                    {
                        if (square.Piece1.PieceType == ChessPieceType::Pawn)
                        {
                            if (square.Piece1.PieceColor == chessPieceColor)
                            {
                                if (((int)dstPosition - 7) % 8 == forceCol || forceCol == -1)
                                {
                                    return (byte)((int)dstPosition - 7);
                                }
                            }
                        }
                    }
                }
                if ((int)dstPosition - 9 >= 0)
                {
                    square = ChessBoard.Squares[(int)dstPosition - 9];

                    if (square.Piece1.PieceType != ChessPieceType::None)
                    {
                        if (square.Piece1.PieceType == ChessPieceType::Pawn)
                        {
                            if (square.Piece1.PieceColor == chessPieceColor)
                            {
                                if (((int)dstPosition - 9) % 8 == forceCol || forceCol == -1)
                                {
                                    return (byte)((int)dstPosition - 9);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int x = 0; x < 64; x++)
        {
            square = ChessBoard.Squares[x];

            if (square.Piece1.PieceType != ChessPieceType::None)
                continue;
            if (square.Piece1.PieceType != chessPieceType)
                continue;
            if (square.Piece1.PieceColor != chessPieceColor)
                continue;

            //foreach(byte move in square.Piece.ValidMoves)
            for (auto& move : square.Piece1.ValidMoves)
            {
                if (move == dstPosition)
                {
                    if (!capture)
                    {
                        if ((x / 8) == (forceRow) || forceRow == -1)
                        {
                            if (x % 8 == forceCol || forceCol == -1)
                            {
                                return (byte)x;
                            }
                        }
                    }

                    //Capture
                    if (ChessBoard.Squares[(short)dstPosition].Piece1.PieceType != ChessPieceType::None)
                    {
                        if (ChessBoard.Squares[(short)dstPosition].Piece1.PieceColor != chessPieceColor)
                        {
                            if (x % 8 == forceCol || forceCol == -1)
                            {
                                if ((x / 8) == (forceRow) || forceRow == -1)
                                {
                                    return (byte)x;
                                }
                            }
                        }
                    }
                }
            }
        }

        return (byte)0;
    }

    bool IsValidMoveAN(string move)
    {
        byte sourceColumn = (byte)0, sourceRow = (byte)0, destinationColumn = (byte)0, destinationRow = (byte)0;
        MoveContent::ParseAN(move, &sourceColumn, &sourceRow, &destinationColumn, &destinationRow);
        return IsValidMove(sourceColumn, sourceRow, destinationColumn, destinationRow);
    }

    bool IsValidMove(byte srcPosition, byte dstPosition)
    {
        if (ChessBoard.isEmpty())
        {
            return false;
        }

        if (ChessBoard.Squares == NULL)
        {
            return false;
        }

        if (ChessBoard.Squares[(short)srcPosition].Piece1.PieceType == ChessPieceType::None)
        {
            return false;
        }

        //foreach(byte bs in ChessBoard.Squares[srcPosition].Piece.ValidMoves)
        for (auto& bs : ChessBoard.Squares[(short)srcPosition].Piece1.ValidMoves)
        {
            if (bs == dstPosition)
            {
                return true;
            }
        }

        if (dstPosition == ChessBoard.EnPassantPosition)
        {
            return true;
        }

        return false;
    }

    bool IsValidMove(byte sourceColumn, byte sourceRow, byte destinationColumn, byte destinationRow)
    {
        if (ChessBoard.isEmpty())
        {
            return false;
        }

        if (ChessBoard.Squares == NULL)
        {
            return false;
        }

        byte index = GetBoardIndex(sourceColumn, sourceRow);

        if (ChessBoard.Squares[(short)index].Piece1.PieceType == ChessPieceType::None)
        {
            return false;
        }

        //foreach(byte bs in ChessBoard.Squares[index].Piece.ValidMoves)
        for (auto& bs : ChessBoard.Squares[(short)index].Piece1.ValidMoves)
        {
            if ((short)bs % 8 == (short)destinationColumn)
            {
                if ((byte)((short)bs / 8) == destinationRow)
                {
                    return true;
                }
            }
        }

        /*index = GetBoardIndex(destinationColumn, destinationRow);

        if (index == ChessBoard.EnPassantPosition && ChessBoard.EnPassantPosition > 0)
        {
            return true;
        }*/

        return false;
    }

    bool IsGameOver()
    {
        if (ChessBoard.StaleMate)
        {
            return true;
        }
        if (ChessBoard.WhiteMate || ChessBoard.BlackMate)
        {
            return true;
        }
        if ((short)ChessBoard.HalfMoveClock >= 100)
        {
            return true;
        }
        if ((short)ChessBoard.RepeatedMove >= 3)
        {
            return true;
        }

        if (ChessBoard.InsufficientMaterial)
        {
            return true;
        }
        return false;
    }

    bool IsTie()
    {
        if (ChessBoard.StaleMate)
        {
            return true;
        }

        if ((short)ChessBoard.HalfMoveClock >= 100)
        {
            return true;
        }
        if ((short)ChessBoard.RepeatedMove >= 3)
        {
            return true;
        }

        if (ChessBoard.InsufficientMaterial)
        {
            return true;
        }

        return false;
    }
    bool MovePiece(byte srcPosition, byte dstPosition)
    {
        Piece piece = ChessBoard.Squares[(short)srcPosition].Piece1;

        PreviousChessBoard = Board(ChessBoard);
        UndoChessBoard = Board(ChessBoard);
        UndoGameBook = list<OpeningMove>(CurrentGameBook);

        Board::MovePiece(ChessBoard, srcPosition, dstPosition, PromoteToPieceType);

        ChessBoard.LastMove.GeneratePGNString(ChessBoard);

        PieceValidMoves::GenerateValidMoves(ChessBoard);
        Evaluation eva1;
        eva1.EvaluateBoardScore(ChessBoard);

        //If there is a check in place, check if this is still true;
        if (piece.PieceColor == ChessPieceColor::White)
        {
            if (ChessBoard.WhiteCheck)
            {
                //Invalid Move
                ChessBoard = Board(PreviousChessBoard);
                PieceValidMoves::GenerateValidMoves(ChessBoard);
                return false;
            }
        }
        else if (piece.PieceColor == ChessPieceColor::Black)
        {
            if (ChessBoard.BlackCheck)
            {
                //Invalid Move
                ChessBoard = Board(PreviousChessBoard);
                PieceValidMoves::GenerateValidMoves(ChessBoard);
                return false;
            }
        }

        MoveHistory.push_back(ChessBoard.LastMove);
        FileIO::SaveCurrentGameMove(ChessBoard, PreviousChessBoard, CurrentGameBook, ChessBoard.LastMove);

        CheckForMate(WhoseMove(), ChessBoard);
        PieceTakenAdd(ChessBoard.LastMove);

        if (ChessBoard.WhiteMate || ChessBoard.BlackMate)
        {
            LastMove().PgnMove += "#";
        }
        else if (ChessBoard.WhiteCheck || ChessBoard.BlackCheck)
        {
            LastMove().PgnMove += "+";
        }

        return true;
    }

    private:
    void PieceTakenAdd(MoveContent lastMove)
    {
        if (lastMove.TakenPiece.PieceType != ChessPieceType::None)
        {
            if (lastMove.TakenPiece.PieceColor == ChessPieceColor::White)
            {
                if (lastMove.TakenPiece.PieceType == ChessPieceType::Queen)
                {
                    PiecesTakenCount.WhiteQueen++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Rook)
                {
                    PiecesTakenCount.WhiteRook++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Bishop)
                {
                    PiecesTakenCount.WhiteBishop++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Knight)
                {
                    PiecesTakenCount.WhiteKnight++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Pawn)
                {
                    PiecesTakenCount.WhitePawn++;
                }
            }
            if (ChessBoard.LastMove.TakenPiece.PieceColor == ChessPieceColor::Black)
            {
                if (lastMove.TakenPiece.PieceType == ChessPieceType::Queen)
                {
                    PiecesTakenCount.BlackQueen++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Rook)
                {
                    PiecesTakenCount.BlackRook++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Bishop)
                {
                    PiecesTakenCount.BlackBishop++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Knight)
                {
                    PiecesTakenCount.BlackKnight++;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Pawn)
                {
                    PiecesTakenCount.BlackPawn++;
                }
            }
        }
    }

    void PieceTakenRemove(MoveContent lastMove)
    {
        if (lastMove.TakenPiece.PieceType != ChessPieceType::None)
        {
            if (lastMove.TakenPiece.PieceColor == ChessPieceColor::White)
            {
                if (lastMove.TakenPiece.PieceType == ChessPieceType::Queen)
                {
                    PiecesTakenCount.WhiteQueen--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Rook)
                {
                    PiecesTakenCount.WhiteRook--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Bishop)
                {
                    PiecesTakenCount.WhiteBishop--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Knight)
                {
                    PiecesTakenCount.WhiteKnight--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Pawn)
                {
                    PiecesTakenCount.WhitePawn--;
                }
            }
            if (lastMove.TakenPiece.PieceColor == ChessPieceColor::Black)
            {
                if (lastMove.TakenPiece.PieceType == ChessPieceType::Queen)
                {
                    PiecesTakenCount.BlackQueen--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Rook)
                {
                    PiecesTakenCount.BlackRook--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Bishop)
                {
                    PiecesTakenCount.BlackBishop--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Knight)
                {
                    PiecesTakenCount.BlackKnight--;
                }
                else if (lastMove.TakenPiece.PieceType == ChessPieceType::Pawn)
                {
                    PiecesTakenCount.BlackPawn--;
                }
            }
        }
    }

    public:
    bool MovePieceAN(string move)
    {
        byte sourceColumn = (byte)0, sourceRow = (byte)0, destinationColumn = (byte)0, destinationRow = (byte)0;
        MoveContent::ParseAN(move, &sourceColumn, &sourceRow, &destinationColumn, &destinationRow);
        return MovePiece(sourceColumn, sourceRow, destinationColumn, destinationRow);
    }

    bool MovePiece(byte sourceColumn, byte sourceRow, byte destinationColumn, byte destinationRow)
    {
        byte srcPosition = (byte)((int)sourceColumn + ((int)sourceRow * 8));
        byte dstPosition = (byte)((int)destinationColumn + ((int)destinationRow * 8));

        return MovePiece(srcPosition, dstPosition);
    }

    void SetChessPiece(Piece piece, byte index)
    {
        ChessBoard.Squares[(short)index].Piece1 = Piece(piece);

    }



    void AiPonderMove()
    {
        Thinking = true;

        /* Fix added to prevent premature declaration of checkmate against computer's king.
            *
            * The original version only looked at squares that were available for the black king to move to PRIOR to white's latest move.
            * So... suppose you had a situation like this:
            *	r4r2/pppb1p1k/8/3p2Q1/q4P2/2np4/6PP/5RK1/ w - 0 27
            *  ... and moved the white queen from G5 to H5.
            *	At the start of white's move, the black king has 5 possible moves... 4 of which are attackable by white, and noted by
            *	GenerateValidMoves in WhiteAttackBoard[]. When AiPonderMove executes, it immediately eliminates those 4 squares as options
            *	for the black king, even though 2 of them are now safe because no white piece can attack them. However, square 7 is now
            *	directly in the queen's attack path, so it's eliminated as an option as well. Boom, premature checkmate... game over.
        */
        ChessBoard.BlackMate = false;
        ChessBoard.WhiteMate = false;
        PieceValidMoves::GenerateValidMoves(ChessBoard);

        NodesSearched = 0;

        ResultBoards resultBoards = ResultBoards();
        resultBoards.Positions = list<Board>();

        if (CheckForMate(WhoseMove(), ChessBoard))
        {
            Thinking = false;
            return;
        }

        MoveContent bestMove = MoveContent();

        //If there is no playbook move search for the best move
        if (FindPlayBookMove(&bestMove, ChessBoard, OpeningBook) == false
            || (short)ChessBoard.HalfMoveClock > 90 || (short)ChessBoard.RepeatedMove >= 2)
        {
            if (FindPlayBookMove(&bestMove, ChessBoard, CurrentGameBook) == false ||
                (short)ChessBoard.HalfMoveClock > 90 || (short)ChessBoard.RepeatedMove >= 2)
            {
                bestMove = Search::IterativeSearch(ChessBoard, PlyDepthSearched, &NodesSearched, &NodesQuiessence, pvLine, &PlyDepthReached, &RootMovesSearched, CurrentGameBook);
            }
        }

        //Make the move 
        PreviousChessBoard = Board(ChessBoard);

        RootMovesSearched = (byte)resultBoards.Positions.size();

        Board::MovePiece(ChessBoard, bestMove.MovingPiecePrimary.SrcPosition, bestMove.MovingPiecePrimary.DstPosition, ChessPieceType::Queen);

        ChessBoard.LastMove.GeneratePGNString(ChessBoard);

        FileIO::SaveCurrentGameMove(ChessBoard, PreviousChessBoard, CurrentGameBook, bestMove);

        for (int x = 0; x < 64; x++)
        {
            Square sqr = ChessBoard.Squares[x];

            if (sqr.Piece1.PieceType == ChessPieceType::None)
                continue;

            sqr.Piece1.DefendedValue = 0;
            sqr.Piece1.AttackedValue = 0;
        }

        PieceValidMoves::GenerateValidMoves(ChessBoard);
        Evaluation eva1;
        eva1.EvaluateBoardScore(ChessBoard);

        PieceTakenAdd(ChessBoard.LastMove);

        MoveHistory.push_back(ChessBoard.LastMove);

        if (CheckForMate(WhoseMove(), ChessBoard))
        {
            Thinking = false;

            if (ChessBoard.WhiteMate || ChessBoard.BlackMate)
            {
                LastMove().PgnMove += "#";
            }

            return;
        }

        if (ChessBoard.WhiteCheck || ChessBoard.BlackCheck)
        {
            LastMove().PgnMove += "+";
        }

        Thinking = false;
    }

    //region test

    //public PerformanceTest.PerformanceResult RunPerformanceTest(int depth = 5)
    //{
    //    return PerformanceTest.RunPerfTest(depth, ChessBoard);
    //}

    //region file io

    public:
    bool SaveGame(string filePath)
    {
        return FileIO::SaveGame(filePath, ChessBoard, WhoseMove(), MoveHistory);
    }

    bool LoadGame(string filePath)
    {
        return FileIO::LoadGame(filePath, &ChessBoard, WhoseMove(), &MoveHistory, &CurrentGameBook, &UndoGameBook);
    }

    bool LoadOpeningBook()
    {
        OpeningBook = Book::LoadOpeningBook();

        return true;
    }



};

//end of file
