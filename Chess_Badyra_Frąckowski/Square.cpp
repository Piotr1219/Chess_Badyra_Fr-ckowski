#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
#include "Piece.h"
//#include "Evaluations.h"
//#include "PGN.h"
//#include "PieceMoves.h"
//#include "PieceSquareTable.h"

struct Square
{
    Piece Piece1;

    Square(Piece piece)
    {
        Piece1 = Piece(piece);
    }
    Square() {
        ;
    }

};
