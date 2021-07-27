#include <string>
#include <list>
#include <stack>
#include <vector>
#include "Engine.h"
#include "Board.h"
#include "Book.h"
#include "main.h"
#include "functions.h"
#include "MoveContent.h"
#include "Piece.h"
#include "Evaluations.h"

using namespace std;

class FileIO
{
    void SaveCurrentGameMove(Board currentBoard, Board previousBoard, vector<OpeningMove> gameBook, MoveContent bestMove);

    static bool SaveGame(string filePath, Board chessBoard, ChessPieceColor whoseMove, stack<MoveContent> moveHistory);

    static bool LoadGame(string filePath, Board* chessBoard, ChessPieceColor whoseMove, stack<MoveContent>* moveHistory, list<OpeningMove>* currentGameBook, list<OpeningMove>* undoGameBook);

public:
    static bool LoadOpeningBook(list<OpeningMove>* openingBook);
    /*
    private static void RegisterPiece(byte boardColumn, byte boardRow, XMLBoard.XMLChessPiece piece, Board chessBoard);
    */
};

