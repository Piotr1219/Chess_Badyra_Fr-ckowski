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

    bool InsufficientMaterial = false;

    int Score;

    unsigned long long int ZobristHash;

    //Game Over Flags
    bool BlackCheck;
    bool BlackMate;
    bool WhiteCheck;
    bool WhiteMate;
    bool StaleMate = false;

    char HalfMoveClock = 0;
    char RepeatedMove = 0;

    bool BlackCastled;
    bool WhiteCastled;

    bool BlackCanCastle;
    bool WhiteCanCastle;

    bool EndGamePhase;

    MoveContent LastMove;

    char WhiteKingPosition;
    char BlackKingPosition;

    bool BlackAttackBoard[64];
    bool WhiteAttackBoard[64];

    //Who initated En Passant
    ChessPieceColor EnPassantColor;
    //Positions liable to En Passant
    char EnPassantPosition = 0;

    //inline static 
    ChessPieceColor WhoseMove;

    int MoveCount = 1;

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

    static bool PromotePawns(Board board, Piece piece, char dstPosition, ChessPieceType promoteToPiece);

    static void RecordEnPassant(ChessPieceColor pcColor, ChessPieceType pcType, Board board, char srcPosition, char dstPosition);

    static bool SetEnpassantMove(Board board, char srcPosition, char dstPosition, ChessPieceColor pcColor);

    static void KingCastle(Board board, Piece piece, char srcPosition, char dstPosition);
    static void KingCastle2(Board board, Piece piece, char srcPosition, char dstPosition, double& time1);

    //Fast Copy
public:
    Board FastCopy();

    static MoveContent MovePiece(Board& board, char srcPosition, char dstPosition, ChessPieceType promoteToPiece);
    static MoveContent MovePiece2(Board& board, char srcPosition, char dstPosition, ChessPieceType promoteToPiece, double& time1);

private:
    static string GetColumnFromByte(char column);

public:
    string ToString();
    bool isSlash(char c);

    static string Fen(bool boardOnly, Board& board);

};
