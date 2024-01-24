#pragma once

#include <string>
#include <curses.h>

class Debugger
{
private:
	Debugger();
	WINDOW* debugWin;
public:
	static Debugger& instance();
	void ShowInfo(std::string str);
};