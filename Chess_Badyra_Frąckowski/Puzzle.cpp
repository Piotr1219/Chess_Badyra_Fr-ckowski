#include <string>
#include <list>
#include <stack>
#include <ctime>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"
//#include "PieceMoves.h"
//#include "PieceSquareTable.h"
//#include "PieceValidMoves.h"
//#include "Square.h"
#include "Puzzle.h"


Engine Puzzle::NewPuzzleKnightBishopKing()
{
    Engine engine;

    do
    {
        engine = PuzzleKnightBishopCandidate();
    } while (engine.IsGameOver() || engine.GetBlackCheck() || engine.GetWhiteCheck());
    return engine;
}

Engine Puzzle::NewPuzzleRookKing()
{
    Engine engine;

    do
    {
        engine = PuzzleRookCandidate();
    } while (engine.IsGameOver() || engine.GetBlackCheck() || engine.GetWhiteCheck());
    return engine;
}

Engine Puzzle::NewPuzzlePawnKing()
{
    Engine engine;

    do
    {
        engine = PuzzleKingPawnCandidate();
    } while (engine.IsGameOver() || engine.GetBlackCheck() || engine.GetWhiteCheck());
    return engine;
}

Engine Puzzle::PuzzleKnightBishopCandidate()
{
    Engine engine = Engine("");

    //Random random = new Random(DateTime.Now.Second);
    srand(time(NULL));

    char whiteKingIndex;
    char blackKingIndex;
    char whiteKnightIndex;
    char whiteBishopIndex;

    do
    {
        whiteKingIndex = (rand()%64);
        blackKingIndex = (rand() % 64);
        whiteKnightIndex = (rand() % 64);
        whiteBishopIndex = (rand() % 64);
    } while (
        whiteKingIndex == blackKingIndex ||
        whiteKingIndex == whiteBishopIndex ||
        whiteKingIndex == whiteKnightIndex ||
        whiteKnightIndex == whiteBishopIndex ||
        blackKingIndex == whiteBishopIndex ||
        blackKingIndex == whiteKingIndex
        );

    Piece whiteKing = Piece(ChessPieceType::King, ChessPieceColor::White);
    Piece whiteBishop = Piece(ChessPieceType::Bishop, ChessPieceColor::White);
    Piece whiteKnight = Piece(ChessPieceType::Knight, ChessPieceColor::White);
    Piece blackKing = Piece(ChessPieceType::King, ChessPieceColor::Black);

    engine.SetChessPiece(whiteKing, whiteKingIndex);
    engine.SetChessPiece(blackKing, blackKingIndex);
    engine.SetChessPiece(whiteKnight, whiteKnightIndex);
    engine.SetChessPiece(whiteBishop, whiteBishopIndex);

    engine.GenerateValidMoves();
    engine.EvaluateBoardScore();

    return engine;
}

Engine Puzzle::PuzzleRookCandidate()
{
    Engine engine = Engine("");

    //Random random = new Random(DateTime.Now.Second);
    srand(time(NULL));

    char whiteKingIndex;
    char blackKingIndex;
    char whiteRookIndex;

    do
    {
        whiteKingIndex = (rand() % 64);
        blackKingIndex = (rand() % 64);
        whiteRookIndex = (rand() % 64);
    } while (
        whiteKingIndex == blackKingIndex ||
        whiteKingIndex == whiteRookIndex ||
        blackKingIndex == whiteKingIndex
        );

    Piece whiteKing = Piece(ChessPieceType::King, ChessPieceColor::White);
    Piece whiteRook = Piece(ChessPieceType::Rook, ChessPieceColor::White);
    Piece blackKing = Piece(ChessPieceType::King, ChessPieceColor::Black);

    engine.SetChessPiece(whiteKing, whiteKingIndex);
    engine.SetChessPiece(blackKing, blackKingIndex);
    engine.SetChessPiece(whiteRook, whiteRookIndex);

    engine.GenerateValidMoves();
    engine.EvaluateBoardScore();

    return engine;
}

Engine Puzzle::PuzzleKingPawnCandidate()
{
    Engine engine = Engine("");

    //Random random = new Random(DateTime.Now.Second);
    srand(time(NULL));

    char whiteKingIndex;
    char blackKingIndex;
    char whitePawnIndex;

    do
    {
        whiteKingIndex = (rand() % 64);
        blackKingIndex = (rand() % 64);
        whitePawnIndex = (rand() % 64);
    } while (
        whiteKingIndex == blackKingIndex ||
        whiteKingIndex == whitePawnIndex ||
        blackKingIndex == whiteKingIndex ||
        whitePawnIndex <= 8 || whitePawnIndex >= 56 ||
        whitePawnIndex < blackKingIndex
        );

    Piece whiteKing = Piece(ChessPieceType::King, ChessPieceColor::White);
    Piece whitePawn = Piece(ChessPieceType::Pawn, ChessPieceColor::White);
    Piece blackKing = Piece(ChessPieceType::King, ChessPieceColor::Black);

    engine.SetChessPiece(whiteKing, whiteKingIndex);
    engine.SetChessPiece(blackKing, blackKingIndex);
    engine.SetChessPiece(whitePawn, whitePawnIndex);

    engine.GenerateValidMoves();
    engine.EvaluateBoardScore();

    return engine;
}

