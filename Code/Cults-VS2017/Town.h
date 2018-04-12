#pragma once

#include "Maptile.h"
#include "MapUtilities.h"
#include <unordered_set>

class Town
{
public:
	Town(MapUtilities * controller, int size);
	~Town();
	void generateTown(MapTile* center, int size);
	MapTile* findTownCenter();
	MapTile* getTownCenter();
	int getTownSize();
private:
	MapTile* m_center;
	std::unordered_set<MapTile*> m_townTiles;
	MapUtilities* m_mapController;
};

