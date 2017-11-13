#include "PathNode.h"


PathNode::PathNode()
{
	f = 0;
	g = 0;
	h = 0;
	tile = NULL;
	next = NULL;
	previous = NULL;
}

PathNode::PathNode(MapTile * nodeTile)
{
	f = 0;
	g = 0;
	h = 0;
	tile = nodeTile;
	next = NULL;
	previous = NULL;
}

PathNode::PathNode(const PathNode& orig) {
}

PathNode::~PathNode()
{
}

bool PathNode::operator==(const PathNode & rhs) const
{
	//return ((f == rhs.f)&&(g == rhs.g)&&(h == rhs.h)&&(tile == rhs.tile)&&(next == rhs.next)&&(previous == rhs.previous));
	return (*tile == *(rhs.tile));
}
