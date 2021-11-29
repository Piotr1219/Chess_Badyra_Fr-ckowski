#pragma once
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


class Puzzle
{
public:
    static Engine NewPuzzleKnightBishopKing();

    static Engine NewPuzzleRookKing();

    static Engine NewPuzzlePawnKing();

private:
    static Engine PuzzleKnightBishopCandidate();

    static Engine PuzzleRookCandidate();

    static Engine PuzzleKingPawnCandidate();

};