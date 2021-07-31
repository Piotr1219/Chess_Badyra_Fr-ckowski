#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <cctype>
#include "Engine.h"
#include "functions.h"
//#include "Board.h"
//#include "Book.h"
//#include "Piece.h"

using namespace std;

class Program
{
	void Main(std::string args[]);

private:
	void RunEngine();

	void MakeEngineMove(Engine engine);

public:
	string GetColumnFromInt(int column);

private:
	string GetPgnMove(ChessPieceType pieceType);

	byte GetRow(string move);

	byte GetColumn(string move);

	void DrawBoard(Engine engine);

};
