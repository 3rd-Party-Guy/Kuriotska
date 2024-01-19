#pragma once

enum class MapNodeType {
	Grass,
	Stone,
	Water,
};

class MapNode
{
private:
	bool isDiscovered;
	MapNodeType type;
public:
	bool IsDiscovered() const;
	MapNodeType GetType() const;
	MapNode();
	MapNode(int x, int y);
	MapNode(MapNodeType type);
	~MapNode();
};

