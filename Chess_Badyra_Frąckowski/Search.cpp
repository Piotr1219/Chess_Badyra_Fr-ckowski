#include "Search.h"
#include <string>
#include <list>
#include <stack>
#include <iostream>
//#include "Board.h"
//#include "Book.h"
//#include "MoveContent.h"
//#include "Evaluations.h"
//#include "ResultBoards.h"
//#include "PieceValidMoves.h"

using namespace std;


string Position::ToString()
{
    return Move;
}


//bool Search::sortComparator::operator() (Board & s2, Board & s1)
//{
//    return (((s1.Score) - (s2.Score)) > 0);
//}
struct sortComparator {
    bool operator () (Board& s2, Board& s1)
    {
        return (((s1.Score) - (s2.Score)) > 0);
    }
};

struct PositionComparator {
    bool operator () (const Position& s2, const Position& s1)
    {
        return s1.Score < s2.Score;
    }
};

int Search::SideToMoveScore(int score, ChessPieceColor color)
{
    if (color == ChessPieceColor::Black)
        return -score;

    return score;
}


MoveContent Search::IterativeSearch(Board& examineBoard, char depth, int* nodesSearched, int* nodesQuiessence, string pvLine, char* plyDepthReached, char* rootMovesSearched, list<OpeningMove> currentGameBook)
{
    list<Position> pvChild = list<Position>();
    int alpha = -400000000;
    const int beta = 400000000;


    MoveContent bestMove = MoveContent();

    //We are going to store our result boards here           
    ResultBoards succ = GetSortValidMoves(examineBoard);

    *rootMovesSearched = succ.Positions.size();

    if (*rootMovesSearched == 1)
    {
        //I only have one move
        list<Board>::iterator it = succ.Positions.begin();
        //advance(it, 0);
        Board board1 = *it;
        return board1.LastMove;
        //return succ.Positions[0].LastMove;
    }

    cout << "ilosc mozliwych pozycji " << succ.Positions.size() << endl;

    //Can I make an instant mate?
    for (list<Board>::iterator it = succ.Positions.begin(); it != succ.Positions.end(); ++it)
    //for(Board &pos : succ.Positions)
    {
        Board pos = *it;
        //for (int i = 0; i < 64; i++) {
        //    if (i % 8 == 0) {
        //        cout << endl;
        //    }
        //    cout << pos.Squares[i].Piece1.PieceType << " ";
        //}

        int value = -AlphaBeta(pos, 1, -beta, -alpha, *nodesSearched, nodesQuiessence, &pvChild, true);

        if (value >= 32767)
        {
            //cout << "iterative search wartosc > 32767 1" << endl;
            return pos.LastMove;
        }
    }

    int currentBoard = 0;

    alpha = -400000000;

    succ.Positions.sort(sortComparator());

    depth = depth - 1;

    cout << "Depth: " << int(depth) << endl;

    *plyDepthReached = ModifyDepth(depth, succ.Positions.size());

    //for(Board pos : succ.Positions)
    for (list<Board>::iterator it = succ.Positions.begin(); it != succ.Positions.end(); ++it)
    {
        Board pos = *it;
        //cout << "przejrzane succ" << endl;
        currentBoard++;

        progress = ((currentBoard / (float)succ.Positions.size()) * 100);

        pvChild = list<Position>();

        //cout << "search glebsze przegladanie" << endl;
        int value = -AlphaBeta(pos, depth, -beta, -alpha, *nodesSearched, nodesQuiessence, &pvChild, false);
        //cout << "petla w pozycjach  " << value << endl;

        if (value >= 32767)
        {
            //cout << "iterative search wartosc > 32767 2" << endl;
            return pos.LastMove;
        }

        if (examineBoard.RepeatedMove == 2)
        {
            string fen = Board::Fen(true, pos);

            for(OpeningMove &move : currentGameBook)
            {
                if (move.EndingFEN == fen)
                {
                    value = 0;
                    break;
                }
            }
        }

        pos.Score = value;

        //If value is greater then alpha this is the best board
        if (value > alpha || alpha == -400000000)
        {
            pvLine = pos.LastMove.ToString();

            for(Position &pvPos : pvChild)
            {
                pvLine += (string)" ";
                pvLine += pvPos.ToString();
            }

            alpha = value;
            bestMove = pos.LastMove;
            //cout << " " << endl;
            //cout << "src pos w search " << pos.LastMove.MovingPiecePrimary.SrcPosition << endl;
        }
    }

    plyDepthReached++;
    progress = 100;


    cout << "Returning best move \n";
    return bestMove;
}

ResultBoards Search::GetSortValidMoves(Board& examineBoard)
{
    ResultBoards succ;
    //succ.Positions = list<Board>(30);

    piecesRemaining = 0;

    //cout << "    poczatek valid moves" << endl;

    for (short x = 0; x < 64; x++)
    {
        Square& sqr = examineBoard.Squares[x];

        //Make sure there is a piece on the square
        if (sqr.Piece1.PieceType == ChessPieceType::None)
        {
            continue;
        }

        piecesRemaining++;

        //Make sure the color is the same color as the one we are moving.
        if (sqr.Piece1.PieceColor != examineBoard.WhoseMove)
        {
            continue;
        }

        //For each valid move for this piece
        //for(char dst : sqr.Piece1.ValidMoves)
        for (list<char>::iterator it = sqr.Piece1.ValidMoves.begin(); it != sqr.Piece1.ValidMoves.end(); ++it)
        {
            char dst = *it;
            //cout << "kazda pozycja w valid moves" << endl;
            //We make copies of the board and move so that we can move it without effecting the parent board
            //Board board = examineBoard.FastCopy();
            Board board = examineBoard;

            //Make move so we can examine it
            Board::MovePiece(board, x, dst, ChessPieceType::Queen);

            //We Generate Valid Moves for Board
            PieceValidMoves::GenerateValidMoves(board);

            //Invalid Move
            if (board.WhiteCheck && examineBoard.WhoseMove == ChessPieceColor::White)
            {
                continue;
            }

            //Invalid Move
            if (board.BlackCheck && examineBoard.WhoseMove == ChessPieceColor::Black)
            {
                continue;
            }

            //We calculate the board score
            //Evaluation eva1;
            EvaluateBoardScore2(board);

            //Invert Score to support Negamax
            board.Score = SideToMoveScore(board.Score, board.WhoseMove);

            succ.Positions.push_back(board);

            /*cout << "wypisanie jeszcze w valid moves" << endl;
            for (int i = 0; i < 64; i++) {
                if (i % 8 == 0) {
                    cout << endl;
                }
                cout << board.Squares[i].Piece1.PieceType << " ";
            }
            cout << "koniec wypiania w valid moves" << endl;*/
        }
    }

    succ.Positions.sort(sortComparator());
    return succ;
}

int Search::AlphaBeta(Board& examineBoard, char depth, int alpha, int beta, int& nodesSearched, int* nodesQuiessence, list<Position>* pvLine, bool extended)

{
    //printf("alphabeta\n");
    nodesSearched++;

    if (examineBoard.HalfMoveClock >= 100 || examineBoard.RepeatedMove >= 3)
        return 0;

    //End Main Search with Quiescence
    if (depth == 0)
    {
        if (!extended && examineBoard.BlackCheck || examineBoard.WhiteCheck)
        {
            depth++;
            extended = true;
        }
        else
        {
            //Perform a Quiessence Search
            return Quiescence(examineBoard, alpha, beta, *nodesQuiessence);
        }
    }

    list<Position> positions = EvaluateMoves(examineBoard, depth);

    if (examineBoard.WhiteCheck || examineBoard.BlackCheck || positions.size() == 0)
    {
        if (SearchForMate(examineBoard.WhoseMove, examineBoard, &examineBoard.BlackMate, &examineBoard.WhiteMate, &examineBoard.StaleMate))
        {
            /*cout << "mate found in alpha beta search in board: " << examineBoard.BlackMate << " " << examineBoard.WhiteMate << " " << examineBoard.StaleMate << endl;
            for (int i = 0; i < 64; i++) {
                if (i % 8 == 0) {
                    cout << endl;
                }
                cout << examineBoard.Squares[i].Piece1.PieceType << " ";
            }*/
            if (examineBoard.BlackMate)
            {
                if (examineBoard.WhoseMove == ChessPieceColor::Black)
                    return -32767 - depth;

                return 32767 + depth;
            }
            if (examineBoard.WhiteMate)
            {
                if (examineBoard.WhoseMove == ChessPieceColor::Black)
                    return 32767 + depth;

                return -32767 - depth;
            }

            //If Not Mate then StaleMate
            return 0;
        }
    }

    positions.sort(PositionComparator());

    for(Position move : positions)
    {
        list<Position> pvChild = list<Position>();

        //Make a copy
        Board board = examineBoard.FastCopy();

        //Move Piece
        Board::MovePiece(board, move.SrcPosition, move.DstPosition, ChessPieceType::Queen);

        //We Generate Valid Moves for Board
        PieceValidMoves::GenerateValidMoves(board);

        if (board.BlackCheck)
        {
            if (examineBoard.WhoseMove == ChessPieceColor::Black)
            {
                //Invalid Move
                continue;
            }
        }

        if (board.WhiteCheck)
        {
            if (examineBoard.WhoseMove == ChessPieceColor::White)
            {
                //Invalid Move
                continue;
            }
        }

        int value = -AlphaBeta(board, depth - 1, -beta, -alpha, nodesSearched, nodesQuiessence, &pvChild, extended);

        if (value >= beta)
        {
            KillerMove[kIndex][depth].SrcPosition = move.SrcPosition;
            KillerMove[kIndex][depth].DstPosition = move.DstPosition;

            kIndex = ((kIndex + 1) % 2);


            return beta;
        }
        if (value > alpha)
        {
            Position pvPos = Position();

            pvPos.SrcPosition = board.LastMove.MovingPiecePrimary.SrcPosition;
            pvPos.DstPosition = board.LastMove.MovingPiecePrimary.DstPosition;
            pvPos.Move = board.LastMove.ToString();

            pvChild.push_front(pvPos);

            *pvLine = pvChild;

            alpha = value;
        }
    }

    return alpha;
}

int Search::Quiescence(Board& examineBoard, int alpha, int beta, int& nodesSearched)
{
    nodesSearched++;

    //Evaluate Score
    //Evaluation eva1;
    EvaluateBoardScore2(examineBoard);

    //Invert Score to support Negamax
    examineBoard.Score = SideToMoveScore(examineBoard.Score, examineBoard.WhoseMove);

    if (examineBoard.Score >= beta)
        return beta;

    if (examineBoard.Score > alpha)
        alpha = examineBoard.Score;


    list<Position> positions;


    if (examineBoard.WhiteCheck || examineBoard.BlackCheck)
    {
        positions = EvaluateMoves(examineBoard, 0);
    }
    else
    {
        positions = EvaluateMovesQ(examineBoard);
    }

    if (positions.size() == 0)
    {
        return examineBoard.Score;
    }

    positions.sort(PositionComparator());

    for(Position move : positions)
    {
        if (StaticExchangeEvaluation(examineBoard.Squares[move.DstPosition]) >= 0)
        {
            continue;
        }

        //Make a copy
        Board board = examineBoard.FastCopy();

        //Move Piece
        Board::MovePiece(board, move.SrcPosition, move.DstPosition, ChessPieceType::Queen);

        //We Generate Valid Moves for Board
        PieceValidMoves::GenerateValidMoves(board);

        if (board.BlackCheck)
        {
            if (examineBoard.WhoseMove == ChessPieceColor::Black)
            {
                //Invalid Move
                continue;
            }
        }

        if (board.WhiteCheck)
        {
            if (examineBoard.WhoseMove == ChessPieceColor::White)
            {
                //Invalid Move
                continue;
            }
        }

        int value = -Quiescence(board, -beta, -alpha, nodesSearched);

        if (value >= beta)
        {
            KillerMove[2][0].SrcPosition = move.SrcPosition;
            KillerMove[2][0].DstPosition = move.DstPosition;

            return beta;
        }
        if (value > alpha)
        {
            alpha = value;
        }
    }

    return alpha;
}

list<Position> Search::EvaluateMoves(Board& examineBoard, char depth)
{

    //We are going to store our result boards here           
    list<Position> positions = list<Position>();

    //bool foundPV = false;


    for (short x = 0; x < 64; x++)
    {
        Piece piece = examineBoard.Squares[x].Piece1;

        //Make sure there is a piece on the square
        if (piece.PieceType == ChessPieceType::None)
            continue;

        //Make sure the color is the same color as the one we are moving.
        if (piece.PieceColor != examineBoard.WhoseMove)
            continue;

        //For each valid move for this piece
        for(char dst : piece.ValidMoves)
        {
            Position move = Position();

            move.SrcPosition = x;
            move.DstPosition = dst;

            if (move.SrcPosition == KillerMove[0][depth].SrcPosition && move.DstPosition == KillerMove[0][depth].DstPosition)
            {
                //move.TopSort = true;
                move.Score += 5000;
                positions.push_back(move);
                continue;
            }
            if (move.SrcPosition == KillerMove[1][depth].SrcPosition && move.DstPosition == KillerMove[1][depth].DstPosition)
            {
                //move.TopSort = true;
                move.Score += 5000;
                positions.push_back(move);
                continue;
            }

            Piece pieceAttacked = examineBoard.Squares[move.DstPosition].Piece1;

            //If the move is a capture add it's value to the score
            if (pieceAttacked.PieceType != ChessPieceType::None)
            {
                move.Score += pieceAttacked.PieceValue;

                if (piece.PieceValue < pieceAttacked.PieceValue)
                {
                    move.Score += pieceAttacked.PieceValue - piece.PieceValue;
                }
            }

            if (!piece.Moved)
            {
                move.Score += 10;
            }

            move.Score += piece.PieceActionValue;

            //Add Score for Castling
            if (!examineBoard.WhiteCastled && examineBoard.WhoseMove == ChessPieceColor::White)
            {

                if (piece.PieceType == ChessPieceType::King)
                {
                    if (move.DstPosition != 62 && move.DstPosition != 58)
                    {
                        move.Score -= 40;
                    }
                    else
                    {
                        move.Score += 40;
                    }
                }
                if (piece.PieceType == ChessPieceType::Rook)
                {
                    move.Score -= 40;
                }
            }

            if (!examineBoard.BlackCastled && examineBoard.WhoseMove == ChessPieceColor::Black)
            {
                if (piece.PieceType == ChessPieceType::King)
                {
                    if (move.DstPosition != 6 && move.DstPosition != 2)
                    {
                        move.Score -= 40;
                    }
                    else
                    {
                        move.Score += 40;
                    }
                }
                if (piece.PieceType == ChessPieceType::Rook)
                {
                    move.Score -= 40;
                }
            }

            positions.push_back(move);
        }
    }

    return positions;
}

list<Position> Search::EvaluateMovesQ(Board& examineBoard)
{
    //We are going to store our result boards here           
    list<Position> positions = list<Position>();

    for (short x = 0; x < 64; x++)
    {
        Piece piece = examineBoard.Squares[x].Piece1;

        //Make sure there is a piece on the square
        if (piece.PieceType == ChessPieceType::None)
            continue;

        //Make sure the color is the same color as the one we are moving.
        if (piece.PieceColor != examineBoard.WhoseMove)
            continue;

        //For each valid move for this piece
        for(char dst : piece.ValidMoves)
        {
            if (examineBoard.Squares[dst].Piece1.PieceType == ChessPieceType::None)
            {
                continue;
            }

            Position move = Position();

            move.SrcPosition = x;
            move.DstPosition = dst;

            if (move.SrcPosition == KillerMove[2][0].SrcPosition && move.DstPosition == KillerMove[2][0].DstPosition)
            {
                //move.TopSort = true;
                move.Score += 5000;
                positions.push_back(move);
                continue;
            }

            Piece pieceAttacked = examineBoard.Squares[move.DstPosition].Piece1;

            move.Score += pieceAttacked.PieceValue;

            if (piece.PieceValue < pieceAttacked.PieceValue)
            {
                move.Score += pieceAttacked.PieceValue - piece.PieceValue;
            }

            move.Score += piece.PieceActionValue;


            positions.push_back(move);
        }
    }

    return positions;
}

bool Search::SearchForMate(ChessPieceColor movingSide, Board& examineBoard, bool* blackMate, bool* whiteMate, bool* staleMate)
{
    bool foundNonCheckBlack = false;
    bool foundNonCheckWhite = false;

    //cout << "rozmiar valid moves " << examineBoard.Squares[10].Piece1.ValidMoves.size() << endl;
    //for (auto const& i : examineBoard.Squares[10].Piece1.ValidMoves) {
    //    cout << "white pawn valid moves w searchformate " << i << std::endl;
    //}

    for (short x = 0; x < 64; x++)
    {
        Square sqr = examineBoard.Squares[x];

        //Make sure there is a piece on the square
        //if (sqr.Piece1.PieceType == ChessPieceType::None)
        if (examineBoard.Squares[x].Piece1.PieceType == ChessPieceType::None)
        {
            continue;
        }

        //Make sure the color is the same color as the one we are moving.
        //if (sqr.Piece1.PieceColor != movingSide)
        if (examineBoard.Squares[x].Piece1.PieceColor != movingSide)
        {
            continue;
        }
        //cout << "przed petla valid moves " <<  sqr.Piece1.ValidMoves.size() << " numer " << x << endl;
        //cout << "przed petla valid moves bezposrednio " << examineBoard.Squares[x].Piece1.ValidMoves.size() << " numer " << x << endl;
        
        //For each valid move for this piece
        //for(char dst : sqr.Piece1.ValidMoves)
        for (char dst : examineBoard.Squares[x].Piece1.ValidMoves)
        {

            //We make copies of the board and move so that we can move it without effecting the parent board
            //Board board = examineBoard.FastCopy();
            Board board = examineBoard;

            //Make move so we can examine it
            //cout << "test move from " << x << " to " << (int)dst << endl;
            Board::MovePiece(board, x, dst, ChessPieceType::Queen);

            //We Generate Valid Moves for Board
            PieceValidMoves::GenerateValidMoves(board);

            if (board.BlackCheck == false)
            {
                foundNonCheckBlack = true;
            }
            else if (movingSide == ChessPieceColor::Black)
            {
                continue;
            }

            if (board.WhiteCheck == false)
            {
                foundNonCheckWhite = true;
            }
            else if (movingSide == ChessPieceColor::White)
            {
                continue;
            }
        }
    }

    if (foundNonCheckBlack == false)
    {
        if (examineBoard.BlackCheck)
        {
            *blackMate = true;
            return true;
        }
        if (!examineBoard.WhiteMate && movingSide != ChessPieceColor::White)
        {
            *staleMate = true;
            cout << "search for mate zwroci true white" << endl;
            return true;
        }
    }

    if (foundNonCheckWhite == false)
    {
        if (examineBoard.WhiteCheck)
        {
            *whiteMate = true;
            return true;
        }
        if (!examineBoard.BlackMate && movingSide != ChessPieceColor::Black)
        {
            *staleMate = true;
            cout << "search for mate zwroci true black" << endl;
            return true;
        }
    }
    return false;

}
char Search::ModifyDepth(char depth, int possibleMoves)
{
    if (possibleMoves <= 20 || piecesRemaining < 14)
    {
        if (possibleMoves <= 10 || piecesRemaining < 6)
        {
            depth = depth+1;
        }

        depth = depth + 1;
    }

    return depth;
}

int Search::StaticExchangeEvaluation(Square examineSquare)
{
    if (examineSquare.Piece1.PieceType != ChessPieceType::None)
    {
        return 0;
    }
    if (examineSquare.Piece1.AttackedValue == 0)
    {
        return 0;
    }

    return examineSquare.Piece1.PieceActionValue - examineSquare.Piece1.AttackedValue + examineSquare.Piece1.DefendedValue;
}


