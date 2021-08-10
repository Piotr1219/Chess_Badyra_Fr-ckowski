#pragma once
#include <string>
#include <list>
#include <stack>
#include <algorithm>
//#include "Engine.h"
//#include "Book.h"
//#include "main.h"
#include "functions.h"
//#include "Piece.h"
#include "MoveContent.h"
#include "Square.h"


class Board
{
public:
    Square Squares[64];

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

    bool BlackAttackBoard[64];
    bool WhiteAttackBoard[64];

    //Who initated En Passant
    ChessPieceColor EnPassantColor;
    //Positions liable to En Passant
    byte EnPassantPosition;

    static ChessPieceColor WhoseMove;

    int MoveCount;

    //constructors

    //Default Constructor

    //Board(string fen) : this()
    Board(string fen);

    Board();

    bool isEmpty();


private:
    Board(Square squares[]);

    //Constructor
    Board(int score);
public:
    //Copy Constructor
    Board(const Board &board);
private:

    static bool PromotePawns(Board board, Piece piece, byte dstPosition, ChessPieceType promoteToPiece);

    static void RecordEnPassant(ChessPieceColor pcColor, ChessPieceType pcType, Board board, byte srcPosition, byte dstPosition);

    static bool SetEnpassantMove(Board board, byte srcPosition, byte dstPosition, ChessPieceColor pcColor);

    static void KingCastle(Board board, Piece piece, byte srcPosition, byte dstPosition);

    //Fast Copy
public:
    Board FastCopy();

    static MoveContent MovePiece(Board board, byte srcPosition, byte dstPosition, ChessPieceType promoteToPiece);

private:
    static string GetColumnFromByte(byte column);

public:
    string ToString();
    bool isSlash(char c);

    static string Fen(bool boardOnly, Board board);

};
