#pragma once
#include <string>
#include <list>
#include <stack>
#include <vector>
//#include "Engine.h"
//#include "Board.h"
//#include "main.h"
//#include "functions.h"
#include "MoveContent.h"


using namespace std;

class OpeningMove
{
public:
    string EndingFEN;
    string StartingFEN;
    list<MoveContent> Moves;

    OpeningMove();
};

class Book
{
public:
    static list<OpeningMove> LoadOpeningBook();
private:
    list<OpeningMove> PopulateOpeningBook();
public:
    static int ValidateOpeningBook(list<OpeningMove> openingBook);

    bool IsValidMove(byte srcPos, byte dstPos, string fen);
};

