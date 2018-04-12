/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   GameMap.cpp
* Author: scott
*
* Created on 4 June 2017, 12:37 AM
*/
#pragma warning(disable : 4996)

#include "GameMap.h"
#include "MapTile.h"
#include "TileType.h"
#include "PathNode.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <chrono>
#include <ctime>
#include <random>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>


GameMap::GameMap() {
	initializeGameMap(m_defaultSize);
}

GameMap::GameMap(int size) {

	initializeGameMap(size);
}

GameMap::GameMap(const GameMap& orig) {

}

GameMap::~GameMap() {

}

//%&map functions
void GameMap::generateMap() {
	std::cout << "	-generating city now *build* *build* *build*" << std::endl;
	std::vector< std::vector<MapTile*> >* mapPtr = & m_gameMap;
	m_city = new City(mapPtr, m_mapController);
	std::cout << "	-finished generating city *hoorah*" << std::endl;

	std::cout << "	-generating country now *farm* *farm* *farm*" << std::endl;
	setRuralArea();
	std::cout << "	-finished generating country now *hoorah*" << std::endl;

	std::cout << "	-generating towns now *build* *build* *build*" << std::endl;
	generateAllTowns();
	std::cout << "	-finished generating towns *hoorah*" << std::endl;

	std::cout << "	-generating rivers now *woosh* *woosh* *woosh*" << std::endl;
	generateRivers(m_mapController->getRandomNumber(1, 3), (m_size / 1.25));
	std::cout << "	-finished generating rivers *hoorah*" << std::endl;

	std::cout << "	-generating mountains now *raise* *raise* *raise*" << std::endl;
	int numberOfMountains = m_mapController->getRandomNumber(1, 3);
	generateMountains(numberOfMountains);
	std::cout << "	-finished generating mountains now *raise* *raise* *raise*" << std::endl;
}

void GameMap::setRuralArea() {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			MapTile* tempTile = m_gameMap[i][j];
			//if (tempTile->getTileType() == 0)
			if ((tempTile->getType().compare("city") != 0) && (tempTile->getType().compare("town") != 0)) {
				tempTile->setType("rural");
			}
		}
	}
}

void GameMap::initializeGameMap(int size) {
	m_size = size;

	for (int i = 0; i < size; ++i) {
		std::vector<MapTile*> tileRow;
		m_gameMap.push_back(tileRow);
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			MapTile* tempTile = new MapTile("blank", false, i, j);
			tempTile->setRiver(false);
			m_gameMap[i].push_back(tempTile);
		}
	}

	m_totalTiles = size*size;
	m_cityTileMax = 0.4 * m_totalTiles;
	m_townTileMax = 0.2 * m_totalTiles;
	m_ruralTileCount = 0;
	m_townMinSize = m_size * 0.5;
	m_townMaxSize = m_size * 1.5;
	//m_maxTowns = (m_townTileMax / 2) / m_townMinSize;
	//m_minTowns = (m_townTileMax / 2) / m_townMaxSize;
	m_maxTowns = 14;
	m_minTowns = 7;
	m_mapController = new MapUtilities(this);
}

int GameMap::getSize()
{
	return m_size;
}

std::vector<std::vector<MapTile*>>* GameMap::getMap()
{
	std::vector<std::vector<MapTile*>>* mapPtr = & m_gameMap;
	return mapPtr;
}

MapUtilities* GameMap::getController() {
	return m_mapController;
}


//%&town functions
void GameMap::generateAllTowns() {
	int totalTowns = m_mapController->getRandomNumber(m_minTowns, m_maxTowns);
	for (int i = 0; i < totalTowns; ++i) {
		int townSize = m_mapController->getRandomNumber(m_townMinSize, m_townMaxSize); 
		//set this towns size, random number between min and max
		//if all town tiles are used, create minimum sized town and finish
		int totalTownTiles = 0;
		for (int j = 0; j < m_towns.size(); ++j) {
			totalTownTiles += m_towns[j]->getTownSize();
		}
		if ((townSize + totalTownTiles) > m_townTileMax) {
			townSize = m_townTileMax - totalTownTiles;
			if (townSize >= m_townMinSize) {
				//MapTile* next = getNextTownCenter();
				//generateTown(next, townSize);
				Town* nextTown = new Town(m_mapController, townSize);
				m_towns.push_back(nextTown);
			}
			return;
		}
		//MapTile* next = getNextTownCenter();
		//generateTown(next, townSize);
		Town* nextTown = new Town(m_mapController, townSize);
		m_towns.push_back(nextTown);
	}
}

//%&feature functions
std::vector<MapTile*> GameMap::voroniDiagramSolution(MapTile* start, MapTile* end) {
	//voroni diagram - generate random points and allocate areas to them
	//ie for every point, continue to add neighbouring tiles in concentric circles, it will stop and form boundaries at the half way point between two points 
	//follow boundaries of partitions always taking shortest path to end...?
	std::vector<MapTile*> thing = { start, end };
	return thing;
}

void GameMap::generateRivers(int numberOfRivers, int minDistance) {
	//split dist in two partitions, 60/40 or 70/30 split, create one quadratic bezier curve on the smaller partition and one cubic one on the larger one
	for (int i = 0; i < numberOfRivers; ++i) {
		River* tempRiver = new River(m_mapController);
		m_rivers.push_back(tempRiver);
	}
}

void GameMap::generateMountains(int numberOfMountains) {
	for (int i = 0; i < numberOfMountains; ++i) {
		Mountain* mountain = new Mountain(m_mapController);
		m_mountains.push_back(mountain);
	}
}

//%&main

int main(int ac, char** av) {
std::srand(time(0));

std::cout << "creating map now" << std::endl;
GameMap testMap = GameMap(100);
std::cout << "finished creating map" << std::endl;

std::cout << "generating map now" << std::endl;
testMap.generateMap();
std::cout << "finished generating map" << std::endl;
//testMap.printMap();

//testMap.PrintToFile("gameMap_Output.txt");
std::cout << "Writing map to image file" << std::endl;
testMap.getController()->visualiseMapAsPpm();
std::cout << "Finished writing map to image file" << std::endl;

//MapTile* tileA = testMap.getTileAt(20, 18);
//MapTile* tileB = testMap.getTileAt(56, 46);
//std::cout << "generating path now" << std::endl;
//testMap.visualiseMapWithPathAsPpm(tileA, tileB, testMap.bezierCurveSolution(tileA, tileB));
//std::cout << "finished generating path" << std::endl;
/*
std::cout << "getting significant river points" << std::endl;
std::vector<MapTile*> points = testMap.getRiverPoints(45);
for (int i = 0; i < points.size(); ++i) {
	std::cout << points.at(i)->toString() << std::endl;
}
std::cout << "finished getting significant river points" << std::endl;
*/
std::cin.get();

return 0;
}
