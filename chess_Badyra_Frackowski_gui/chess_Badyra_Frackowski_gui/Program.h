#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cctype>
#pragma once
#include "Engine.h"
#include "functions.h"
//#include "Board.h"
//#include "Book.h"
//#include "Piece.h"

using namespace std;


class Program
{
	void Main(std::string args[]);
	Engine engine;

public:
	void RunEngine();
	string HumanMove(string m);
	string HumanMove1(string m);
	string EngineMove1();
	string new_game();
	string undo();
	string get_board();
	int set_level(int level);
private:
	void MakeEngineMove(Engine &engine);

public:
	string GetColumnFromInt(int column);

private:
	string GetPgnMove(ChessPieceType pieceType);

	char GetRow(string move);

	char GetColumn(string move);

	void DrawBoard(Engine engine);

};
