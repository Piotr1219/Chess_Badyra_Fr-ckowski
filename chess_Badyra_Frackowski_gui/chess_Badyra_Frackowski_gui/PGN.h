#pragma once
#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
//#include "Piece.h"
//#include "Evaluations.h"

using namespace std;

class PGN
{
public:
    enum Result
    {
        White,
        Black,
        Tie,
        Ongoing
    };


    static string GeneratePGN(list<MoveContent> moveHistory, int round, string whitePlayer, string blackPlayer, Result result);


};