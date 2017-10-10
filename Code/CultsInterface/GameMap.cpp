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
#include <random>

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
			} else {
				std::cout << " , ";
			}
		}
		std::cout << std::endl;
	}
}

MapTile* GameMap::getMiddle() {
	MapTile* mid = m_gameMap[m_size/2][m_size/2];
	return mid;
}

void GameMap::generateCityCenter() {	
	//set center tile to city
	MapTile* midPoint = this->getMiddle();
	midPoint->setType("city");
	midPoint->setRoad(true);
	//generate average city "radius" ie length from center to edge
	int cityRadius = m_size/4;
	
	//iterate in 4 directions, ie north/south/east/west
	for (int i = 0; i < 4; ++i) {
		//generate random length to change radius by with 50/50 odds of shrinking or growing
		int radiusChange = std::rand() % (m_size/8);
		if ((std::rand() % 2) == 0) {
			radiusChange = 0 - radiusChange;
		}
		
		//flip tiles to city for length of radius + random change to radius
		for (int j = 0; j < (cityRadius + radiusChange); ++j) {
			MapTile* tempTile;
			bool atVertex = false;
			if ((j + 1) == (cityRadius + radiusChange)) {
				atVertex = true;
			}
			switch(i)
			{
				case 0:
					//north ie y decreasing
					tempTile = m_gameMap[midPoint->getX()][midPoint->getY()-j];
					if (atVertex) {
						
					}
					break;
				case 1:
					//south ie y increasing
					tempTile = m_gameMap[midPoint->getX()][midPoint->getY()+j];
					if (atVertex) {
						
					}
					break;
				case 2:
					//east ie x increasing
					tempTile = m_gameMap[midPoint->getX()+j][midPoint->getY()];
					if (atVertex) {
						
					}
					break;
				case 3:
					//west ie x decreasing
					tempTile = m_gameMap[midPoint->getX()-j][midPoint->getY()];
					if (atVertex) {
						
					}
					break;
				default:
					//nope
					std::cout << "error	- city axis generation" << std::endl;
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
	while (townTileCount <= size) {
		
		townTileCount++;
	}
}

void GameMap::generateAllTowns() {
	//int townSize = m_townMinSize + (std::rand() % (m_townMaxSize - m_townMinSize));
	std::random_device rd; //obtain rand num from hw
	std::mt19937 eng(rd()); //seed generator
	std::uniform_distribution<> distr(m_townMaxSize, m_townMinSize); //define range
	int townSize = distr(eng); //set this towns size, random number between min and max
	
}

std::vector<MapTile*> GameMap::getNeighbouringTiles(MapTile* tile) {
	std::vector<MapTile*> neighbours;
	//need to check if tile is on top or bottom boundary
	bool verticalBoundary = (tile->getY() == 0 || tile->getY() == (m_size - 1));
	//need to check if tile is on left or right boundary
	bool horizontalBoundary = (tile->getX() == 0 || tile->getX() == (m_size - 1));
	if (verticalBoundary && horivontalBoundary) {
		//corner
		
	} else if (verticalBoundary) {
		//at top or bottom
		
	} else if (horizontalBoundary) {
		//at right or left
		
	} else {
		//not on edge
		neighbours.add(m_gameMap[tile->getX()+1][tile->getY()]);
		neighbours.add(m_gameMap[tile->getX()-1][tile->getY()]);
		neighbours.add(m_gameMap[tile->getX()][tile->getY()+1]);
		neighbours.add(m_gameMap[tile->getX()][tile->getY()-1]);
		neighbours.add(m_gameMap[tile->getX()+1][tile->getY()+1]);
		neighbours.add(m_gameMap[tile->getX()-1][tile->getY()-1]);
		neighbours.add(m_gameMap[tile->getX()+1][tile->getY()-1]);
		neighbours.add(m_gameMap[tile->getX()-1][tile->getY()+1]);
	}
	return neighbours;
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

int main(int ac, char** av) {
	std::srand(time(0));
	GameMap testMap = GameMap(25);
	testMap.generateCity();
	testMap.printOnly("rural");
	
	return 0;
}
