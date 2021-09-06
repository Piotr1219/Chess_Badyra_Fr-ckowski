#include <string>
#include <list>
#include <stack>
#include <iostream>
#include <typeinfo>
#include "Engine.h"
//#include "Book.h"
//#include "Evaluations.h"
//#include "PieceMoves.h"
//#include "PieceTaken.h"
//#include "PieceValidMoves.h"
///#include "FileIO.h"
//#include "ResultBoards.h"
///#include "Search.h"


using namespace std;


string Engine::FEN()
{
    return Board::Fen(false, ChessBoard);
}

MoveContent Engine::LastMove()
{
    return ChessBoard.LastMove;
}


Engine::Difficulty Engine::GameDifficulty()
{
    if (PlyDepthSearched == 3)
    {
        return Difficulty::Easy;
    }
    else if (PlyDepthSearched == 5)
    {
        return Difficulty::Medium;
    }
    else if (PlyDepthSearched == 6)
    {
        return Difficulty::Hard;
    }
    else if (PlyDepthSearched == 7)
    {
        return Difficulty::VeryHard;
    }

    return Difficulty::Medium;
}
void Engine::setGameDifficulty(Difficulty value)
{
    if (value == Difficulty::Easy)
    {
        PlyDepthSearched = 3;
        GameTimeSettings = TimeSettings::Moves40In10Minutes;
    }
    else if (value == Difficulty::Medium)
    {
        PlyDepthSearched = 5;
        GameTimeSettings = TimeSettings::Moves40In20Minutes;
    }
    else if (value == Difficulty::Hard)
    {
        PlyDepthSearched = 6;
        GameTimeSettings = TimeSettings::Moves40In60Minutes;
    }
    else if (value == Difficulty::VeryHard)
    {
        PlyDepthSearched = 7;
        GameTimeSettings = TimeSettings::Moves40In90Minutes;
    }
}

ChessPieceColor Engine::WhoseMove()
{
    return ChessBoard.WhoseMove;
}
void Engine::setWhoseMove(ChessPieceColor value)
{
    ChessBoard.WhoseMove = value;
}

bool Engine::StaleMate()
{
    return ChessBoard.StaleMate;
}
void Engine::setStaleMate(bool value) {
    ChessBoard.StaleMate = value;
}
bool Engine::RepeatedMove()
{
    if (ChessBoard.RepeatedMove >= 3)
    {
        return true;
    }

    return false;
}

string Engine::PvLine()
{
    return pvLine;
}

bool Engine::FiftyMove()
{
    if (ChessBoard.HalfMoveClock >= 100)
    {
        return true;
    }

    return false;
}

bool Engine::InsufficientMaterial()
{
    return ChessBoard.InsufficientMaterial;
}


Engine::Engine()
{
    InitiateEngine();
    InitiateBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Engine::Engine(string fen)
{
    InitiateEngine();
    InitiateBoard(fen);
}

void Engine::NewGame()
{
    InitiateEngine();
    InitiateBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Engine::InitiateBoard(string fen)
{
    ChessBoard = Board(fen);

    if (fen != "")
    {
        PieceValidMoves::GenerateValidMoves(ChessBoard);
        //Evaluation eva1 = Evaluation();
        //eva1.EvaluateBoardScore(ChessBoard);
        EvaluateBoardScore2(ChessBoard);
    }
}

void Engine::InitiateEngine()
{
    setGameDifficulty(Difficulty::Easy);

    MoveHistory = list<MoveContent>();
    HumanPlayer = ChessPieceColor::White;
    OpeningBook = list<OpeningMove>();
    CurrentGameBook = list<OpeningMove>();
    PieceMoves::InitiateChessPieceMotion();
    LoadOpeningBook();
}

void Engine::SetChessPieceSelection(char boardColumn, char boardRow,
                                    bool selection)
{
    char index = GetBoardIndex(boardColumn, boardRow);

    if (ChessBoard.Squares[index].Piece1.PieceType != ChessPieceType::None)
    {
        return;
    }
    if (ChessBoard.Squares[index].Piece1.PieceColor != HumanPlayer)
    {
        return;
    }
    if (ChessBoard.Squares[index].Piece1.PieceColor != WhoseMove())
    {
        return;
    }
    ChessBoard.Squares[index].Piece1.Selected = selection;
}

int Engine::ValidateOpeningBook()
{
    return Book::ValidateOpeningBook(OpeningBook);
}

bool Engine::CheckForMate(ChessPieceColor whosTurn, Board& chessBoard)
{
    Search::SearchForMate(whosTurn, chessBoard, &chessBoard.BlackMate,
                            &chessBoard.WhiteMate, &chessBoard.StaleMate);

    //cout << "mates" << chessBoard.BlackMate << chessBoard.WhiteMate << chessBoard.StaleMate << endl;
    if (chessBoard.BlackMate || chessBoard.WhiteMate || chessBoard.StaleMate)
    {
        return true;
    }

    return false;
}

bool Engine::FindPlayBookMove(MoveContent* bestMove, Board& chessBoard, list<OpeningMove> openingBook)
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

            //bestMove = move.Moves[index];
            list<MoveContent>::iterator it = move.Moves.begin();
            advance(it, index);
            *bestMove = *it;
            return true;
        }
    }

    return false;
}

void Engine::Undo()
{
    if (!UndoChessBoard.isEmpty())
    {
        PieceTakenRemove(ChessBoard.LastMove);
        PieceTakenRemove(PreviousChessBoard.LastMove);

        ChessBoard = Board(UndoChessBoard);
        CurrentGameBook = list<OpeningMove>(UndoGameBook);

        PieceValidMoves::GenerateValidMoves(ChessBoard);
        //Evaluation eva1;
        //eva1.EvaluateBoardScore(ChessBoard);
        EvaluateBoardScore2(ChessBoard);
    }
}

char Engine::GetBoardIndex(char boardColumn, char boardRow)
{
    return (boardColumn + (boardRow * 8));
}

char* Engine::GetEnPassantMoves()
{
    if (ChessBoard.isEmpty())
    {
        return NULL;
    }

    char* returnArray = new char[2];

    returnArray[0] = (ChessBoard.EnPassantPosition % 8);
    returnArray[1] = (ChessBoard.EnPassantPosition / 8);

    return returnArray;
}

bool Engine::GetBlackMate()
{
    if (ChessBoard.isEmpty())
    {
        return false;
    }

    return ChessBoard.BlackMate;
}

bool Engine::GetWhiteMate()
{
    return ChessBoard.WhiteMate;
}

bool Engine::GetBlackCheck()
{
    return ChessBoard.BlackCheck;
}

bool Engine::GetWhiteCheck()
{
    return ChessBoard.WhiteCheck;
}

char Engine::GetRepeatedMove()
{
    return ChessBoard.RepeatedMove;
}

char Engine::GetHalfMoveClock()
{
    return ChessBoard.HalfMoveClock;
}

list<MoveContent> Engine::GetMoveHistory()
{
    return MoveHistory;
}

ChessPieceType Engine::GetPieceTypeAt(char boardColumn, char boardRow)
{
    char index = GetBoardIndex(boardColumn, boardRow);

    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return ChessPieceType::None;
    }

    return ChessBoard.Squares[index].Piece1.PieceType;
}

ChessPieceType Engine::GetPieceTypeAt(char index)
{
    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return ChessPieceType::None;
    }

    return ChessBoard.Squares[index].Piece1.PieceType;
}

ChessPieceColor Engine::GetPieceColorAt(char boardColumn, char boardRow)
{
    char index = GetBoardIndex(boardColumn, boardRow);

    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return ChessPieceColor::White;
    }
    return ChessBoard.Squares[index].Piece1.PieceColor;
}

ChessPieceColor Engine::GetPieceColorAt(char index)
{
    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return ChessPieceColor::White;
    }
    return ChessBoard.Squares[index].Piece1.PieceColor;
}

bool Engine::GetChessPieceSelected(char boardColumn, char boardRow)
{
    char index = GetBoardIndex(boardColumn, boardRow);

    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return false;
    }

    return ChessBoard.Squares[index].Piece1.Selected;
}

void Engine::GenerateValidMoves()
{
    PieceValidMoves::GenerateValidMoves(ChessBoard);
}

int Engine::EvaluateBoardScore()
{
    //Evaluation eva1;
    //eva1.EvaluateBoardScore(ChessBoard);
    EvaluateBoardScore2(ChessBoard);
    return ChessBoard.Score;
}

char** Engine::GetValidMoves(char boardColumn, char boardRow)
{
    char index = GetBoardIndex(boardColumn, boardRow);

    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return NULL;
    }

    //char** returnArray = char[ChessBoard.Squares[index].Piece1.ValidMoves.size()][3];
    char** returnArray = new char* [2]; // each element is a pointer to an array.
    for (size_t i = 0; i < 2; ++i)
        returnArray[i] = new char[ChessBoard.Squares[index].Piece1.ValidMoves.size()]; // build rows

    int counter = 0;

    for (auto& square : ChessBoard.Squares[index].Piece1.ValidMoves)
    //foreach(char square in ChessBoard.Squares[index].Piece.ValidMoves)
    {
        //returnArray[counter] = new char[2];
        returnArray[0][counter] = (square % 8);
        returnArray[1][counter] = (square / 8);
        counter++;
    }

    return returnArray;
}

int Engine::GetScore()
{
    return ChessBoard.Score;
}

char Engine::FindSourcePositon(ChessPieceType chessPieceType, ChessPieceColor chessPieceColor, char dstPosition, bool capture, int forceCol, int forceRow)
{
    Square square;

    if (dstPosition == ChessBoard.EnPassantPosition && chessPieceType == ChessPieceType::Pawn)
    {
        if (chessPieceColor == ChessPieceColor::White)
        {
            square = ChessBoard.Squares[dstPosition + 7];

            if (square.Piece1.PieceType != ChessPieceType::None)
            {
                if (square.Piece1.PieceType == ChessPieceType::Pawn)
                {
                    if (square.Piece1.PieceColor == chessPieceColor)
                    {
                        if ((dstPosition + 7) % 8 == forceCol || forceCol == -1)
                        {
                            return (dstPosition + 7);
                        }

                    }
                }
            }

            square = ChessBoard.Squares[dstPosition + 9];

            if (square.Piece1.PieceType != ChessPieceType::None)
            {
                if (square.Piece1.PieceType == ChessPieceType::Pawn)
                {
                    if (square.Piece1.PieceColor == chessPieceColor)
                    {
                        if ((dstPosition + 9) % 8 == forceCol || forceCol == -1)
                        {
                            return (dstPosition + 9);
                        }
                    }
                }
            }
        }
        else
        {
            if (dstPosition - 7 >= 0)
            {
                square = ChessBoard.Squares[dstPosition - 7];

                if (square.Piece1.PieceType != ChessPieceType::None)
                {
                    if (square.Piece1.PieceType == ChessPieceType::Pawn)
                    {
                        if (square.Piece1.PieceColor == chessPieceColor)
                        {
                            if ((dstPosition - 7) % 8 == forceCol || forceCol == -1)
                            {
                                return (dstPosition - 7);
                            }
                        }
                    }
                }
            }
            if (dstPosition - 9 >= 0)
            {
                square = ChessBoard.Squares[dstPosition - 9];

                if (square.Piece1.PieceType != ChessPieceType::None)
                {
                    if (square.Piece1.PieceType == ChessPieceType::Pawn)
                    {
                        if (square.Piece1.PieceColor == chessPieceColor)
                        {
                            if ((dstPosition - 9) % 8 == forceCol || forceCol == -1)
                            {
                                return (dstPosition - 9);
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

        //foreach(char move in square.Piece.ValidMoves)
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
                            return x;
                        }
                    }
                }

                //Capture
                if (ChessBoard.Squares[dstPosition].Piece1.PieceType != ChessPieceType::None)
                {
                    if (ChessBoard.Squares[dstPosition].Piece1.PieceColor != chessPieceColor)
                    {
                        if (x % 8 == forceCol || forceCol == -1)
                        {
                            if ((x / 8) == (forceRow) || forceRow == -1)
                            {
                                return x;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

bool Engine::IsValidMoveAN(string move)
{
    char sourceColumn = 0, sourceRow = 0, destinationColumn = 0, destinationRow = 0;
    MoveContent::ParseAN(move, &sourceColumn, &sourceRow, &destinationColumn, &destinationRow);
    return IsValidMove(sourceColumn, sourceRow, destinationColumn, destinationRow);
}

bool Engine::IsValidMove(char srcPosition, char dstPosition)
{
    if (ChessBoard.isEmpty())
    {
        return false;
    }

    if (ChessBoard.Squares == NULL)
    {
        return false;
    }

    if (ChessBoard.Squares[srcPosition].Piece1.PieceType == ChessPieceType::None)
    {
        return false;
    }

    //foreach(char bs in ChessBoard.Squares[srcPosition].Piece.ValidMoves)
    for (auto& bs : ChessBoard.Squares[srcPosition].Piece1.ValidMoves)
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

bool Engine::IsValidMove(char sourceColumn, char sourceRow, char destinationColumn, char destinationRow)
{
    if (ChessBoard.isEmpty())
    {
        return false;
    }

    if (ChessBoard.Squares == NULL)
    {
        return false;
    }

    char index = GetBoardIndex(sourceColumn, sourceRow);

    if (ChessBoard.Squares[index].Piece1.PieceType == ChessPieceType::None)
    {
        return false;
    }
    //cout << "rozpoczecie sprawdzania valid moves" << endl;
    //foreach(char bs in ChessBoard.Squares[index].Piece.ValidMoves)
    for (auto& bs : ChessBoard.Squares[index].Piece1.ValidMoves)
    {
        //cout << "proba valid moves " << bs << endl;
        if (bs % 8 == destinationColumn)
        {
            if ((bs / 8) == destinationRow)
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

bool Engine::IsGameOver()
{
    if (ChessBoard.StaleMate)
    {
        return true;
    }
    if (ChessBoard.WhiteMate || ChessBoard.BlackMate)
    {
        return true;
    }
    if (ChessBoard.HalfMoveClock >= 100)
    {
        return true;
    }
    if (ChessBoard.RepeatedMove >= 3)
    {
        return true;
    }

    if (ChessBoard.InsufficientMaterial)
    {
        return true;
    }
    return false;
}

bool Engine::IsTie()
{
    if (ChessBoard.StaleMate)
    {
        return true;
    }

    if (ChessBoard.HalfMoveClock >= 100)
    {
        return true;
    }
    if (ChessBoard.RepeatedMove >= 3)
    {
        return true;
    }

    if (ChessBoard.InsufficientMaterial)
    {
        return true;
    }

    return false;
}
bool Engine::MovePiece(char srcPosition, char dstPosition)
{
    Piece piece = ChessBoard.Squares[srcPosition].Piece1;

    PreviousChessBoard = Board(ChessBoard);
    UndoChessBoard = Board(ChessBoard);
    UndoGameBook = list<OpeningMove>(CurrentGameBook);

    Board::MovePiece(ChessBoard, srcPosition, dstPosition, PromoteToPieceType);

    ChessBoard.LastMove.GeneratePGNString(ChessBoard.Squares);

    PieceValidMoves::GenerateValidMoves(ChessBoard);
    //Evaluation eva1;
    //eva1.EvaluateBoardScore(ChessBoard);
    EvaluateBoardScore2(ChessBoard);

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
    SaveCurrentGameMove(ChessBoard, PreviousChessBoard, CurrentGameBook, ChessBoard.LastMove);

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

void Engine::PieceTakenAdd(MoveContent lastMove)
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

void Engine::PieceTakenRemove(MoveContent lastMove)
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

bool Engine::MovePieceAN(string move)
{
    char sourceColumn = 0, sourceRow = 0, destinationColumn = 0, destinationRow = 0;
    MoveContent::ParseAN(move, &sourceColumn, &sourceRow, &destinationColumn, &destinationRow);
    return MovePiece(sourceColumn, sourceRow, destinationColumn, destinationRow);
}

bool Engine::MovePiece(char sourceColumn, char sourceRow, char destinationColumn, char destinationRow)
{
    char srcPosition = (sourceColumn + (sourceRow * 8));
    char dstPosition = (destinationColumn + (destinationRow * 8));

    return MovePiece(srcPosition, dstPosition);
}

void Engine::SetChessPiece(Piece piece, char index)
{
    ChessBoard.Squares[index].Piece1 = Piece(piece);

}



void Engine::AiPonderMove()
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

    //cout << "przed szukaniem mata " << endl;
    if (CheckForMate(WhoseMove(), ChessBoard))
    {
        //cout << "znaleziony mat" << endl;
        Thinking = false;
        return;
    }

    MoveContent bestMove = MoveContent();

    //If there is no playbook move search for the best move
    if (FindPlayBookMove(&bestMove, ChessBoard, OpeningBook) == false
        || ChessBoard.HalfMoveClock > 90 || ChessBoard.RepeatedMove >= 2)
    {
        if (FindPlayBookMove(&bestMove, ChessBoard, CurrentGameBook) == false ||
            ChessBoard.HalfMoveClock > 90 || ChessBoard.RepeatedMove >= 2)
        {
            cout << "PlyDepthSearched jest typu: " << typeid(PlyDepthSearched).name() <<", jej wartosc: " << int(PlyDepthSearched) << endl;
            bestMove = Search::IterativeSearch(ChessBoard, PlyDepthSearched, &NodesSearched, &NodesQuiessence, pvLine, &PlyDepthReached, &RootMovesSearched, CurrentGameBook);
            //cout << "przed ruchem komputera " << bestMove.MovingPiecePrimary.SrcPosition << "   " << bestMove.MovingPiecePrimary.DstPosition << endl;
        }
    }

    //Make the move 
    cout << "Udalo sie wyjsc z petli wyszukiwania ruchu\n";
    PreviousChessBoard = Board(ChessBoard);

    RootMovesSearched = resultBoards.Positions.size();

    cout << "ruch komputera " << int(bestMove.MovingPiecePrimary.SrcPosition) << "   " << int(bestMove.MovingPiecePrimary.DstPosition) << endl;
    Board::MovePiece(ChessBoard, bestMove.MovingPiecePrimary.SrcPosition, bestMove.MovingPiecePrimary.DstPosition, ChessPieceType::Queen);

    ChessBoard.LastMove.GeneratePGNString(ChessBoard.Squares);

    SaveCurrentGameMove(ChessBoard, PreviousChessBoard, CurrentGameBook, bestMove);

    for (int x = 0; x < 64; x++)
    {
        Square sqr = ChessBoard.Squares[x];

        if (sqr.Piece1.PieceType == ChessPieceType::None)
            continue;

        sqr.Piece1.DefendedValue = 0;
        sqr.Piece1.AttackedValue = 0;
    }

    //PieceValidMoves::GenerateValidMoves(ChessBoard);
    //Evaluation eva1;
    //eva1.EvaluateBoardScore(ChessBoard);
    EvaluateBoardScore2(ChessBoard);

    PieceTakenAdd(ChessBoard.LastMove);

    cout << "MoveHistory size before adding move: " << MoveHistory.size() << endl;
    MoveHistory.push_back(ChessBoard.LastMove);
    cout << "MoveHistory size after adding move: " << MoveHistory.size() << endl;

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
    cout << "Koniec funckji AoPonderMove\n";
}

//region test

//public PerformanceTest.PerformanceResult RunPerformanceTest(int depth = 5)
//{
//    return PerformanceTest.RunPerfTest(depth, ChessBoard);
//}

//region file io

bool Engine::SaveGame(string filePath)
{
    //return FileIO::SaveGame(filePath, ChessBoard, WhoseMove(), MoveHistory);
    return true;
}

bool Engine::LoadGame(string filePath)
{
    //return FileIO::LoadGame(filePath, &ChessBoard, WhoseMove(), &MoveHistory, &CurrentGameBook, &UndoGameBook);
    return true;
}

bool Engine::LoadOpeningBook()
{
    OpeningBook = Book::LoadOpeningBook();

    return true;
}




//end of file
