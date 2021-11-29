#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
//#include "Board.h"
//#include "Book.h"
//#include "main.h"
//#include "functions.h"
//#include "MoveContent.h"
#include "PGN.h"
//#include "Piece.h"
//#include "Evaluations.h"

using namespace std;


string PGN::GeneratePGN(list<MoveContent> moveHistory, int round, string whitePlayer, string blackPlayer, Result result)
{
    int count = 0;

    string pgn = "";

    /*
        [Event "F/S Return Match"]
        [Site "Belgrade, Serbia Yugoslavia|JUG"]
        [Date "1992.11.04"]
        [Round "29"]
        [White "Fischer, Robert J."]
        [Black "Spassky, Boris V."]
        [Result "1/2-1/2"]
    */

    string pgnHeader = "";

    //pgnHeader += "[Date \"" + DateTime.Now.Year + "." + DateTime.Now.Month + "." + DateTime.Now.Day + "\"]\r\n";
    pgnHeader += "[White \"" + whitePlayer + "\"]\r\n";
    pgnHeader += "[Black \"" + blackPlayer + "\"]\r\n";

    if (result == Result::Ongoing)
    {
        pgnHeader += (string)"[Result \"" + "*" + "\"]\r\n";
    }
    else if (result == Result::White)
    {
        pgnHeader += (string)"[Result \"" + "1-0" + "\"]\r\n";
    }
    else if (result == Result::Black)
    {
        pgnHeader += (string)"[Result \"" + "0-1" + "\"]\r\n";
    }
    else if (result == Result::Tie)
    {
        pgnHeader += (string)"[Result \"" + "1/2-1/2" + "\"]\r\n";
    }

    for(MoveContent move : moveHistory)
    {
        string tmp = "";

        if (move.MovingPiecePrimary.PieceColor == ChessPieceColor::White)
        {
            tmp += to_string(((moveHistory.size() / 2) - count + 1)) + ". ";
        }

        tmp += move.ToString();
        tmp += " ";

        tmp += pgn;
        pgn = tmp;

        if (move.MovingPiecePrimary.PieceColor == ChessPieceColor::Black)
        {
            count++;
        }
    }

    if (result == Result::White)
    {
        pgn += " 1-0";
    }
    else if (result == Result::Black)
    {
        pgn += " 0-1";
    }
    else if (result == Result::Tie)
    {
        pgn += " 1/2-1/2";
    }

    return pgnHeader + pgn;
}



