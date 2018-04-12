#pragma once
#include "MapTile.h"
#include "MapUtilities.h"
#include <unordered_set>

class Mountain
{
public:
	Mountain(MapUtilities * controller);
	~Mountain();
	void generateMountain(MapTile* center);
private:
	MapTile* m_center;
	std::unordered_set<MapTile*> m_tiles;
	MapUtilities* m_mapController;
	const int m_maxSize = 13;
	const int m_minSize = 6;
	const int m_radius = 2;
};

