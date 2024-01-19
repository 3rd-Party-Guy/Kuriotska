#include <iostream>

#include "MapNode.h"
#include "PerlinNoise.h"
#include "Misc.h"


MapNodeType NodeTypeValLookup(int val) {
	if (val <= 25) return MapNodeType::Water;
	if (val <= 75) return MapNodeType::Grass;
	return MapNodeType::Stone;
}

bool MapNode::IsDiscovered() const { return isDiscovered; }

MapNodeType MapNode::GetType() const { return type; }

MapNode::MapNode() : isDiscovered(false), type(MapNodeType::Water) { }

MapNode::MapNode(int x, int y) : isDiscovered(false) {
	PerlinNoise pn(9);
	int coordVal = MapDoubleToInt(pn.GetCoordValue2D(x, y) * 10, 0.0, 1.0, 0, 100);
	type = NodeTypeValLookup(coordVal);
}

MapNode::MapNode(MapNodeType type) : isDiscovered(false), type(type) { }

MapNode::~MapNode() { }