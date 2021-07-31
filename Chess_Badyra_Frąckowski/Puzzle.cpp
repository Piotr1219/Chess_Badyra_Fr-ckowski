#include <string>
#include <list>
#include <stack>
#include <ctime>
#include "Engine.h"
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


class Puzzle
{
public:
    static Engine NewPuzzleKnightBishopKing()
    {
        Engine engine;

        do
        {
            engine = PuzzleKnightBishopCandidate();
        } while (engine.IsGameOver() || engine.GetBlackCheck() || engine.GetWhiteCheck());
        return engine;
    }

    static Engine NewPuzzleRookKing()
    {
        Engine engine;

        do
        {
            engine = PuzzleRookCandidate();
        } while (engine.IsGameOver() || engine.GetBlackCheck() || engine.GetWhiteCheck());
        return engine;
    }

    static Engine NewPuzzlePawnKing()
    {
        Engine engine;

        do
        {
            engine = PuzzleKingPawnCandidate();
        } while (engine.IsGameOver() || engine.GetBlackCheck() || engine.GetWhiteCheck());
        return engine;
    }

private:
    static Engine PuzzleKnightBishopCandidate()
    {
        Engine engine = Engine("");

        //Random random = new Random(DateTime.Now.Second);
        srand(time(NULL));

        byte whiteKingIndex;
        byte blackKingIndex;
        byte whiteKnightIndex;
        byte whiteBishopIndex;

        do
        {
            whiteKingIndex = (byte)(rand()%64);
            blackKingIndex = (byte)(rand() % 64);
            whiteKnightIndex = (byte)(rand() % 64);
            whiteBishopIndex = (byte)(rand() % 64);
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

    static Engine PuzzleRookCandidate()
    {
        Engine engine = Engine("");

        //Random random = new Random(DateTime.Now.Second);
        srand(time(NULL));

        byte whiteKingIndex;
        byte blackKingIndex;
        byte whiteRookIndex;

        do
        {
            whiteKingIndex = (byte)(rand() % 64);
            blackKingIndex = (byte)(rand() % 64);
            whiteRookIndex = (byte)(rand() % 64);
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

    static Engine PuzzleKingPawnCandidate()
    {
        Engine engine = Engine("");

        //Random random = new Random(DateTime.Now.Second);
        srand(time(NULL));

        byte whiteKingIndex;
        byte blackKingIndex;
        byte whitePawnIndex;

        do
        {
            whiteKingIndex = (byte)(rand() % 64);
            blackKingIndex = (byte)(rand() % 64);
            whitePawnIndex = (byte)(rand() % 64);
        } while (
            whiteKingIndex == blackKingIndex ||
            whiteKingIndex == whitePawnIndex ||
            blackKingIndex == whiteKingIndex ||
            (short)whitePawnIndex <= 8 || (short)whitePawnIndex >= 56 ||
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

};
