#include <stdlib.h>

#include "Command.h"
#include "Entity.h"

MoveCommand::MoveCommand(int x, int y, bool isAbsolute) : x(x), y(y), isAbsolute(isAbsolute) { }
void MoveCommand::execute(Entity* entity) {
	if (entity == nullptr) return;
	isAbsolute ? entity->SetPositionAbs(x, y) : entity->SetPositionRel(x, y);
}

void ExitCommand::execute(Entity* entity) {
	exit(0);
}