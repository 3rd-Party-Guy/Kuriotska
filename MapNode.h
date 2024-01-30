#pragma once

#include "Entity.h"
#include "MapNodeType.h"

class MapNode : public Entity
{
private:
	bool isDiscovered;
	MapNodeType type;
public:
	bool isFree;

	bool IsDiscovered() const;
	MapNodeType GetType() const;
	MapNode(Vector2<int> position);
	MapNode(Vector2<int>, MapNodeType type);
	~MapNode();
};