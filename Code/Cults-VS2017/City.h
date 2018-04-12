#pragma once
#include <list>
#include <unordered_set>
#include <vector>
#include "MapTile.h"
#include "MapUtilities.h"

class City
{
public:
	City();
	City(std::vector< std::vector<MapTile*> > * gameMap, MapUtilities* controller);
	~City();
	void generateCityAxis();
	void generateCity();
	void fillCity(MapTile * startPosition);
	void generateCityBoundaries();
	std::list<MapTile*> recursivePathSolution(MapTile * start, MapTile * end, int threshold, int moveRange, int quadrant);
	int getCityTileCount();
	void generateRoads(int numPoints);
private:
	std::vector< std::vector<MapTile*> > * m_map;
	std::list<MapTile*> m_boundary;
	std::unordered_set<MapTile*> m_cityTiles;
	MapTile* m_cityCenter;
	MapTile* m_northVertex;
	MapTile* m_eastVertex;
	MapTile* m_southVertex;
	MapTile* m_westVertex;
	int m_pathThreshold = 5;
	int m_moveRange = 3;
	MapUtilities* m_mapController;
	int m_numberOfVoroniPoints = 7;
};

