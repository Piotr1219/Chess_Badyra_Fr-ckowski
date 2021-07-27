#include <string>
#include <list>
#include <stack>
#include "Engine.h"
#include "main.h"
#include "functions.h"
#include "MoveContent.h"


using namespace std;

class Book
{
    list<OpeningMove> LoadOpeningBook();

    list<OpeningMove> PopulateOpeningBook();
public:
    static int ValidateOpeningBook(list<OpeningMove> openingBook);

    bool IsValidMove(byte srcPos, byte dstPos, string fen);
};

class OpeningMove
{
public:
    string EndingFEN;
    string StartingFEN;
    list<MoveContent> Moves;

    OpeningMove();
};
