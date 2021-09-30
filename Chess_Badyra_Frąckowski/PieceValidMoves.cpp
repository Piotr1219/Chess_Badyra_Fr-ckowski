#include <string>
#include <list>
#include <stack>
#include <iostream>
#include "PieceValidMoves.h"
//#include "Engine.h"
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
//#include "Square.h"

using namespace std;

void PieceValidMoves::AnalyzeMovePawn(Board& board, char dstPos, Piece& pcMoving)
{
    //Because Pawns only kill diagonaly we handle the En Passant scenario specialy
    if (board.EnPassantPosition > 0)
    {
        if (pcMoving.PieceColor != board.EnPassantColor)
        {
            if (board.EnPassantPosition == dstPos)
            {
                //We have an En Passant Possible
                pcMoving.ValidMoves.push_back(dstPos);

                if (pcMoving.PieceColor == ChessPieceColor::White)
                {
                    board.WhiteAttackBoard[dstPos] = true;
                }
                else
                {
                    board.BlackAttackBoard[dstPos] = true;
                }
            }
        }
    }

    Piece pcAttacked = board.Squares[dstPos].Piece1;

    //If there no piece there I can potentialy kill
    //Piece* attacked = &pcAttacked;
    //if (pcAttacked == NULL)
    if(pcAttacked.PieceType == ChessPieceType::None)
        return;

    //Regardless of what is there I am attacking this square
    if (pcMoving.PieceColor == ChessPieceColor::White)
    {
        board.WhiteAttackBoard[dstPos] = true;

        //if that piece is the same color
        if (pcAttacked.PieceColor == pcMoving.PieceColor)
        {
            pcAttacked.DefendedValue += pcMoving.PieceActionValue;
            board.Squares[dstPos].Piece1.DefendedValue += pcMoving.PieceActionValue; //moze potrzebne
            return;
        }

        pcAttacked.AttackedValue += pcMoving.PieceActionValue;
        board.Squares[dstPos].Piece1.AttackedValue += pcMoving.PieceActionValue; //moze potrzebne

        //If this is a king set it in check                   
        if (pcAttacked.PieceType == ChessPieceType::King)
        {
            board.BlackCheck = true;
        }
        else
        {
            //Add this as a valid move
            pcMoving.ValidMoves.push_back(dstPos);
        }
    }
    else
    {
        board.BlackAttackBoard[dstPos] = true;

        //if that piece is the same color
        if (pcAttacked.PieceColor == pcMoving.PieceColor)
        {
            pcAttacked.DefendedValue += pcMoving.PieceActionValue;
            board.Squares[dstPos].Piece1.DefendedValue += pcMoving.PieceActionValue; //moze potrzebne
            return;
        }

        pcAttacked.AttackedValue += pcMoving.PieceActionValue;
        board.Squares[dstPos].Piece1.AttackedValue += pcMoving.PieceActionValue; //moze potrzebne

        //If this is a king set it in check                   
        if (pcAttacked.PieceType == ChessPieceType::King)
        {
            board.WhiteCheck = true;
        }
        else
        {
            //Add this as a valid move
            pcMoving.ValidMoves.push_back(dstPos);
        }
    }

    return;
}

bool PieceValidMoves::AnalyzeMove(Board& board, char dstPos, Piece& pcMoving)
{
    //If I am not a pawn everywhere I move I can attack
    if (pcMoving.PieceColor == ChessPieceColor::White)
    {
        board.WhiteAttackBoard[dstPos] = true;
    }
    else
    {
        board.BlackAttackBoard[dstPos] = true;
    }

    //If there no piece there I can potentialy kill just add the move and exit
    if (board.Squares[dstPos].Piece1.PieceType == ChessPieceType::None)
    {
        pcMoving.ValidMoves.push_back(dstPos);

        return true;
    }

    Piece pcAttacked = board.Squares[dstPos].Piece1;

    //if that piece is a different color
    if (pcAttacked.PieceColor != pcMoving.PieceColor)
    {
        pcAttacked.AttackedValue += pcMoving.PieceActionValue;
        board.Squares[dstPos].Piece1.AttackedValue += pcMoving.PieceActionValue; //moze potrzebne

        //If this is a king set it in check                   
        if (pcAttacked.PieceType == ChessPieceType::King)
        {
            if (pcAttacked.PieceColor == ChessPieceColor::Black)
            {
                board.BlackCheck = true;
            }
            else
            {
                board.WhiteCheck = true;
            }
        }
        else
        {
            //Add this as a valid move
            pcMoving.ValidMoves.push_back(dstPos);
        }


        //We don't continue movement past this piece
        return false;
    }
    //Same Color I am defending
    pcAttacked.DefendedValue += pcMoving.PieceActionValue;
    board.Squares[dstPos].Piece1.DefendedValue += pcMoving.PieceActionValue; //moze potrzebne

    //Since this piece is of my kind I can't move there
    return false;
}

void PieceValidMoves::CheckValidMovesPawn(list<char> moves, Piece& pcMoving, char srcPosition,
                                        Board& board, char count)
{
    for (short i = 0; i < count; i++)
    {
        //char dstPos = moves[i];
        list<char>::iterator it = moves.begin();
        advance(it, i);
        char dstPos = *it;

        //Diagonal
        if (dstPos % 8 != srcPosition % 8)
        {
            //If there is a piece there I can potentialy kill
            AnalyzeMovePawn(board, dstPos, pcMoving);

            if (pcMoving.PieceColor == ChessPieceColor::White)
            {
                board.WhiteAttackBoard[dstPos] = true;
            }
            else
            {
                board.BlackAttackBoard[dstPos] = true;
            }
        }
        // if there is something if front pawns can't move there
        else if (board.Squares[dstPos].Piece1.PieceType != ChessPieceType::None)
        {
            return;
        }
        //if there is nothing in front of 
        else
        {
            pcMoving.ValidMoves.push_back(dstPos);
        }
    }
    //for (auto const& i : pcMoving.ValidMoves) {
    //    cout << "valid in pawn checking" << i << std::endl;
    //}
}

void PieceValidMoves::GenerateValidMovesKing(Piece& piece, Board& board, char srcPosition)
{
    Piece* attacked = &piece;
    //if (pcAttacked == NULL)
    if (attacked == NULL)
    {
        return;
    }

    for (short i = 0; i < MoveArrays::KingTotalMoves[srcPosition]; i++)
    {
        list<char>::iterator it = MoveArrays::KingMoves[srcPosition].Moves.begin();
        advance(it, i);
        char dstPos = *it;

        if (piece.PieceColor == ChessPieceColor::White)
        {
            //I can't move where I am being attacked
            if (board.BlackAttackBoard[dstPos])
            {
                board.WhiteAttackBoard[dstPos] = true;
                continue;
            }
        }
        else
        {
            if (board.WhiteAttackBoard[dstPos])
            {
                board.BlackAttackBoard[dstPos] = true;
                continue;
            }
        }

        AnalyzeMove(board, dstPos, piece);
    }
}

void PieceValidMoves::GenerateValidMovesKingCastle(Board& board, Piece& king)
{
    //This code will add the castleling move to the pieces available moves
    if (king.PieceColor == ChessPieceColor::White)
    {
        if (board.Squares[63].Piece1.PieceType != ChessPieceType::None)
        {
            //Check if the Right Rook is still in the correct position
            if (board.Squares[63].Piece1.PieceType == ChessPieceType::Rook)
            {
                if (board.Squares[63].Piece1.PieceColor == king.PieceColor)
                {
                    //Move one column to right see if its empty
                    if (board.Squares[62].Piece1.PieceType == ChessPieceType::None)
                    {
                        if (board.Squares[61].Piece1.PieceType == ChessPieceType::None)
                        {
                            if (board.BlackAttackBoard[61] == false &&
                                board.BlackAttackBoard[62] == false)
                            {
                                //Ok looks like move is valid lets add it
                                king.ValidMoves.push_back((char)62);
                                board.WhiteAttackBoard[62] = true;
                            }
                        }
                    }
                }
            }
        }

        if (board.Squares[56].Piece1.PieceType != ChessPieceType::None)
        {
            //Check if the Left Rook is still in the correct position
            if (board.Squares[56].Piece1.PieceType == ChessPieceType::Rook)
            {
                if (board.Squares[56].Piece1.PieceColor == king.PieceColor)
                {
                    //Move one column to right see if its empty
                    if (board.Squares[57].Piece1.PieceType == ChessPieceType::None)
                    {
                        if (board.Squares[58].Piece1.PieceType == ChessPieceType::None)
                        {
                            if (board.Squares[59].Piece1.PieceType == ChessPieceType::None)
                            {
                                if (board.BlackAttackBoard[58] == false &&
                                    board.BlackAttackBoard[59] == false)
                                {
                                    //Ok looks like move is valid lets add it
                                    king.ValidMoves.push_back((char)58);
                                    board.WhiteAttackBoard[58] = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (king.PieceColor == ChessPieceColor::Black)
    {
        //There are two ways to castle, scenario 1:
        if (board.Squares[7].Piece1.PieceType != ChessPieceType::None)
        {
            //Check if the Right Rook is still in the correct position
            if (board.Squares[7].Piece1.PieceType == ChessPieceType::Rook
                && !board.Squares[7].Piece1.Moved)
            {
                if (board.Squares[7].Piece1.PieceColor == king.PieceColor)
                {
                    //Move one column to right see if its empty

                    if (board.Squares[6].Piece1.PieceType == ChessPieceType::None)
                    {
                        if (board.Squares[5].Piece1.PieceType == ChessPieceType::None)
                        {
                            if (board.WhiteAttackBoard[5] == false && board.WhiteAttackBoard[6] == false)
                            {
                                //Ok looks like move is valid lets add it
                                king.ValidMoves.push_back((char)6);
                                board.BlackAttackBoard[6] = true;
                            }
                        }
                    }
                }
            }
        }
        //There are two ways to castle, scenario 2:
        if (board.Squares[0].Piece1.PieceType != ChessPieceType::None)
        {
            //Check if the Left Rook is still in the correct position
            if (board.Squares[0].Piece1.PieceType == ChessPieceType::Rook &&
                !board.Squares[0].Piece1.Moved)
            {
                if (board.Squares[0].Piece1.PieceColor ==
                    king.PieceColor)
                {
                    //Move one column to right see if its empty
                    if (board.Squares[1].Piece1.PieceType == ChessPieceType::None)
                    {
                        if (board.Squares[2].Piece1.PieceType == ChessPieceType::None)
                        {
                            if (board.Squares[3].Piece1.PieceType == ChessPieceType::None)
                            {
                                if (board.WhiteAttackBoard[2] == false &&
                                    board.WhiteAttackBoard[3] == false)
                                {
                                    //Ok looks like move is valid lets add it
                                    king.ValidMoves.push_back((char)2);
                                    board.BlackAttackBoard[2] = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void PieceValidMoves::GenerateValidMoves(Board& board)
{
    // Reset Board
    board.BlackCheck = false;
    board.WhiteCheck = false;

    short blackRooksMoved = 0;
    short whiteRooksMoved = 0;

    for (int i = 0; i < 64; i++) {
        board.WhiteAttackBoard[i] = false;
        board.BlackAttackBoard[i] = false;
    }

    //Calculate Remaining Material on Board to make the End Game Decision
    int remainingPieces = 0;

    //Generate Moves

    for (short x = 0; x < 64; x++)
    {
        Square sqr = board.Squares[x];

        board.Squares[x].Piece1.ValidMoves.clear();

        if (board.Squares[x].Piece1.PieceType == ChessPieceType::None) {
            continue;
        }
        //cout << "analizowany ruch " << board.Squares[x].Piece1.PieceType << endl;
        //board.Squares[x].Piece1.ValidMoves = list<char>(board.Squares[x].Piece1.LastValidMoveCount);

        remainingPieces++;

        switch (board.Squares[x].Piece1.PieceType)
        {
        case ChessPieceType::Pawn:
                {
                    if (board.Squares[x].Piece1.PieceColor == ChessPieceColor::White)
                    {
                        //for (auto const& i : MoveArrays::WhitePawnMoves[x].Moves) {
                        //    cout << "white pawn moves" << i << std::endl;
                        //}
                        CheckValidMovesPawn(MoveArrays::WhitePawnMoves[x].Moves, board.Squares[x].Piece1, (char)x,
                                            board, MoveArrays::WhitePawnTotalMoves[x]);
                        //for (auto const& i : board.Squares[x].Piece1.ValidMoves) {
                        //    cout << "white pawn valid moves" << i << std::endl;
                        //}
                        break;
                    }
                    if (board.Squares[x].Piece1.PieceColor == ChessPieceColor::Black)
                    {
                        CheckValidMovesPawn(MoveArrays::BlackPawnMoves[x].Moves, board.Squares[x].Piece1, (char)x,
                                            board, MoveArrays::BlackPawnTotalMoves[x]);
                        break;
                    }

                    break;
                }
        case ChessPieceType::Knight:
                {
                    for (short i = 0; i < MoveArrays::KnightTotalMoves[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::KnightMoves[x].Moves.begin();
                        advance(it, i);

                        AnalyzeMove(board, *it, board.Squares[x].Piece1);
                    }

                    break;
                }
        case ChessPieceType::Bishop:
                {
                    for (short i = 0; i < MoveArrays::BishopTotalMoves1[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::BishopMoves1[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::BishopTotalMoves2[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::BishopMoves2[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::BishopTotalMoves3[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::BishopMoves3[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::BishopTotalMoves4[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::BishopMoves4[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }

                    break;
                }
        case ChessPieceType::Rook:
                {
                    if (board.Squares[x].Piece1.Moved)
                    {
                        if (board.Squares[x].Piece1.PieceColor == ChessPieceColor::Black)
                        {
                            blackRooksMoved++;
                        }
                        else
                        {
                            whiteRooksMoved++;
                        }
                    }


                    for (short i = 0; i < MoveArrays::RookTotalMoves1[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::RookMoves1[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::RookTotalMoves2[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::RookMoves2[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::RookTotalMoves3[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::RookMoves3[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::RookTotalMoves4[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::RookMoves4[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }

                    break;
                }
        case ChessPieceType::Queen:
                {
                    for (short i = 0; i < MoveArrays::QueenTotalMoves1[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves1[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::QueenTotalMoves2[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves2[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::QueenTotalMoves3[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves3[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::QueenTotalMoves4[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves4[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }

                    for (short i = 0; i < MoveArrays::QueenTotalMoves5[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves5[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::QueenTotalMoves6[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves6[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::QueenTotalMoves7[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves7[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < MoveArrays::QueenTotalMoves8[x]; i++)
                    {
                        list<char>::iterator it = MoveArrays::QueenMoves8[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }

                    break;
                }
        case ChessPieceType::King:
                {
                    if (board.Squares[x].Piece1.PieceColor == ChessPieceColor::White)
                    {
                        if (board.Squares[x].Piece1.Moved)
                        {
                            board.WhiteCanCastle = false;
                        }
                        board.WhiteKingPosition = x;
                    }
                    else
                    {
                        if (board.Squares[x].Piece1.Moved)
                        {
                            board.BlackCanCastle = false;
                        }
                        board.BlackKingPosition = x;
                    }

                    break;
                }
        }
    }


    if (blackRooksMoved > 1)
    {
        board.BlackCanCastle = false;
    }
    if (whiteRooksMoved > 1)
    {
        board.WhiteCanCastle = false;
    }

    if (remainingPieces < 10)
    {
        board.EndGamePhase = true;
    }


    if (board.WhoseMove == ChessPieceColor::White)
    {
        GenerateValidMovesKing(board.Squares[board.BlackKingPosition].Piece1, board,
                                board.BlackKingPosition);
        GenerateValidMovesKing(board.Squares[board.WhiteKingPosition].Piece1, board,
                                board.WhiteKingPosition);
    }
    else
    {
        GenerateValidMovesKing(board.Squares[board.WhiteKingPosition].Piece1, board,
                                board.WhiteKingPosition);
        GenerateValidMovesKing(board.Squares[board.BlackKingPosition].Piece1, board,
                                board.BlackKingPosition);
    }


    //Now that all the pieces were examined we know if the king is in check
    if (!board.WhiteCastled && board.WhiteCanCastle && !board.WhiteCheck)
    {
        GenerateValidMovesKingCastle(board, board.Squares[board.WhiteKingPosition].Piece1);
    }
    if (!board.BlackCastled && board.BlackCanCastle && !board.BlackCheck)
    {
        GenerateValidMovesKingCastle(board, board.Squares[board.BlackKingPosition].Piece1);
    }
}
