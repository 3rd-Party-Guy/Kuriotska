#pragma once

#include <map>
#include <utility>

#include "MapNode.h"

class Map {
private:
	std::map<std::pair<int, int>, MapNode> map;
	void GenerateMap();
public:
	const int sizeX, sizeY;
	const MapNode* GetNode(int x, int y) const;
	
	const MapNode* GetNode(Vector2<int> pos) const;
	const MapNode* GetRandomNode() const;
	
	const bool GetNodeIsFree(int x, int y) const;
	const bool GetNodeIsFree(Vector2<int> pos) const;
	
	const void SetNodeIsFree(int x, int y, bool isFree);
	const void SetNodeIsFree(Vector2<int> pos, bool isFree);
	

	Map();
	Map(int sizeX, int sizeY);
};