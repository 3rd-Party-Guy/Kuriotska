#pragma once
#include "Entity.h"

class Command
{
public:
	virtual void execute(Entity* entity) = 0;
};

class MoveCommand : public Command
{
private:
	int x, y;
	bool isAbsolute;
public:
	MoveCommand(int x, int y, bool isAbsolute);
	virtual void execute(Entity* entity);
};

class ExitCommand : public Command
{
public:
	virtual void execute(Entity* entity);
};