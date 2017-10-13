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

#include "GameMap.h"
#include "MapTile.h"
#include "TileType.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <random>
#include <set>

GameMap::GameMap() {
	initializeGameMap(m_defaultSize);
}

GameMap::GameMap(int size) {
	
	initializeGameMap(size);
}

void GameMap::initializeGameMap(int size) {
	m_size = size;
	
	for (int i=0; i < size; ++i) {
		std::vector<MapTile*> tileRow;
		for (int j=0; j < size; ++j) {
			MapTile* tempTile = new MapTile("blank", false, j, i);
			tileRow.push_back(tempTile);
		}
		m_gameMap.push_back(tileRow);
	}
	
	m_totalTiles = size*size;
	m_cityTileMax = 0.4 * size;
	m_cityTileCount = 0;
	m_townTileMax = 0.2 * size;
	m_townTileCount = 0;
	m_totalTownCount = 0;
	m_ruralTileCount = 0;
	
	//floor
	m_minTowns = floor(m_townTileMax / m_townMinSize);
	m_maxTowns = floor(m_townTileMax / m_townMaxSize);
}

GameMap::GameMap(const GameMap& orig) {

}

GameMap::~GameMap() {

}

void GameMap::printMap() {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			MapTile* tempTile = m_gameMap[i][j];
			tempTile->printTile();
			std::cout << ", ";
		}
		std::cout << std::endl;
	}
}

void GameMap::printOnly(std::string type) {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
MapTile* tempTile = m_gameMap[i][j];
//if (tempTile->getTileType() == i) {
if (tempTile->getType().compare(type) == 0) {
	tempTile->printTile();
	std::cout << ", ";
}
else {
	std::cout << " , ";
}
		}
		std::cout << std::endl;
	}
}

MapTile* GameMap::getMiddle() {
	MapTile* mid = m_gameMap[m_size / 2][m_size / 2];
	return mid;
}

void GameMap::generateCityCenter() {
	//set center tile to city
	MapTile* midPoint = this->getMiddle();
	midPoint->setType("city");
	midPoint->setRoad(true);
	//generate average city "radius" ie length from center to edge
	int cityRadius = m_size / 4;
	//iterate in 4 directions, ie north/south/east/west
	for (int i = 0; i < 4; ++i) {
		//generate random length to change radius by with 50/50 odds of shrinking or growing
		int radiusChange = getRandomNumber(0, (m_size / 8));
		if (getRandomNumber(0, 1) == 0) {
			radiusChange = 0 - radiusChange;
		}
		//flip tiles to city for length of radius + random change to radius
		for (int j = 0; j < (cityRadius + radiusChange); ++j) {
			MapTile* tempTile;
			bool atVertex = false;
			if ((j + 1) == (cityRadius + radiusChange)) {
				atVertex = true;
			}
			switch (i)
			{
			case 0:
				//north ie y decreasing
				tempTile = m_gameMap[midPoint->getX()][midPoint->getY() - j];
				if (atVertex) {
					m_cityNorthVertex = tempTile;
				}
				break;
			case 1:
				//south ie y increasing
				tempTile = m_gameMap[midPoint->getX()][midPoint->getY() + j];
				if (atVertex) {
					m_citySouthVertex = tempTile;
				}
				break;
			case 2:
				//east ie x increasing
				tempTile = m_gameMap[midPoint->getX() + j][midPoint->getY()];
				if (atVertex) {
					m_cityEastVertex = tempTile;
				}
				break;
			case 3:
				//west ie x decreasing
				tempTile = m_gameMap[midPoint->getX() - j][midPoint->getY()];
				if (atVertex) {
					m_cityWestVertex = tempTile;
				}
				break;
			default:
				//nope
				std::cerr << "error	- city axis generation" << std::endl;
				break;
			}

			tempTile->setType("city");
		}
	}

}

void GameMap::generateCity() {
	generateCityCenter();
	setRuralArea();
}

void GameMap::reduceCity() {

}

void GameMap::generateTown(MapTile* center, int size) {
	center->setType("town");
	m_townTileCount++; //increment town tiles used
	int townTileCount = 1; //track this towns tiles
	std::vector<MapTile*> tempNeigh = getNeighbouringTiles(center);
	std::vector<MapTile*> townTiles = { center };
	std::set<MapTile*> neighbours(tempNeigh.begin(), tempNeigh.end());
	while (townTileCount <= size) {
		for (int i = 0; i < townTiles.size(); ++i) {
			std::vector<MapTile*> newNeighbours = getNeighbouringTiles(townTiles.at(i));
			for (int j = 0; j < newNeighbours.size(); ++j) {
				neighbours.insert(newNeighbours.at(i));
			}
		}

		std::set<MapTile*>::iterator it = neighbours.begin();
		std::advance(it, getRandomNumber(0, neighbours.size()-1));
		MapTile* townExpansion = *it;
		neighbours.erase(it);
		townExpansion->setType("town");
		townExpansion->setTileType(TileType::Town);
		townTiles.push_back(townExpansion);

		townTileCount++;
	}
}

void GameMap::generateAllTowns() {
	int townSize = getRandomNumber(m_townMinSize, m_townMaxSize); //set this towns size, random number between min and max

	//create 2d array of integers to represent game map
	//set city, town & map boundary tiles to -1
	//for each other tile, count distance left/right/up/down until -1, add all distances and divide by four
	//find max numbers, place a town, reevaluate weights and repeat
}

std::vector<MapTile*> GameMap::getNeighbouringTiles(MapTile* tile) {
	std::vector<MapTile*> neighbours;
	int nOffset[8][2] = { { -1,0 },{ -1, -1 },{ 0, -1 },{ 1, -1 },{ 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 } };
	int tX = tile->getX();
	int tY = tile->getY();
	for (int i = 0; i < 8; ++i) {
		if (((tX + nOffset[i][0]) > 0) && ((tX + nOffset[i][0]) < m_size) && ((tY + nOffset[i][1]) > 0) && ((tY + nOffset[i][1]) < m_size)) {
			neighbours.push_back(m_gameMap[(tX + nOffset[i][0])][(tY + nOffset[i][1])]);
		}
	}
	return neighbours;
}

int GameMap::getRandomNumber(int min, int max) {
	std::random_device rd; //obtain rand num from hw
	std::mt19937 eng(rd()); //seed generator
	std::uniform_int_distribution<> distr(min, max); //define range
	return distr(eng);
}

void GameMap::findPath(MapTile* start, MapTile* end) {
	
}

void GameMap::countTilesFor(std::string type) {
	
}

void GameMap::selectTownCenters() {
	
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

/*
int main(int ac, char** av) {
	std::srand(time(0));
	GameMap testMap = GameMap(25);
	testMap.generateCity();
	testMap.printOnly("rural");
	
	return 0;
}*/
