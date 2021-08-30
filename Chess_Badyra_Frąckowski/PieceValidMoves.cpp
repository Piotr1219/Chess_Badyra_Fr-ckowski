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

void PieceValidMoves::AnalyzeMovePawn(Board board, byte dstPos, Piece pcMoving)
{
    //Because Pawns only kill diagonaly we handle the En Passant scenario specialy
    if ((short)board.EnPassantPosition > 0)
    {
        if (pcMoving.PieceColor != board.EnPassantColor)
        {
            if (board.EnPassantPosition == dstPos)
            {
                //We have an En Passant Possible
                pcMoving.ValidMoves.push_back(dstPos);

                if (pcMoving.PieceColor == ChessPieceColor::White)
                {
                    board.WhiteAttackBoard[(short)dstPos] = true;
                }
                else
                {
                    board.BlackAttackBoard[(short)dstPos] = true;
                }
            }
        }
    }

    Piece pcAttacked = board.Squares[(short)dstPos].Piece1;

    //If there no piece there I can potentialy kill
    Piece* attacked = &pcAttacked;
    //if (pcAttacked == NULL)
    if(attacked == NULL)
        return;

    //Regardless of what is there I am attacking this square
    if (pcMoving.PieceColor == ChessPieceColor::White)
    {
        board.WhiteAttackBoard[(short)dstPos] = true;

        //if that piece is the same color
        if (pcAttacked.PieceColor == pcMoving.PieceColor)
        {
            pcAttacked.DefendedValue += pcMoving.PieceActionValue;
            return;
        }

        pcAttacked.AttackedValue += pcMoving.PieceActionValue;

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
        board.BlackAttackBoard[(short)dstPos] = true;

        //if that piece is the same color
        if (pcAttacked.PieceColor == pcMoving.PieceColor)
        {
            pcAttacked.DefendedValue += pcMoving.PieceActionValue;
            return;
        }

        pcAttacked.AttackedValue += pcMoving.PieceActionValue;

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

bool PieceValidMoves::AnalyzeMove(Board board, byte dstPos, Piece pcMoving)
{
    //If I am not a pawn everywhere I move I can attack
    if (pcMoving.PieceColor == ChessPieceColor::White)
    {
        board.WhiteAttackBoard[(short)dstPos] = true;
    }
    else
    {
        board.BlackAttackBoard[(short)dstPos] = true;
    }

    //If there no piece there I can potentialy kill just add the move and exit
    if (board.Squares[(short)dstPos].Piece1.PieceType == ChessPieceType::None)
    {
        pcMoving.ValidMoves.push_back(dstPos);

        return true;
    }

    Piece pcAttacked = board.Squares[(short)dstPos].Piece1;

    //if that piece is a different color
    if (pcAttacked.PieceColor != pcMoving.PieceColor)
    {
        pcAttacked.AttackedValue += pcMoving.PieceActionValue;

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

    //Since this piece is of my kind I can't move there
    return false;
}

void PieceValidMoves::CheckValidMovesPawn(list<byte> moves, Piece& pcMoving, byte srcPosition,
                                        Board& board, byte count)
{
    for (short i = 0; i < (short)count; i++)
    {
        //byte dstPos = moves[i];
        list<byte>::iterator it = moves.begin();
        advance(it, i);
        byte dstPos = *it;

        //Diagonal
        if ((short)dstPos % 8 != (short)srcPosition % 8)
        {
            //If there is a piece there I can potentialy kill
            AnalyzeMovePawn(board, dstPos, pcMoving);

            if (pcMoving.PieceColor == ChessPieceColor::White)
            {
                board.WhiteAttackBoard[(short)dstPos] = true;
            }
            else
            {
                board.BlackAttackBoard[(short)dstPos] = true;
            }
        }
        // if there is something if front pawns can't move there
        else if (board.Squares[(short)dstPos].Piece1.PieceType != ChessPieceType::None)
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
    //    cout << "valid in pawn checking" << (short)i << std::endl;
    //}
}

void PieceValidMoves::GenerateValidMovesKing(Piece piece, Board board, byte srcPosition)
{
    Piece* attacked = &piece;
    //if (pcAttacked == NULL)
    if (attacked == NULL)
    {
        return;
    }

    for (short i = 0; i < (short)MoveArrays::KingTotalMoves[(short)srcPosition]; i++)
    {
        list<byte>::iterator it = MoveArrays::KingMoves[(short)srcPosition].Moves.begin();
        advance(it, i);
        byte dstPos = *it;

        if (piece.PieceColor == ChessPieceColor::White)
        {
            //I can't move where I am being attacked
            if (board.BlackAttackBoard[(short)dstPos])
            {
                board.WhiteAttackBoard[(short)dstPos] = true;
                continue;
            }
        }
        else
        {
            if (board.WhiteAttackBoard[(short)dstPos])
            {
                board.BlackAttackBoard[(short)dstPos] = true;
                continue;
            }
        }

        AnalyzeMove(board, dstPos, piece);
    }
}

void PieceValidMoves::GenerateValidMovesKingCastle(Board board, Piece king)
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
                                king.ValidMoves.push_back((byte)62);
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
                                    king.ValidMoves.push_back((byte)58);
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
                                king.ValidMoves.push_back((byte)6);
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
                                    king.ValidMoves.push_back((byte)2);
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

    //Calculate Remaining Material on Board to make the End Game Decision
    int remainingPieces = 0;

    //Generate Moves

    for (short x = 0; x < 64; x++)
    {
        Square sqr = board.Squares[x];

        if (board.Squares[x].Piece1.PieceType == ChessPieceType::None) {
            continue;
        }

        //board.Squares[x].Piece1.ValidMoves = list<byte>(board.Squares[x].Piece1.LastValidMoveCount);
        board.Squares[x].Piece1.ValidMoves.clear();

        remainingPieces++;

        switch (board.Squares[x].Piece1.PieceType)
        {
        case ChessPieceType::Pawn:
                {
                    if (board.Squares[x].Piece1.PieceColor == ChessPieceColor::White)
                    {
                        //for (auto const& i : MoveArrays::WhitePawnMoves[x].Moves) {
                        //    cout << "white pawn moves" << (short)i << std::endl;
                        //}
                        CheckValidMovesPawn(MoveArrays::WhitePawnMoves[x].Moves, board.Squares[x].Piece1, (byte)x,
                                            board, MoveArrays::WhitePawnTotalMoves[x]);
                        //for (auto const& i : board.Squares[x].Piece1.ValidMoves) {
                        //    cout << "white pawn valid moves" << (short)i << std::endl;
                        //}
                        break;
                    }
                    if (board.Squares[x].Piece1.PieceColor == ChessPieceColor::Black)
                    {
                        CheckValidMovesPawn(MoveArrays::BlackPawnMoves[x].Moves, board.Squares[x].Piece1, (byte)x,
                                            board, MoveArrays::BlackPawnTotalMoves[x]);
                        break;
                    }

                    break;
                }
        case ChessPieceType::Knight:
                {
                    for (short i = 0; i < (short)MoveArrays::KnightTotalMoves[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::KnightMoves[x].Moves.begin();
                        advance(it, i);

                        AnalyzeMove(board, *it, board.Squares[x].Piece1);
                    }

                    break;
                }
        case ChessPieceType::Bishop:
                {
                    for (short i = 0; i < (short)MoveArrays::BishopTotalMoves1[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::BishopMoves1[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::BishopTotalMoves2[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::BishopMoves2[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::BishopTotalMoves3[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::BishopMoves3[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it,
                                        board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::BishopTotalMoves4[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::BishopMoves4[x].Moves.begin();
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


                    for (short i = 0; i < (short)MoveArrays::RookTotalMoves1[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::RookMoves1[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::RookTotalMoves2[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::RookMoves2[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::RookTotalMoves3[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::RookMoves3[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::RookTotalMoves4[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::RookMoves4[x].Moves.begin();
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
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves1[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves1[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves2[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves2[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves3[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves3[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves4[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves4[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }

                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves5[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves5[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves6[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves6[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves7[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves7[x].Moves.begin();
                        advance(it, i);
                        if (
                            AnalyzeMove(board, *it, board.Squares[x].Piece1) ==
                            false)
                        {
                            break;
                        }
                    }
                    for (short i = 0; i < (short)MoveArrays::QueenTotalMoves8[x]; i++)
                    {
                        list<byte>::iterator it = MoveArrays::QueenMoves8[x].Moves.begin();
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
                        board.WhiteKingPosition = (byte)x;
                    }
                    else
                    {
                        if (board.Squares[x].Piece1.Moved)
                        {
                            board.BlackCanCastle = false;
                        }
                        board.BlackKingPosition = (byte)x;
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
        GenerateValidMovesKing(board.Squares[(short)board.BlackKingPosition].Piece1, board,
                                board.BlackKingPosition);
        GenerateValidMovesKing(board.Squares[(short)board.WhiteKingPosition].Piece1, board,
                                board.WhiteKingPosition);
    }
    else
    {
        GenerateValidMovesKing(board.Squares[(short)board.WhiteKingPosition].Piece1, board,
                                board.WhiteKingPosition);
        GenerateValidMovesKing(board.Squares[(short)board.BlackKingPosition].Piece1, board,
                                board.BlackKingPosition);
    }


    //Now that all the pieces were examined we know if the king is in check
    if (!board.WhiteCastled && board.WhiteCanCastle && !board.WhiteCheck)
    {
        GenerateValidMovesKingCastle(board, board.Squares[(short)board.WhiteKingPosition].Piece1);
    }
    if (!board.BlackCastled && board.BlackCanCastle && !board.BlackCheck)
    {
        GenerateValidMovesKingCastle(board, board.Squares[(short)board.BlackKingPosition].Piece1);
    }
}
