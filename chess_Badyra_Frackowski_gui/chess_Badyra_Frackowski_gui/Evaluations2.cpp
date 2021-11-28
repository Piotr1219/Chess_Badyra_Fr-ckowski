#include <string>
#include <list>
#include <stack>
#include <iostream>
//#include "Board.h"
#include "Evaluations2.h"
//#include "Square.h"

using namespace std;

int EvaluatePieceScore2(Square square, char position, bool endGamePhase,
    char& knightCount, char& bishopCount, bool& insufficientMaterial, short(&blackPawnCount)[8], short(&whitePawnCount)[8])
{
    int score = 0;

    char index = position;

    if (square.Piece1.PieceColor == ChessPieceColor::Black)
    {
        index = (63 - position);
    }

    //Calculate Piece Values
    score += square.Piece1.PieceValue;
    score += square.Piece1.DefendedValue;
    score -= square.Piece1.AttackedValue;

    //Double Penalty for Hanging Pieces
    if (square.Piece1.DefendedValue < square.Piece1.AttackedValue)
    {
        score -= ((square.Piece1.AttackedValue - square.Piece1.DefendedValue) * 10);
    }

    //Add Points for Mobility
    if (!square.Piece1.ValidMoves.empty())
    {
        score += square.Piece1.ValidMoves.size();
    }

    if (square.Piece1.PieceType == ChessPieceType::Pawn)
    {
        insufficientMaterial = false;

        if (position % 8 == 0 || position % 8 == 7)
        {
            //Rook Pawns are worth 15% less because they can only attack one way
            score -= 15;
        }

        //Calculate Position Values
        score += PawnTable[index];

        if (square.Piece1.PieceColor == ChessPieceColor::White)
        {
            if (whitePawnCount[position % 8] > 0)
            {
                //Doubled Pawn
                score -= 15;
            }

            if (position >= 8 && position <= 15)
            {
                if (square.Piece1.AttackedValue == 0)
                {
                    whitePawnCount[position % 8] += 50;

                    if (square.Piece1.DefendedValue != 0)
                        whitePawnCount[position % 8] += 50;
                }
            }
            else if (position >= 16 && position <= 23)
            {
                if (square.Piece1.AttackedValue == 0)
                {
                    whitePawnCount[position % 8] += 25;


                    if (square.Piece1.DefendedValue != 0)
                        whitePawnCount[position % 8] += 25;
                }
            }

            whitePawnCount[position % 8] += 10;
        }
        else
        {
            if (blackPawnCount[position % 8] > 0)
            {
                //Doubled Pawn
                score -= 15;
            }

            if (position >= 48 && position <= 55)
            {
                if (square.Piece1.AttackedValue == 0)
                {
                    blackPawnCount[position % 8] += 200;

                    if (square.Piece1.DefendedValue != 0)
                        blackPawnCount[position % 8] += 50;
                }
            }
            //Pawns in 6th Row that are not attacked are worth more points.
            else if (position >= 40 && position <= 47)
            {
                if (square.Piece1.AttackedValue == 0)
                {
                    blackPawnCount[position % 8] += 100;

                    if (square.Piece1.DefendedValue != 0)
                        blackPawnCount[position % 8] += 25;
                }
            }

            blackPawnCount[position % 8] += 10;

        }
    }
    else if (square.Piece1.PieceType == ChessPieceType::Knight)
    {
        //*knightCount = (knightCount);

        score += KnightTable[index];

        //In the end game remove a few points for Knights since they are worth less
        if (endGamePhase)
        {
            score -= 10;
        }

    }
    else if (square.Piece1.PieceType == ChessPieceType::Bishop)
    {
        bishopCount = (bishopCount + 1);

        if (bishopCount >= 2)
        {
            //2 Bishops receive a bonus
            score += 10;
        }

        //In the end game Bishops are worth more
        if (endGamePhase)
        {
            score += 10;
        }

        score += BishopTable[index];
    }
    else if (square.Piece1.PieceType == ChessPieceType::Rook)
    {
        insufficientMaterial = false;
    }
    else if (square.Piece1.PieceType == ChessPieceType::Queen)
    {
        insufficientMaterial = false;

        if (square.Piece1.Moved && !endGamePhase)
        {
            score -= 10;
        }
    }
    else if (square.Piece1.PieceType == ChessPieceType::King)
    {
        if (!square.Piece1.ValidMoves.empty())
        {
            if (square.Piece1.ValidMoves.size() < 2)
            {
                score -= 5;
            }
        }

        if (endGamePhase)
        {
            score += KingTableEndGame[index];
        }
        else
        {
            score += KingTable[index];
        }

    }

    return score;
}

void EvaluateBoardScore2(Board& board)
{
    //printf("bs");
    //Black Score - 
    //White Score +
    board.Score = 0;

    bool insufficientMaterial = true;

    if (board.StaleMate)
    {
        return;
    }
    if (board.HalfMoveClock >= 100)
    {
        return;
    }
    if (board.RepeatedMove >= 3)
    {
        return;
    }
    if (board.BlackMate)
    {
        board.Score = 32767;
        return;
    }
    if (board.WhiteMate)
    {
        board.Score = -32767;
        return;
    }
    if (board.BlackCheck)
    {
        board.Score += 70;
        if (board.EndGamePhase)
            board.Score += 10;
    }
    else if (board.WhiteCheck)
    {
        board.Score -= 70;
        if (board.EndGamePhase)
            board.Score -= 10;
    }
    if (board.BlackCastled)
    {
        board.Score -= 50;
    }
    if (board.WhiteCastled)
    {
        board.Score += 50;
    }
    //Add a small bonus for tempo (turn)
    if (board.WhoseMove == ChessPieceColor::White)
    {
        board.Score += 10;
    }
    else
    {
        board.Score -= 10;
    }

    char blackBishopCount = 0;
    char whiteBishopCount = 0;

    char blackKnightCount = 0;
    char whiteKnightCount = 0;


    char knightCount = 0;

    //fill_n(blackPawnCount, 8, 0);
    //blackPawnCount = new short[8];
    //whitePawnCount = new short[8];
    short blackPawnCount[8];
    short whitePawnCount[8];
    for (int i = 0; i < 8; i++) {
        blackPawnCount[i] = 0;
        whitePawnCount[i] = 0;
    }

    for (int x = 0; x < 64; x++)
    {
        Square square = board.Squares[x];

        if (square.Piece1.PieceType == ChessPieceType::None)
        {
            continue;
        }


        if (square.Piece1.PieceColor == ChessPieceColor::White)
        {
            board.Score += EvaluatePieceScore2(square, x, board.EndGamePhase,
                whiteKnightCount, whiteBishopCount, insufficientMaterial, blackPawnCount, whitePawnCount);

            if (square.Piece1.PieceType == ChessPieceType::King)
            {
                if (x != 59 && x != 60)
                {
                    int pawnPos = x - 8;

                    board.Score += CheckPawnWall2(board, pawnPos, x);

                    pawnPos = x - 7;

                    board.Score += CheckPawnWall2(board, pawnPos, x);

                    pawnPos = x - 9;

                    board.Score += CheckPawnWall2(board, pawnPos, x);
                }
            }
        }
        else if (square.Piece1.PieceColor == ChessPieceColor::Black)
        {
            board.Score -= EvaluatePieceScore2(square, x, board.EndGamePhase,
                blackKnightCount, blackBishopCount, insufficientMaterial, blackPawnCount, whitePawnCount);


            if (square.Piece1.PieceType == ChessPieceType::King)
            {
                if (x != 3 && x != 4)
                {
                    int pawnPos = x + 8;

                    board.Score -= CheckPawnWall2(board, pawnPos, x);

                    pawnPos = x + 7;

                    board.Score -= CheckPawnWall2(board, pawnPos, x);

                    pawnPos = x + 9;

                    board.Score -= CheckPawnWall2(board, pawnPos, x);
                }

            }

        }

        if (square.Piece1.PieceType == ChessPieceType::Knight)
        {
            knightCount = (knightCount + 1);

            if (knightCount > 1)
            {
                insufficientMaterial = false;
            }
        }
        /*
        if ((blackBishopCount + whiteBishopCount) > 1)
        {
            insufficientMaterial = false;
        }
        else if ((blackBishopCount + blackKnightCount) > 1)
        {
            insufficientMaterial = false;
        }
        else if ((whiteBishopCount + whiteKnightCount) > 1)
        {
            insufficientMaterial = false;
        }
        */
    }

    if (insufficientMaterial)
    {
        board.Score = 0;
        board.StaleMate = true;
        board.InsufficientMaterial = true;
        return;
    }

    if (board.EndGamePhase)
    {
        if (board.BlackCheck)
        {
            board.Score += 10;
        }
        else if (board.WhiteCheck)
        {
            board.Score -= 10;
        }
    }
    else
    {
        if (!board.WhiteCanCastle && !board.WhiteCastled)
        {
            board.Score -= 50;
        }
        if (!board.BlackCanCastle && !board.BlackCastled)
        {
            board.Score += 50;
        }
    }

    //Black Isolated Pawns
    if (blackPawnCount[0] >= 1 && blackPawnCount[1] == 0)
    {
        board.Score += 12;
    }
    if (blackPawnCount[1] >= 1 && blackPawnCount[0] == 0 &&
        blackPawnCount[2] == 0)
    {
        board.Score += 14;
    }
    if (blackPawnCount[2] >= 1 && blackPawnCount[1] == 0 &&
        blackPawnCount[3] == 0)
    {
        board.Score += 16;
    }
    if (blackPawnCount[3] >= 1 && blackPawnCount[2] == 0 &&
        blackPawnCount[4] == 0)
    {
        board.Score += 20;
    }
    if (blackPawnCount[4] >= 1 && blackPawnCount[3] == 0 &&
        blackPawnCount[5] == 0)
    {
        board.Score += 20;
    }
    if (blackPawnCount[5] >= 1 && blackPawnCount[4] == 0 &&
        blackPawnCount[6] == 0)
    {
        board.Score += 16;
    }
    if (blackPawnCount[6] >= 1 && blackPawnCount[5] == 0 &&
        blackPawnCount[7] == 0)
    {
        board.Score += 14;
    }
    if (blackPawnCount[7] >= 1 && blackPawnCount[6] == 0)
    {
        board.Score += 12;
    }

    //White Isolated Pawns
    if (whitePawnCount[0] >= 1 && whitePawnCount[1] == 0)
    {
        board.Score -= 12;
    }
    if (whitePawnCount[1] >= 1 && whitePawnCount[0] == 0 &&
        whitePawnCount[2] == 0)
    {
        board.Score -= 14;
    }
    if (whitePawnCount[2] >= 1 && whitePawnCount[1] == 0 &&
        whitePawnCount[3] == 0)
    {
        board.Score -= 16;
    }
    if (whitePawnCount[3] >= 1 && whitePawnCount[2] == 0 &&
        whitePawnCount[4] == 0)
    {
        board.Score -= 20;
    }
    if (whitePawnCount[4] >= 1 && whitePawnCount[3] == 0 &&
        whitePawnCount[5] == 0)
    {
        board.Score -= 20;
    }
    if (whitePawnCount[5] >= 1 && whitePawnCount[4] == 0 &&
        whitePawnCount[6] == 0)
    {
        board.Score -= 16;
    }
    if (whitePawnCount[6] >= 1 && whitePawnCount[5] == 0 &&
        whitePawnCount[7] == 0)
    {
        board.Score -= 14;
    }
    if (whitePawnCount[7] >= 1 && whitePawnCount[6] == 0)
    {
        board.Score -= 12;
    }

    //Black Passed Pawns
    if (blackPawnCount[0] >= 1 && whitePawnCount[0] == 0)
    {
        board.Score -= blackPawnCount[0];
    }
    if (blackPawnCount[1] >= 1 && whitePawnCount[1] == 0)
    {
        board.Score -= blackPawnCount[1];
    }
    if (blackPawnCount[2] >= 1 && whitePawnCount[2] == 0)
    {
        board.Score -= blackPawnCount[2];
    }
    if (blackPawnCount[3] >= 1 && whitePawnCount[3] == 0)
    {
        board.Score -= blackPawnCount[3];
    }
    if (blackPawnCount[4] >= 1 && whitePawnCount[4] == 0)
    {
        board.Score -= blackPawnCount[4];
    }
    if (blackPawnCount[5] >= 1 && whitePawnCount[5] == 0)
    {
        board.Score -= blackPawnCount[5];
    }
    if (blackPawnCount[6] >= 1 && whitePawnCount[6] == 0)
    {
        board.Score -= blackPawnCount[6];
    }
    if (blackPawnCount[7] >= 1 && whitePawnCount[7] == 0)
    {
        board.Score -= blackPawnCount[7];
    }

    //White Passed Pawns
    if (whitePawnCount[0] >= 1 && blackPawnCount[1] == 0)
    {
        board.Score += whitePawnCount[0];
    }
    if (whitePawnCount[1] >= 1 && blackPawnCount[1] == 0)
    {
        board.Score += whitePawnCount[1];
    }
    if (whitePawnCount[2] >= 1 && blackPawnCount[2] == 0)
    {
        board.Score += whitePawnCount[2];
    }
    if (whitePawnCount[3] >= 1 && blackPawnCount[3] == 0)
    {
        board.Score += whitePawnCount[3];
    }
    if (whitePawnCount[4] >= 1 && blackPawnCount[4] == 0)
    {
        board.Score += whitePawnCount[4];
    }
    if (whitePawnCount[5] >= 1 && blackPawnCount[5] == 0)
    {
        board.Score += whitePawnCount[5];
    }
    if (whitePawnCount[6] >= 1 && blackPawnCount[6] == 0)
    {
        board.Score += whitePawnCount[6];
    }
    if (whitePawnCount[7] >= 1 && blackPawnCount[7] == 0)
    {
        board.Score += whitePawnCount[7];
    }

    //std::cout << "Score from EvaluateBoardScore2 is : " << board.Score << std::endl;
}

int CheckPawnWall2(Board board, int pawnPos, int kingPos)
{

    if (kingPos % 8 == 7 && pawnPos % 8 == 0)
    {
        return 0;
    }

    if (kingPos % 8 == 0 && pawnPos % 8 == 7)
    {
        return 0;
    }

    if (pawnPos > 63 || pawnPos < 0)
    {
        return 0;
    }

    if (board.Squares[pawnPos].Piece1.PieceType != ChessPieceType::None)
    {
        if (board.Squares[pawnPos].Piece1.PieceColor == board.Squares[kingPos].Piece1.PieceColor)
        {
            if (board.Squares[pawnPos].Piece1.PieceType == ChessPieceType::Pawn)
            {
                return 10;
            }
        }
    }

    return 0;
}

