#include <iostream>

#include "MapNode.h"
#include "PerlinNoise.h"
#include "Misc.h"

MapNodeType NodeTypeValLookup(int val) {
	if (val <= 25) return MapNodeType::Water;
	if (val <= 50) return MapNodeType::Sand;
	return MapNodeType::Grass;
}

bool MapNode::IsDiscovered() const { return isDiscovered; }

MapNodeType MapNode::GetType() const { return type; }

MapNode::MapNode(Vector2<int> position) : Entity(position), isDiscovered(false), type(MapNodeType::Water), isFree(true) {

	int coordVal = Misc::MapDoubleToInt(PerlinNoise::GetCoordValue2D(position.GetX(), position.GetY()) * 10, 0.0, 1.0, 0, 100);
	type = NodeTypeValLookup(coordVal);
}

MapNode::MapNode(Vector2<int> position, MapNodeType type) : Entity(position), isDiscovered(false), type(type), isFree(true) { }
MapNode::~MapNode() { }