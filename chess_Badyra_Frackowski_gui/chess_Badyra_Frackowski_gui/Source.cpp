#include <string>
#include "Source.h"
#include "MyForm.h"

using namespace std;


string Source::func()
{
	printf("func exec");
	return "fen_string";
}

void Source::set(int s) {
	int p = s;
	cl.a = s;
}

int Source::get() {
	return cl.a;
}

string Source::move(string m) {
	string fen = engineProgram.HumanMove(m);
	return fen;
}
string Source::move_human(string m) {
	string fen = engineProgram.HumanMove1(m);
	return fen;
}
string Source::move_engine() {
	string fen = engineProgram.EngineMove1();
	return fen;
}

string Source::undo() {
	return engineProgram.undo();
}
string Source::new_game() {
	return engineProgram.new_game();
}
string Source::get_board() {
	return engineProgram.get_board();
}
int Source::set_level(int level) {
	return engineProgram.set_level(level);
}

//int Source::d = 0;
nsd Source::cl = nsd();
Program Source::engineProgram = Program();





