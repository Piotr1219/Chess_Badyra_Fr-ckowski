#include <string>
#include <iostream>
#include "Program.h"

using namespace std;

int mainf() {
	Program engineProgram;
	//engineProgram.RunEngine();
	string s;
	string fen;
	cout << "podaj ruch" << endl;
	cin >> s;
	//fen = engineProgram.HumanMove(s);
	cout << "fen wynikowy" << fen << endl;

	cout << "podaj ruch" << endl;
	cin >> s;
	//fen = engineProgram.HumanMove(s);
	cout << "fen wynikowy" << fen << endl;

	cout << "podaj ruch" << endl;
	cin >> s;
	//fen = engineProgram.HumanMove(s);
	cout << "fen wynikowy" << fen << endl;

	return 0;
}