#pragma once
#include <list>
#include "MapTile.h"
#include "MapUtilities.h"

class River
{
public:
	River(MapUtilities* controller);
	~River();
	std::list<MapTile*> getRiverTiles();
	void generateRiver();
	void correctRiver();
private:
	std::list<MapTile*> m_river;
	MapUtilities* m_mapController;
};

