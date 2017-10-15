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
#include <list>
#include <string>
#include <cmath>
#include <ctime>
#include <random>
#include <set>
#include <algorithm>

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
	std::set<MapTile*> neighbours;
	for (int i = 0; i < tempNeigh.size(); ++i) {
		if (tempNeigh.at(i)->getType().compare("city") != 0 || tempNeigh.at(i)->getType().compare("town") != 0) {
			neighbours.insert(tempNeigh.at(i));
		}
	}
	//std::set<MapTile*> neighbours(tempNeigh.begin(), tempNeigh.end());
	while (townTileCount <= size) {
		for (int i = 0; i < townTiles.size(); ++i) {
			std::vector<MapTile*> newNeighbours = getNeighbouringTiles(townTiles.at(i));
			for (int j = 0; j < newNeighbours.size(); ++j) {
				if (tempNeigh.at(i)->getType().compare("city") != 0 || tempNeigh.at(i)->getType().compare("town") != 0) {
					neighbours.insert(newNeighbours.at(i));
				}
			}
		}

		std::set<MapTile*>::iterator it = neighbours.begin();
		std::advance(it, getRandomNumber(0, neighbours.size() - 1));
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


}

void GameMap::selectTownCenters() {

}

MapTile* GameMap::getNextTownCenter() {
	//set boundary and town/city tiles to -1, set unexplored tiles to INT_MIN
	int** weights = new int*[m_size];
	for (int i = 0; i < m_size; ++i) {
		weights[i] = new int[m_size];
		if (i == 0 || (i + 1) == m_size) {
			std::fill(weights[i], weights[i] + sizeof(weights[i]), -1);
		} else {
			std::fill(weights[i], weights[i] + sizeof(weights[i]), INT_MIN);
			weights[i][0] = -1;
			weights[i][(m_size - 1)] = -1;
		}
	}

	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			if (m_gameMap[i][j]->getType().compare("town") == 0 || m_gameMap[i][j]->getType().compare("city") == 0) {
				weights[i][j] = -1;
			}
		}
	}

	//keep list of all explored and unexplored tiles, finish when all tiles explored
	//add all unusable (boundary/city/town) tiles to explored, the rest to unexplored
	//add first tile to unvisited, use two while loops to maintain search of current reachable tiles and all tiles
	//find neighbours, add to unvisited if not in visited, check to see if adj tile has the minimum weight of all neighbours
	//update current tile weight to be min adj weight plus one
	//add tile to visited/explored, and remove from unexplored, already removed from visited at start of loop
	//if we have visited all adjacent tiles, but there are still unexplored tiles we grab the next one add to unvisited and start again
	std::vector<MapTile*> visited, explored;
	std::list<MapTile*> unvisited, unexplored;
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			if (weights[i][j] == -1) {
				explored.push_back(m_gameMap[i][j]);
			} else {
				unexplored.push_back(m_gameMap[i][j]);
			}
		}
	}
	
	MapTile* current = m_gameMap[0][0];
	unvisited.push_back(current);
	while (!unexplored.empty()) {
		while (!unvisited.empty()) {
			current = unvisited.front();
			unvisited.pop_front();
			
			int minAdjWeight = INT_MAX;
			int newWeight = -1;
			std::vector<MapTile*> neigh = getNeighbouringTiles(current);
			for (int i = 0; i < neigh.size(); ++i) {
				MapTile* tempTile = neigh.at(i);
				if (std::find(visited.begin(), visited.end(), tempTile) == visited.end()) {
					if (weights[current->getX()][current->getY()] < minAdjWeight) {
						minAdjWeight = weights[current->getX()][current->getY()];
					}
					unvisited.push_back(tempTile);
				}
			}

			if (minAdjWeight != INT_MAX) {
				newWeight = minAdjWeight + 1;
			} else {
				std::cerr << "error getting next town - could not find adjacent unvisited tile";
			}

			weights[current->getX()][current->getY()] = newWeight;

			visited.push_back(current);
			explored.push_back(current);
			unexplored.remove(current);
		}
		//scan from new spot
		MapTile* newSpot = unexplored.front();
		unvisited.push_back(newSpot);
	}

	//MapTile* current = m_gameMap[1][1];
	//if (weights[1][1] == INT_MIN) {
	//	start = current;
	//}
	//else {
	//	//get first unweighted tile
	//	std::list<MapTile*> queue = { current };
	//	while (start == NULL && !queue.empty()) {
	//		std::vector<MapTile*> neigh = getNeighbouringTiles(current);
	//		for (int i = 0; i < neigh.size(); ++i) {
	//			MapTile* tempTile = neigh.at(i);
	//			if (std::find(visited.begin(), visited.end(), tempTile) == visited.end()) {
	//				if (std::find(queue.begin(), queue.end(), tempTile) == queue.end()) {
	//					queue.push_back(tempTile);
	//				}
	//			}
	//		}
	//		current = queue.front();
	//		queue.pop_front();
	//		if (weights[current->getX()][current->getY()] == INT_MIN) {
	//			start == current;
	//		}
	//	}
	//}
	//if (start == NULL) {
	//	std::cerr << "error getting next town - could not find position to start assigning weights" << std::endl;
	//}
	//else {
	//	unvisited.push_back(start);
	//	while (!unvisited.empty()) {
	//		MapTile* nextTile = unvisited.front();
	//		unvisited.pop_front();
	//		int minAdjWeight = INT_MAX;
	//		std::vector<MapTile*> neigh = getNeighbouringTiles(current);
	//		for (int i = 0; i < neigh.size(); ++i) {
	//			MapTile* tempTile = neigh.at(i);
	//			if (std::find(visited.begin(), visited.end(), tempTile) == visited.end()) {
	//				if (std::find(unvisited.begin(), unvisited.end(), tempTile) == unvisited.end()) {
	//					unvisited.push_back(tempTile);
	//				}
	//			} else {
	//				if (weights[tempTile->getX()][tempTile->getY()] < minAdjWeight) {
	//					minAdjWeight = weights[tempTile->getX()][tempTile->getY()];
	//				}
	//			}
	//		}
	//	}
	//}


}

double GameMap::getTileDistanceRank(int x, int y, int** arr) {
	//if (arr[x][y] == -1) return -1;
	//double distRank = 0;
	//double distModifier = 0;
	////if tier 1 contains city/town/boundary -> position invalid
	////if tier 2 contains city/town/boundary -> at best boundary of town
	//std::set<MapTile*> tier1, tier2, tier3;
	//std::vector<MapTile*> neighbours = getNeighbouringTiles(m_gameMap[x][y]);
	//for (int i = 0; i < m_size; ++i) {
	//	for (int j = 0; j < m_size; ++j) {
	//	}
	//}
	return 0.0;

}

std::vector<MapTile*> GameMap::getNeighbouringTiles(MapTile* tile) {
	std::vector<MapTile*> neighbours;
	//right, bottom right, bottom, bottom left, left, left top, top, top right
	int nOffset[8][2] = { { 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 },{ -1,0 },{ -1, -1 },{ 0, -1 },{ 1, -1 } };
	int tX = tile->getX();
	int tY = tile->getY();
	for (int i = 0; i < 8; ++i) {
		if (((tX + nOffset[i][0]) >= 0) && ((tX + nOffset[i][0]) < m_size) && ((tY + nOffset[i][1]) >= 0) && ((tY + nOffset[i][1]) < m_size)) {
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
