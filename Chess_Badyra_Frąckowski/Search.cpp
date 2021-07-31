#include <string>
#include <list>
#include <stack>
//#include "Engine.h"
#include "Board.h"
#include "Book.h"
//#include "main.h"
//#include "functions.h"
#include "MoveContent.h"
//#include "Piece.h"
#include "Evaluations.h"
//#include "Square.h"
#include "ResultBoards.h"
#include "PieceValidMoves.h"
#include "Search.h"

using namespace std;

struct Position
{
    byte SrcPosition;
    byte DstPosition;
    int Score;
    //internal bool TopSort;
    string Move;
public:
    string ToString()
    {
        return Move;
    }
};

bool Sort(Position s2, Position s1)
{
    return (((s1.Score) - (s2.Score)) > 0);
}

static class Search
{
    static int progress;

private:
    static int piecesRemaining;


    

private:
    //static Position KillerMove[][] = Position[3,20];
    static Position KillerMove[3][20];
    static int kIndex;

    bool Sort(Board s2, Board s1)
    {
        return (((s1.Score) - (s2.Score)) > 0);
    }

    static int SideToMoveScore(int score, ChessPieceColor color)
    {
        if (color == ChessPieceColor::Black)
            return -score;

        return score;
    }


public:
    static MoveContent IterativeSearch(Board examineBoard, byte depth, int* nodesSearched, int* nodesQuiessence, string pvLine, byte* plyDepthReached, byte* rootMovesSearched, list<OpeningMove> currentGameBook)
    {
        list<Position> pvChild = list<Position>();
        int alpha = -400000000;
        const int beta = 400000000;


        MoveContent bestMove = MoveContent();

        //We are going to store our result boards here           
        ResultBoards succ = GetSortValidMoves(examineBoard);

        byte rootMovesSearched = (byte)succ.Positions.size();

        if ((short)rootMovesSearched == 1)
        {
            //I only have one move
            list<Board>::iterator it = succ.Positions.begin();
            //advance(it, 0);
            Board board1 = *it;
            return board1.LastMove;
            //return succ.Positions[0].LastMove;
        }

        //Can I make an instant mate?
        for(Board &pos : succ.Positions)
        {
            int value = -AlphaBeta(pos, (byte)1, -beta, -alpha, nodesSearched, nodesQuiessence, &pvChild, true);

            if (value >= 32767)
            {
                return pos.LastMove;
            }
        }

        int currentBoard = 0;

        alpha = -400000000;

        succ.Positions.sort(Sort);

        depth = byte((short)depth - 1);

        *plyDepthReached = ModifyDepth(depth, succ.Positions.size());

        for(Board pos : succ.Positions)
        {
            currentBoard++;

            progress = (int)((currentBoard / (float)succ.Positions.size()) * 100);

            pvChild = list<Position>();

            int value = -AlphaBeta(pos, depth, -beta, -alpha, nodesSearched, nodesQuiessence, &pvChild, false);

            if (value >= 32767)
            {
                return pos.LastMove;
            }

            if ((short)examineBoard.RepeatedMove == 2)
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
            }
        }

        plyDepthReached++;
        progress = 100;

        return bestMove;
    }

private:
    static ResultBoards GetSortValidMoves(Board examineBoard)
    {
        ResultBoards succ;
        succ.Positions = list<Board>(30);

        piecesRemaining = 0;

        for (short x = 0; x < 64; x++)
        {
            Square sqr = examineBoard.Squares[x];

            //Make sure there is a piece on the square
            if (sqr.Piece1.PieceType == ChessPieceType::None)
                continue;

            piecesRemaining++;

            //Make sure the color is the same color as the one we are moving.
            if (sqr.Piece1.PieceColor != examineBoard.WhoseMove)
                continue;

            //For each valid move for this piece
            for(byte dst : sqr.Piece1.ValidMoves)
            {
                //We make copies of the board and move so that we can move it without effecting the parent board
                Board board = examineBoard.FastCopy();

                //Make move so we can examine it
                Board::MovePiece(board, (byte)x, dst, ChessPieceType::Queen);

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
                Evaluation eva1;
                eva1.EvaluateBoardScore(board);

                //Invert Score to support Negamax
                board.Score = SideToMoveScore(board.Score, board.WhoseMove);

                succ.Positions.push_back(board);
            }
        }

        succ.Positions.sort(Sort);
        return succ;
    }

    static int AlphaBeta(Board examineBoard, byte depth, int alpha, int beta, int* nodesSearched, int* nodesQuiessence, list<Position>* pvLine, bool extended)
    {
        nodesSearched++;

        if ((short)examineBoard.HalfMoveClock >= 100 || (short)examineBoard.RepeatedMove >= 3)
            return 0;

        //End Main Search with Quiescence
        if ((short)depth == 0)
        {
            if (!extended && examineBoard.BlackCheck || examineBoard.WhiteCheck)
            {
                depth = (byte)((short)depth+1);
                extended = true;
            }
            else
            {
                //Perform a Quiessence Search
                return Quiescence(examineBoard, alpha, beta, nodesQuiessence);
            }
        }

        list<Position> positions = EvaluateMoves(examineBoard, depth);

        if (examineBoard.WhiteCheck || examineBoard.BlackCheck || positions.size() == 0)
        {
            if (SearchForMate(examineBoard.WhoseMove, examineBoard, &examineBoard.BlackMate, &examineBoard.WhiteMate, &examineBoard.StaleMate))
            {
                if (examineBoard.BlackMate)
                {
                    if (examineBoard.WhoseMove == ChessPieceColor::Black)
                        return -32767 - (short)depth;

                    return 32767 + (short)depth;
                }
                if (examineBoard.WhiteMate)
                {
                    if (examineBoard.WhoseMove == ChessPieceColor::Black)
                        return 32767 + (short)depth;

                    return -32767 - (short)depth;
                }

                //If Not Mate then StaleMate
                return 0;
            }
        }

        positions.sort(Sort);

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

            int value = -AlphaBeta(board, (byte)((short)depth - 1), -beta, -alpha, nodesSearched, nodesQuiessence, &pvChild, extended);

            if (value >= beta)
            {
                KillerMove[kIndex][(short)depth].SrcPosition = move.SrcPosition;
                KillerMove[kIndex][(short)depth].DstPosition = move.DstPosition;

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

                alpha = (int)value;
            }
        }

        return alpha;
    }

    static int Quiescence(Board examineBoard, int alpha, int beta, int* nodesSearched)
    {
        nodesSearched++;

        //Evaluate Score
        Evaluation eva1;
        eva1.EvaluateBoardScore(examineBoard);

        //Invert Score to support Negamax
        examineBoard.Score = SideToMoveScore(examineBoard.Score, examineBoard.WhoseMove);

        if (examineBoard.Score >= beta)
            return beta;

        if (examineBoard.Score > alpha)
            alpha = examineBoard.Score;


        list<Position> positions;


        if (examineBoard.WhiteCheck || examineBoard.BlackCheck)
        {
            positions = EvaluateMoves(examineBoard, (byte)0);
        }
        else
        {
            positions = EvaluateMovesQ(examineBoard);
        }

        if (positions.size() == 0)
        {
            return examineBoard.Score;
        }

        positions.sort(Sort);

        for(Position move : positions)
        {
            if (StaticExchangeEvaluation(examineBoard.Squares[(short)move.DstPosition]) >= 0)
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

    static list<Position> EvaluateMoves(Board examineBoard, byte depth)
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
            for(byte dst : piece.ValidMoves)
            {
                Position move = Position();

                move.SrcPosition = (byte)x;
                move.DstPosition = dst;

                if (move.SrcPosition == KillerMove[0][(short)depth].SrcPosition && move.DstPosition == KillerMove[0][(short)depth].DstPosition)
                {
                    //move.TopSort = true;
                    move.Score += 5000;
                    positions.push_back(move);
                    continue;
                }
                if (move.SrcPosition == KillerMove[1][(short)depth].SrcPosition && move.DstPosition == KillerMove[1][(short)depth].DstPosition)
                {
                    //move.TopSort = true;
                    move.Score += 5000;
                    positions.push_back(move);
                    continue;
                }

                Piece pieceAttacked = examineBoard.Squares[(short)move.DstPosition].Piece1;

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
                        if ((short)move.DstPosition != 62 && (short)move.DstPosition != 58)
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
                        if ((short)move.DstPosition != 6 && (short)move.DstPosition != 2)
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

    static list<Position> EvaluateMovesQ(Board examineBoard)
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
            for(byte dst : piece.ValidMoves)
            {
                if (examineBoard.Squares[(short)dst].Piece1.PieceType == ChessPieceType::None)
                {
                    continue;
                }

                Position move = Position();

                move.SrcPosition = (byte)x;
                move.DstPosition = (byte)dst;

                if (move.SrcPosition == KillerMove[2][0].SrcPosition && move.DstPosition == KillerMove[2][0].DstPosition)
                {
                    //move.TopSort = true;
                    move.Score += 5000;
                    positions.push_back(move);
                    continue;
                }

                Piece pieceAttacked = examineBoard.Squares[(short)move.DstPosition].Piece1;

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
public:
    static bool SearchForMate(ChessPieceColor movingSide, Board examineBoard, bool* blackMate, bool* whiteMate, bool* staleMate)
    {
        bool foundNonCheckBlack = false;
        bool foundNonCheckWhite = false;

        for (short x = 0; x < 64; x++)
        {
            Square sqr = examineBoard.Squares[x];

            //Make sure there is a piece on the square
            if (sqr.Piece1.PieceType != ChessPieceType::None)
                continue;

            //Make sure the color is the same color as the one we are moving.
            if (sqr.Piece1.PieceColor != movingSide)
                continue;

            //For each valid move for this piece
            for(byte dst : sqr.Piece1.ValidMoves)
            {

                //We make copies of the board and move so that we can move it without effecting the parent board
                Board board = examineBoard.FastCopy();

                //Make move so we can examine it
                Board::MovePiece(board, (byte)x, dst, ChessPieceType::Queen);

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
                return true;
            }
        }

        return false;

    }
private:
    static byte ModifyDepth(byte depth, int possibleMoves)
    {
        if (possibleMoves <= 20 || piecesRemaining < 14)
        {
            if (possibleMoves <= 10 || piecesRemaining < 6)
            {
                depth = (byte)((short)depth+1);
            }

            depth = (byte)((short)depth + 1);
        }

        return depth;
    }

    static int StaticExchangeEvaluation(Square examineSquare)
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

};

