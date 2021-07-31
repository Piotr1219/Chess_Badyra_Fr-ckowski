#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Board.h"
#include "Book.h"
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
//#include "Square.h"

using namespace std;

class Engine
{
public:
    
    enum Difficulty
    {
        Easy,
        Medium,
        Hard,
        VeryHard
    };
    /*
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

    ChessPieceType PromoteToPieceType = ChessPieceType.Queen;

    PiecesTaken PiecesTakenCount = new PiecesTaken();

    //State Variables
    */
    static ChessPieceColor HumanPlayer;
    
    bool Thinking;
    bool TrainingMode;

    //Stats
    int NodesSearched;
    int NodesQuiessence;
    byte PlyDepthSearched;
    byte PlyDepthReached;
    byte RootMovesSearched;
    
    //TimeSettings GameTimeSettings;
    
    string FEN();

    MoveContent LastMove();

    Difficulty GameDifficulty();
    void setGameDifficulty(Difficulty value);

    ChessPieceColor WhoseMove();

    bool StaleMate();
    bool RepeatedMove();

    string PvLine();

    bool FiftyMove();
    bool InsufficientMaterial();

    Engine();

    Engine(string fen);

    void NewGame();

    void InitiateBoard(string fen);

    void SetChessPieceSelection(byte boardColumn, byte boardRow,
        bool selection);

    int ValidateOpeningBook();

    void Undo();

    byte GetEnPassantMoves();

    bool GetBlackMate();

    bool GetWhiteMate();

    bool GetBlackCheck();

    bool GetWhiteCheck();

    byte GetRepeatedMove();

    byte GetHalfMoveClock();

    list<MoveContent> GetMoveHistory();

    ChessPieceType GetPieceTypeAt(byte boardColumn, byte boardRow);

    ChessPieceType GetPieceTypeAt(byte index);

    ChessPieceColor GetPieceColorAt(byte boardColumn, byte boardRow);

    ChessPieceColor GetPieceColorAt(byte index);

    bool GetChessPieceSelected(byte boardColumn, byte boardRow);

    void GenerateValidMoves();
    int EvaluateBoardScore();

    byte** GetValidMoves(byte boardColumn, byte boardRow);

    int GetScore();

    byte FindSourcePositon(ChessPieceType chessPieceType, ChessPieceColor chessPieceColor, byte dstPosition, bool capture, int forceCol, int forceRow);

    bool IsValidMoveAN(string move);

    bool IsValidMove(byte srcPosition, byte dstPosition);

    bool IsValidMove(byte sourceColumn, byte sourceRow, byte destinationColumn, byte destinationRow);

    bool IsGameOver();

    bool IsTie();
    bool MovePiece(byte srcPosition, byte dstPosition);

    bool MovePieceAN(string move);

    bool MovePiece(byte sourceColumn, byte sourceRow, byte destinationColumn, byte destinationRow);

    void SetChessPiece(Piece piece, byte index);

    void AiPonderMove();

    PerformanceTest.PerformanceResult RunPerformanceTest(int depth = 5);


    bool SaveGame(string filePath);

    bool LoadGame(string filePath);

    bool LoadOpeningBook();

    private:
    void InitiateEngine();
    bool CheckForMate(ChessPieceColor whosTurn, Board* chessBoard);
    bool FindPlayBookMove(MoveContent* bestMove, Board chessBoard, list<OpeningMove> openingBook);
    byte GetBoardIndex(byte boardColumn, byte boardRow);
    void PieceTakenAdd(MoveContent lastMove);

    void PieceTakenRemove(MoveContent lastMove);
};
