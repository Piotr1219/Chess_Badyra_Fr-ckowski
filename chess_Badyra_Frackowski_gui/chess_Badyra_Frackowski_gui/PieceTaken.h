#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"

using namespace std;

class PiecesTaken
{
public:
    int WhiteQueen;
    int WhiteRook;
    int WhiteBishop;
    int WhiteKnight;
    int WhitePawn;
    int BlackQueen;
    int BlackRook;
    int BlackBishop;
    int BlackKnight;
    int BlackPawn;

    PiecesTaken();
};
