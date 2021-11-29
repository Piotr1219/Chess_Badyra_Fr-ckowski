#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"
#include "PieceMoves.h"
#include "PieceTaken.h"
//#include "PieceSquareTable.h"
//#include "PieceValidMoves.h"
#include "Square.h"
#include "FileIO.h"
//#include "Test.h"
#include "Search.h"

using namespace std;

class Engine
{
public:
    list<OpeningMove> CurrentGameBook;
    list<OpeningMove> UndoGameBook;

//private:
    //inline static 
    Board ChessBoard;

private:
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
    inline static ChessPieceColor HumanPlayer;
    bool Thinking;
    bool TrainingMode;

    //Stats
    int NodesSearched;
    int NodesQuiessence;
    char PlyDepthSearched;
    char PlyDepthReached;
    char RootMovesSearched;

    TimeSettings GameTimeSettings;
    
    string FEN();

    MoveContent LastMove();

    Difficulty GameDifficulty();
    void setGameDifficulty(Difficulty value);

    ChessPieceColor WhoseMove();
    void setWhoseMove(ChessPieceColor value);

    bool StaleMate();
    void setStaleMate(bool value);
    bool RepeatedMove();

    string PvLine();

    bool FiftyMove();
    bool InsufficientMaterial();

    Engine();

    Engine(string fen);

    void NewGame();

    void InitiateBoard(string fen);

    void SetChessPieceSelection(char boardColumn, char boardRow,
        bool selection);

    int ValidateOpeningBook();

    void Undo();

    char* GetEnPassantMoves();

    bool GetBlackMate();

    bool GetWhiteMate();

    bool GetBlackCheck();

    bool GetWhiteCheck();

    char GetRepeatedMove();

    char GetHalfMoveClock();

    list<MoveContent> GetMoveHistory();

    ChessPieceType GetPieceTypeAt(char boardColumn, char boardRow);

    ChessPieceType GetPieceTypeAt(char index);

    ChessPieceColor GetPieceColorAt(char boardColumn, char boardRow);

    ChessPieceColor GetPieceColorAt(char index);

    bool GetChessPieceSelected(char boardColumn, char boardRow);

    void GenerateValidMoves();
    int EvaluateBoardScore();

    char** GetValidMoves(char boardColumn, char boardRow);

    int GetScore();

    char FindSourcePositon(ChessPieceType chessPieceType, ChessPieceColor chessPieceColor, char dstPosition, bool capture, int forceCol, int forceRow);

    bool IsValidMoveAN(string move);

    bool IsValidMove(char srcPosition, char dstPosition);

    bool IsValidMove(char sourceColumn, char sourceRow, char destinationColumn, char destinationRow);

    bool IsGameOver();

    bool IsTie();
    bool MovePiece(char srcPosition, char dstPosition);

    bool MovePieceAN(string move);

    bool MovePiece(char sourceColumn, char sourceRow, char destinationColumn, char destinationRow);

    void SetChessPiece(Piece piece, char index);

    void AiPonderMove();

    //PerformanceTest.PerformanceResult RunPerformanceTest(int depth = 5);


    bool SaveGame(string filePath);

    bool LoadGame(string filePath);

    bool LoadOpeningBook();

    private:
    void InitiateEngine();
    bool CheckForMate(ChessPieceColor whosTurn, Board& chessBoard);
    bool FindPlayBookMove(MoveContent* bestMove, Board& chessBoard, list<OpeningMove> openingBook);
    char GetBoardIndex(char boardColumn, char boardRow);
    void PieceTakenAdd(MoveContent lastMove);

    void PieceTakenRemove(MoveContent lastMove);
};
