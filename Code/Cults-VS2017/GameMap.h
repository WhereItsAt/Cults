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
	void fillCity(std::list<MapTile*> boundary, MapTile * startPosition);
	void generateCityBoundaries();
	std::vector<MapTile*> selectCityBoundaryPoints(MapTile * start, MapTile * end);
	std::list<MapTile*> recursivePathSolution(MapTile * start, MapTile * end, int threshold, int moveRange, int quadrant);
	MapTile * getMidPoint(MapTile * start, MapTile * end);
	std::vector<MapTile*> voroniDiagramSolution(MapTile * start, MapTile * end);
	void generateRivers(int numberOfRivers, int minDistance);
	std::list<MapTile*> generateBezierCurve(MapTile * start, MapTile * end, bool quadratic);
	int getRandomNumberInRangePositiveOrNegative(int num1, int num2, float chanceToFlip);
	std::list<MapTile*> quadraticBezier(MapTile * p1, MapTile * p2, MapTile * p3);
	std::list<MapTile*> cubicBezier(MapTile * p1, MapTile * p2, MapTile * p3, MapTile * p4);
	//std::vector<MapTile*> getRiverPoints(int minDistance);
	MapTile * getRandomBoundaryTile(int edge, int minDistance);
	MapTile * getRandomTileInRange(MapTile * tile, int range);
	int getStartingPointShiftValue(int startEdge, int endEdge, MapTile * start, int minDistance);
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
	std::vector<MapTile*> getNonDiagonallyAdjacentNeighbours(MapTile * tile);
	void initialiseWeights();
	void calculateWeights();
	int getRandomNumber(int min, int max);

private:
	int m_size;
	const int m_defaultSize = 50;
	int m_townMinSize;
	int m_townMaxSize;
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
	int m_pathThreshold = 5;
	int m_moveRange = 3;

};

#endif /* GAMEMAP_H */
