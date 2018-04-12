#pragma once
#include "MapTile.h"

class PathNode
{
public:
	PathNode();
	PathNode(const PathNode& orig);
	PathNode(MapTile* nodeTile);
	~PathNode();
	bool operator==(const PathNode& rhs) const;
	double f;
	double g;
	double h;
	MapTile* tile;
	PathNode* next;
	PathNode* previous;

private:
	
};
