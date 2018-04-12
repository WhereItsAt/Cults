#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include "MapTile.h"

class GameMap;

class MapUtilities
{
public:
	MapUtilities(GameMap* map);
	~MapUtilities();
	std::string getDateTimeNow();
	int getRandomNumber(int min, int max);
	int getRandomNumberInRangePositiveOrNegative(int num1, int num2, float chanceToFlip);
	void printMap();
	void printOnly(std::string type);
	void PrintToFile(std::string output);
	void visualiseMapAsPpm();
	void visualiseMapWithPathAsPpm(MapTile * start, MapTile * end, std::list<MapTile*> path);
	void printPath(std::list<MapTile*> path);
	MapTile * getTileAt(int x, int y);
	std::vector<std::string> split(std::string s, char c);
	std::string convertMonth(std::string month);
	std::list<MapTile*> generateBezierCurve(MapTile * start, MapTile * end, bool quadratic);
	std::list<MapTile*> quadraticBezier(MapTile * p1, MapTile * p2, MapTile * p3);
	std::list<MapTile*> cubicBezier(MapTile * p1, MapTile * p2, MapTile * p3, MapTile * p4);
	MapTile * findEmptySpot();
	int distanceFromLine(MapTile * p1, MapTile * p2, MapTile * point);
	int findSide(MapTile * p1, MapTile * p2, MapTile * point);
	std::vector<MapTile*> getPartitionBoundary(std::vector<MapTile*> partition);
	MapTile* getMiddle();
	MapTile * getMidPoint(MapTile * start, MapTile * end);
	MapTile * getRandomBoundaryTile(int edge, int minDistance);
	MapTile * getRandomTileInRange(MapTile * tile, int range);
	std::vector<MapTile*> getNeighbouringTiles(MapTile* tile, bool startOnTileBelow = true);
	std::vector<MapTile*> getNonDiagonallyAdjacentNeighbours(MapTile * tile);
	std::unordered_set<MapTile*> getTilesWithWeight(int weight, bool findMax);
	std::unordered_set<MapTile*> getTilesWithWeight(int weight, bool findMax, std::unordered_set<MapTile*> tiles);
	int getManhattanDistance(MapTile * a, MapTile * b);
	int getMaxWeight();
	std::list<MapTile*> aStar(MapTile * start, MapTile * end);
	double getEuclideanDistance(MapTile * a, MapTile * b);
	int getDiagonalDistance(MapTile * a, MapTile * b);
	void initialiseWeights();
	void calculateWeights();
	int getStartingPointShiftValue(int startEdge, int endEdge, MapTile * start, int minDistance);
	int getMapSize();
	std::string datePretty();
	GameMap* getMapReference();
	bool tilesAreAdjacent(MapTile* a, MapTile* b);
private:
	GameMap* m_map;
	int m_borderWeightBump = 3;
	std::vector<MapTile*> m_hull;
	void quickHull(std::vector<MapTile*> partition, MapTile * a, MapTile * b, int side);
};

