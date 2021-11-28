#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <iostream>
///#include "Engine.h"
#include "Program.h"
#include "PositionEvaluationCuda.cuh"
///#include "functions.h"
//#include "Board.h"
//#include "Book.h"
//#include "Piece.h"

using namespace std;


void Program::Main(string args[])
{
	RunEngine();
}

void Program::RunEngine()
{
	bool ShowBoard = false;

	//Engine engine = Engine();
	Engine engine;
	DrawBoard(engine);
	std::cout << engine.FEN() << endl;

	printf("Chess Core\n");
	printf("Version: 1.0.1\n");
	printf("\n");
	printf("Type quit to exit\n");
	printf("Type show to show board\n");
	printf("\n");
	printf("feature setboard=1\n");

	
	while (true)
	{
		std::cout << "Start of while loop \n\n";
		try
		{
			if (ShowBoard)
			{
				DrawBoard(engine);
			}

			if (engine.ChessBoard.WhoseMove != engine.HumanPlayer)
			{
				std::cout << "It is a move of " << engine.WhoseMove() << endl;

				for (int i = 0; i < 64; i++) {
					for (std::list<char>::iterator it = engine.ChessBoard.Squares[i].Piece1.ValidMoves.begin(); it != engine.ChessBoard.Squares[i].Piece1.ValidMoves.end(); ++it) {
						char field = *it;
						//cout << "dozwolony ruch z pola " << i << " na pole " << (int)field << endl;
					}
				}

				MakeEngineMove(engine);
				//to ponizej dodalem bo chyba nigdzie nie ustawia
				// albo i nie potrzebne (w sumie nie wiem)
				//engine.setWhoseMove(engine.HumanPlayer);
			}
			else
			{
				printf("\n");

				string move;
				//scanf_s("%s", move, 4);
				//EvaluatePieces::test();
				std::cout << "wpisz sowj ruch:" << endl;
				cin >> move;

				printf("wpisano: %s \n", move.c_str());

				if (move.empty())
				{
					continue;
				}

				//move = trim(move);


				if (move == "new")
				{
					engine.NewGame();
					continue;
				}
				if (move == "quit")
				{
					return;
				}
				if (move == "xboard")
				{
					continue;
				}
				if (move == "show")
				{
					ShowBoard = !ShowBoard;

					continue;
				}
				if (move.rfind("edit", 0) == 0)
				{
					continue;
				}
				if (move == "hint")
				{
					continue;
				}
				if (move == "bk")
				{
					continue;
				}
				if (move == "undo")
				{
					engine.Undo();
					continue;
				}
				if (move == "remove")
				{
					continue;
				}
				if (move == "remove")
				{
					continue;
				}
				if (move == "hard")
				{
					engine.setGameDifficulty(Engine::Difficulty::Hard);
					continue;
				}
				if (move == "easy")
				{
					continue;
				}
				if (move.rfind("accepted", 0) == 0)
				{
					continue;
				}
				if (move.rfind("rejected", 0) == 0)
				{
					continue;
				}
				if (move.rfind("variant", 0) == 0)
				{
					continue;
				}
				if (move == "random")
				{
					continue;
				}
				if (move == "force")
				{
					continue;
				}
				if (move == "go")
				{
					continue;
				}
				if (move == "playother")
				{
					if (engine.WhoseMove() == ChessPieceColor::White)
					{
						engine.HumanPlayer = ChessPieceColor::Black;
					}
					else if (engine.WhoseMove() == ChessPieceColor::Black)
					{
						engine.HumanPlayer = ChessPieceColor::White;
					}

					continue;
				}
				if (move == "white")
				{
					engine.HumanPlayer = ChessPieceColor::Black;

					if (engine.WhoseMove() != engine.HumanPlayer)
					{
						MakeEngineMove(engine);
					}
					continue;
				}
				if (move == "black")
				{
					engine.HumanPlayer = ChessPieceColor::White;

					if (engine.WhoseMove() != engine.HumanPlayer)
					{
						MakeEngineMove(engine);
					}
					continue;
				}
				if (move.rfind("level", 0) == 0)
				{
					continue;
				}
				if (move.rfind("st", 0) == 0)
				{
					continue;
				}
				if (move.rfind("sd", 0) == 0)
				{
					continue;
				}
				if (move.rfind("time", 0) == 0)
				{
					continue;
				}
				if (move.rfind("otim", 0) == 0)
				{
					continue;
				}
				if (move == "?")
				{
					continue;
				}
				if (move.rfind("ping", 0) == 0)
				{
					if (move.find(" ") > 0)
					{
						string pong = move.substr(move.find(" "), move.length() - move.find(" "));

						printf("pong %s", pong);
					}
					continue;
				}
				if (move.rfind("result", 0) == 0)
				{
					continue;
				}
				if (move.rfind("setboard", 0) == 0)
				{
					if (move.find(" ") > 0)
					{
						string fen = trim(move.substr(move.find(" "), move.length() - move.find(" ")));

						engine.InitiateBoard(fen);
					}

					continue;
				}
				if (move.rfind("setboard", 0) == 0)
				{
					continue;
				}
				if (move.rfind("edit", 0) == 0)
				{
					engine.NewGame();
					continue;
				}
				if (move.rfind("1/2-1/2", 0) == 0)
				{
					engine.NewGame();
					continue;
				}
				if (move.rfind("0-1", 0) == 0)
				{
					engine.NewGame();
					continue;
				}
				if (move.rfind("1-0", 0) == 0)
				{
					engine.NewGame();
					continue;
				}

				if (move.length() < 4)
				{
					continue;
				}

				if (move.length() > 5)
				{
					continue;
				}
				//printf("%i", move.length());

				string src = move.substr(0, 2);
				string dst = move.substr(2, 2);

				char srcCol;
				char srcRow;
				char dstRow;
				char dstCol;

				//try
				//{
				srcCol = GetColumn(src);
				srcRow = GetRow(src);
				dstRow = GetRow(dst);
				dstCol = GetColumn(dst);
				//}
				//catch (int ex)
				if (srcCol == 255 || srcRow == 255 || dstRow == 255 || dstCol == 255)
				{
					//Console.WriteLine(ex.Message);
					printf("Error");
					continue;
				}
				//pomocnicze wypisanie rzedow i kolumn
				std::cout << " " << int(srcCol) << " " << int(srcRow) << " " << int(dstCol) << " " << int(dstRow) << endl;

				//wypisanie mozliwych ruchow
				//for (engine.ChessBoard.Squares[0].Piece1.ValidMoves)
				for(int i=0; i<64; i++){
					for (std::list<char>::iterator it = engine.ChessBoard.Squares[i].Piece1.ValidMoves.begin(); it != engine.ChessBoard.Squares[i].Piece1.ValidMoves.end(); ++it) {
						char field = *it;
						//cout << "dozwolony ruch z pola " << i << " na pole " << (int)field << endl;
					}
				}

				if (!engine.IsValidMove(srcCol, srcRow, dstCol, dstRow))
				{
					printf("Invalid Move");
					continue;
				}

				if (!engine.MovePiece(srcCol, srcRow, dstCol, dstRow)) {
					continue;
				}

				std::cout << "wypisanie tablicy tylko po ruchu czlowieka" << endl;
				DrawBoard(engine);

				MakeEngineMove(engine);

				std::cout << "MakeEngineMove ended \n";
				std::cout << "Position after computer move: " << engine.ChessBoard.ToString() << endl;


				if (engine.StaleMate())
				{
					DrawBoard(engine);
					if (engine.InsufficientMaterial())
					{
						printf("1/2-1/2 {Draw by insufficient material}");
					}
					else if (engine.RepeatedMove())
					{
						printf("1/2-1/2 {Draw by repetition}");
					}
					else if (engine.FiftyMove())
					{
						printf("1/2-1/2 {Draw by fifty move rule}");
					}
					else
					{
						printf("1/2-1/2 {Stalemate}");
					}
					engine.NewGame();
				}
				else if (engine.GetWhiteMate())
				{
					DrawBoard(engine);
					printf("0-1 {Black mates}");
					engine.NewGame();
				}
				else if (engine.GetBlackMate())
				{
					DrawBoard(engine);
					printf("1-0 {White mates}");
					engine.NewGame();
				}
			}
		}
		//catch (Exception ex)
		catch(int ex)
		{
			//Console.WriteLine(ex.Message);
			printf("Error %i", ex);
			return;
		}

		std::cout << "Ending whole segment of code \n";
		ShowBoard = true;
		//engine.HumanPlayer = 1;
		std::cout << "Is it human move now? " << engine.HumanPlayer << endl;
	}
	
}

void Program::MakeEngineMove(Engine &engine)
{
	//DateTime start = DateTime.Now;
	//auto start = std::chrono::system_clock::now();
	time_t start;
	time(&start);

	engine.AiPonderMove();

	auto Moves = engine.GetMoveHistory();
	list<MoveContent>::iterator it = Moves.begin();
	//list<MoveContent>::iterator it = engine.GetMoveHistory().begin();
	std::cout << "rozmiar listy " << engine.GetMoveHistory().size() << endl;
	MoveContent lastMove = *it;

	//MoveContent lastMove = engine.GetMoveHistory().ToArray()[0];

	string tmp = "";

	char sourceColumn = lastMove.MovingPiecePrimary.SrcPosition % 8;
	char srcRow = 8 - (lastMove.MovingPiecePrimary.SrcPosition / 8);
	char destinationColumn = lastMove.MovingPiecePrimary.DstPosition % 8;
	char destinationRow = 8 - (lastMove.MovingPiecePrimary.DstPosition / 8);

	tmp += GetPgnMove(lastMove.MovingPiecePrimary.PieceType);

	if (lastMove.MovingPiecePrimary.PieceType == ChessPieceType::Knight)
	{
		tmp += GetColumnFromInt(sourceColumn + 1);
		tmp += (char)srcRow;
	}
	else if (lastMove.MovingPiecePrimary.PieceType == ChessPieceType::Rook)
	{
		tmp += GetColumnFromInt(sourceColumn + 1);
		tmp += (char)srcRow;
	}
	else if (lastMove.MovingPiecePrimary.PieceType == ChessPieceType::Pawn)
	{
		if (sourceColumn != destinationColumn)
		{
			tmp += GetColumnFromInt(sourceColumn + 1);
		}
	}

	if (lastMove.TakenPiece.PieceType != ChessPieceType::None)
	{
		tmp += "x";
	}

	tmp += GetColumnFromInt(destinationColumn + 1);

	tmp += destinationRow;

	if (lastMove.PawnPromotedTo == ChessPieceType::Queen)
	{
		tmp += "=Q";
	}
	else if (lastMove.PawnPromotedTo == ChessPieceType::Rook)
	{
		tmp += "=R";
	}
	else if (lastMove.PawnPromotedTo == ChessPieceType::Knight)
	{
		tmp += "=K";
	}
	else if (lastMove.PawnPromotedTo == ChessPieceType::Bishop)
	{
		tmp += "=B";
	}

	time_t now = time(0);
	//DateTime end = DateTime.Now;
	time_t end;
	time(&end);

	int ts = difftime(end, start);		//time difference in seconds
	//TimeSpan ts = end - start;

	printf("%hhx", engine.PlyDepthReached);
	printf("\n ");

	std::cout << engine.ChessBoard.ToString() << endl;
	/*int score = engine.GetScore();

	if (score > 0)
	{
		score = score / 10;
	}

	std::cout << "score: " << score << " " << endl;
	printf(ts * 100 + " ");
	printf(engine.NodesSearched + engine.NodesQuiessence + " ");
	printf("%hhx", engine.PvLine());
	printf("");

	printf("move ");
	printf(tmp.c_str());
	*/
}

string Program::GetColumnFromInt(int column)
{
	string returnColumnt;

	switch (column)
	{
	case 1:
		returnColumnt = "a";
		break;
	case 2:
		returnColumnt = "b";
		break;
	case 3:
		returnColumnt = "c";
		break;
	case 4:
		returnColumnt = "d";
		break;
	case 5:
		returnColumnt = "e";
		break;
	case 6:
		returnColumnt = "f";
		break;
	case 7:
		returnColumnt = "g";
		break;
	case 8:
		returnColumnt = "h";
		break;
	default:
		returnColumnt = "Unknown";
		break;
	}

	return returnColumnt;
}

string Program::GetPgnMove(ChessPieceType pieceType)
{
	string move = "";

	if (pieceType == ChessPieceType::Bishop)
	{
		move += "B";
	}
	else if (pieceType == ChessPieceType::King)
	{
		move += "K";
	}
	else if (pieceType == ChessPieceType::Knight)
	{
		move += "N";
	}
	else if (pieceType == ChessPieceType::Queen)
	{
		move += "Q";
	}
	else if (pieceType == ChessPieceType::Rook)
	{
		move += "R";
	}

	return move;
}

char Program::GetRow(string move)
{
	if (move != "")
	{
		if (move.length() == 2)
		{
			string row;
			//transform((move.substr(1, 1)).begin(), (move.substr(1, 1)).end(), (move.substr(1, 1)).begin(), [](unsigned char c) { return tolower(c); });
			row = tolower(move[1]);
			//cout << row << endl;
			return (8 - stoi(row));
			//return (stoi(row));
		}
	}

	return 255;
}

char Program::GetColumn(string move)
{
	if (move != "")
	{
		if (move.length() == 2)
		{
			string col = move;
			//transform((col.substr(0, 1)).begin(), (col.substr(0, 1)).end(), (col.substr(0, 1)).begin(), [](unsigned char c) { return tolower(c); });
			col = tolower(move[0]);
			//cout << col << endl;
			//switch (col)
			//{
			if(col == "a")
			{
				return 0;
			}
			else if (col == "b")
			{
				return 1;
			}
			else if (col == "c")
			{
				return 2;
			}
			else if (col == "d")
			{
				return 3;
			}
			else if (col == "e")
			{
				return 4;
			}
			else if (col == "f")
			{
				return 5;
			}
			else if (col == "g")
			{
				return 6;
			}
			else if (col == "h")
			{
				return 7;
			}
			else {
				return 255;
			}
			//}
		}
	}

	return 255;
}

void Program::DrawBoard(Engine engine)
{
	//Console.Clear();

	for (int i = 0; i < 64; i++)
	{
		if (i % 8 == 0)
		{
			printf("\n");
			printf(" ---------------------------------\n");
			printf("%i", 8 - (i / 8));
		}

		ChessPieceType PieceType = engine.GetPieceTypeAt(i);
		ChessPieceColor PieceColor = engine.GetPieceColorAt(i);
		string str;

		switch (PieceType)
		{
		case ChessPieceType::Pawn:
		{
			str = string("| ") + "P ";
			break;
		}
		case ChessPieceType::Knight:
		{
			str = string("| ") + "N ";
			break;
		}
		case ChessPieceType::Bishop:
		{
			str = string("| ") + "B ";
			break;
		}
		case ChessPieceType::Rook:
		{
			str = string("| ") + "R ";
			break;
		}

		case ChessPieceType::Queen:
		{
			str = string("| ") + "Q ";
			break;
		}

		case ChessPieceType::King:
		{
			str = string("| ") + "K ";
			break;
		}
		default:
		{
			str = string("| ") + "  ";
			break;
		}
		}

		if (PieceColor == ChessPieceColor::Black)
		{
			transform(str.begin(), str.end(), str.begin(),
				[](unsigned char c) { return tolower(c); });
		}

		printf(str.c_str());

		if (i % 8 == 7)
		{
			printf("|");
		}
	}

	printf("\n");
	printf(" ---------------------------------\n");
	printf("   A   B   C   D   E   F   G   H\n");

}

