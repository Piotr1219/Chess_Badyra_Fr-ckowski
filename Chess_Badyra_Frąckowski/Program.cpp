#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <iostream>
///#include "Engine.h"
#include "Program.h"
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
	cout << engine.FEN() << endl;

	printf("Chess Core\n");
	printf("Version: 1.0.1\n");
	printf("\n");
	printf("Type quit to exit\n");
	printf("Type show to show board\n");
	printf("\n");
	printf("feature setboard=1\n");

	
	while (true)
	{
		try
		{
			if (ShowBoard)
			{
				DrawBoard(engine);
			}

			if (engine.WhoseMove() != engine.HumanPlayer)
			{
				MakeEngineMove(engine);
				//to dodalem bo chyba nigdzie nie ustawia
				// albo i nie potrzebne (w sumie nie wiem)
				//engine.setWhoseMove(engine.HumanPlayer);
			}
			else
			{
				printf("\n");

				string move;
				//scanf_s("%s", move, 4);
				cout << "wpisz sowj ruch:" << endl;
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
					//continue;
				}

				if (move.length() > 5)
				{
					//continue;
				}
				//printf("%i", move.length());

				string src = move.substr(0, 2);
				string dst = move.substr(2, 2);

				byte srcCol;
				byte srcRow;
				byte dstRow;
				byte dstCol;

				//try
				//{
					srcCol = GetColumn(src);
					srcRow = GetRow(src);
					dstRow = GetRow(dst);
					dstCol = GetColumn(dst);
				//}
				//catch (int ex)
				if (srcCol == (byte)255 || srcRow == (byte)255 || dstRow == (byte)255 || dstCol == (byte)255)
				{
					//Console.WriteLine(ex.Message);
					printf("Error");
					continue;
				}
				//pomocnicze wypisanie rzedow i kolumn
				cout << " " << (short)srcCol << " " << (short)srcRow << " " << (short)dstCol << " " << (short)dstRow << endl;
				if (!engine.IsValidMove(srcCol, srcRow, dstCol, dstRow))
				{
					printf("Invalid Move");
					continue;
				}

				engine.MovePiece(srcCol, srcRow, dstCol, dstRow);

				cout << "wypisanie tablicy tylko po ruchu czlowieka" << endl;
				DrawBoard(engine);

				MakeEngineMove(engine);


				if (engine.StaleMate())
				{
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
					printf("0-1 {Black mates}");
					engine.NewGame();
				}
				else if (engine.GetBlackMate())
				{
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
	}
	
}

void Program::MakeEngineMove(Engine engine)
{
	//DateTime start = DateTime.Now;
	//auto start = std::chrono::system_clock::now();
	time_t start;
	time(&start);

	engine.AiPonderMove();

	auto Moves = engine.GetMoveHistory();
	list<MoveContent>::iterator it = Moves.begin();
	//list<MoveContent>::iterator it = engine.GetMoveHistory().begin();
	cout << "rozmiar listy " << engine.GetMoveHistory().size() << endl;
	MoveContent lastMove = *it;

	//MoveContent lastMove = engine.GetMoveHistory().ToArray()[0];

	string tmp = "";

	byte sourceColumn = (byte)((short)lastMove.MovingPiecePrimary.SrcPosition % 8);
	byte srcRow = (byte)(8 - ((short)lastMove.MovingPiecePrimary.SrcPosition / 8));
	byte destinationColumn = (byte)((short)lastMove.MovingPiecePrimary.DstPosition % 8);
	byte destinationRow = (byte)(8 - ((short)lastMove.MovingPiecePrimary.DstPosition / 8));

	tmp += GetPgnMove(lastMove.MovingPiecePrimary.PieceType);

	if (lastMove.MovingPiecePrimary.PieceType == ChessPieceType::Knight)
	{
		tmp += GetColumnFromInt((int)sourceColumn + 1);
		tmp += (char)srcRow;
	}
	else if (lastMove.MovingPiecePrimary.PieceType == ChessPieceType::Rook)
	{
		tmp += GetColumnFromInt((int)sourceColumn + 1);
		tmp += (char)srcRow;
	}
	else if (lastMove.MovingPiecePrimary.PieceType == ChessPieceType::Pawn)
	{
		if (sourceColumn != destinationColumn)
		{
			tmp += GetColumnFromInt((int)sourceColumn + 1);
		}
	}

	if (lastMove.TakenPiece.PieceType != ChessPieceType::None)
	{
		tmp += "x";
	}

	tmp += GetColumnFromInt((int)destinationColumn + 1);

	tmp += (int)destinationRow;

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
	printf(" ");

	cout << engine.ChessBoard.ToString() << endl;
	int score = engine.GetScore();

	if (score > 0)
	{
		score = score / 10;
	}

	cout << "score: " << score << " " << endl;
	printf(ts * 100 + " ");
	printf(engine.NodesSearched + engine.NodesQuiessence + " ");
	printf("%hhx", engine.PvLine());
	printf("");

	printf("move ");
	printf(tmp.c_str());
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

byte Program::GetRow(string move)
{
	if (move != "")
	{
		if (move.length() == 2)
		{
			string row;
			//transform((move.substr(1, 1)).begin(), (move.substr(1, 1)).end(), (move.substr(1, 1)).begin(), [](unsigned char c) { return tolower(c); });
			row = tolower(move[1]);
			//cout << row << endl;
			return (byte)(8 - stoi(row));
			//return (byte)(stoi(row));
		}
	}

	return (byte)255;
}

byte Program::GetColumn(string move)
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
				return (byte)0;
			}
			else if (col == "b")
			{
				return (byte)1;
			}
			else if (col == "c")
			{
				return (byte)2;
			}
			else if (col == "d")
			{
				return (byte)3;
			}
			else if (col == "e")
			{
				return (byte)4;
			}
			else if (col == "f")
			{
				return (byte)5;
			}
			else if (col == "g")
			{
				return (byte)6;
			}
			else if (col == "h")
			{
				return (byte)7;
			}
			else {
				return (byte)255;
			}
			//}
		}
	}

	return (byte)255;
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

		ChessPieceType PieceType = engine.GetPieceTypeAt((byte)i);
		ChessPieceColor PieceColor = engine.GetPieceColorAt((byte)i);
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

