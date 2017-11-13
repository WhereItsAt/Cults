/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   GameMap.h
* Author: scott
*
* Created on 4 June 2017, 12:37 AM
*/

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "MapTile.h"
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <list>

class GameMap {
public:
	GameMap();
	GameMap(int size);
	GameMap(const GameMap& orig);
	virtual ~GameMap();
	void printMap();
	MapTile* getMiddle();
	void generateCityCenter();
	void generateMap();
	void printOnly(std::string type);
	void generateCity();
	void reduceCity();
	void generateCityBoundaries();
	void generateTown(MapTile* center, int size);
	std::unordered_set<MapTile*> getTilesWithWeight(int weight, bool findMax);
	std::unordered_set<MapTile*> getTilesWithWeight(int weight, bool findMax, std::unordered_set<MapTile*> tiles);
	int getManhattanDistance(MapTile * a, MapTile * b);
	void generateAllTowns();
	void test();
	std::list<MapTile*> aStar(MapTile * start, MapTile * end);
	double getEuclideanDistance(MapTile * a, MapTile * b);
	int getDiagonalDistance(MapTile * a, MapTile * b);
	void countTilesFor(std::string type);
	MapTile * getNextTownCenter();
	void setRuralArea();
	void PrintToFile(std::string output);
	void visualiseMapAsPpm();
	void visualiseMapWithPathAsPpm(MapTile * start, MapTile * end, std::list<MapTile*> path);
	std::string getDateTimeNow();
	void printPath(std::list<MapTile*> path);
	MapTile * getTileAt(int x, int y);
	void initializeGameMap(int size);
	std::vector<MapTile*> getNeighbouringTiles(MapTile* tile, bool startOnTileBelow = true);
	void initialiseWeights();
	void calculateWeights();
	int getRandomNumber(int min, int max);

private:
	int m_size;
	const int m_defaultSize = 25;
	const int m_townMinSize = 15;
	const int m_townMaxSize = 35;
	std::vector< std::vector<MapTile*> > m_gameMap;
	int m_totalTiles;
	int m_cityTileMax;
	int m_cityTileCount;
	int m_townTileMax;
	int m_townTileCount;
	int m_totalTownCount;
	int m_ruralTileCount;
	int m_maxTowns;
	int m_minTowns;
	MapTile* m_cityCenter;
	MapTile* m_cityNorthVertex;
	MapTile* m_citySouthVertex;
	MapTile* m_cityWestVertex;
	MapTile* m_cityEastVertex;

};

#endif /* GAMEMAP_H */

