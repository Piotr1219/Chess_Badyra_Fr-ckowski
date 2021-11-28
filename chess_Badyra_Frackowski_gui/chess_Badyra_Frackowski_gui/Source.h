#pragma once
#include <string>
#include "Program.h"
#include "nsd.h"

using namespace std;


class Source
{
	//static int d;
public:
	static nsd cl;
	static Program engineProgram;
	//static int d;
	static string func();
	static void set(int s);
	static int get();
	static string move(string m);
	static string move_human(string m);
	static string move_engine();
	static string undo();
	static string new_game();
	static string get_board();
	static int set_level(int level);

};