#include "Debugger.h"

Debugger::Debugger() {
	int winY = getmaxy(stdscr);
	debugWin = newwin(2, 25, winY - 3, 0);
	wrefresh(debugWin);
}

Debugger& Debugger::instance() {
	static Debugger* instance = new Debugger();
	return *instance;
}

void Debugger::ShowInfo(std::string str) {
	wclear(debugWin);
	mvwaddstr(debugWin, 0, 0, str.c_str());
	wrefresh(debugWin);
}