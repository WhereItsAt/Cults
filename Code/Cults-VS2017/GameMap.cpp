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
#include <iterator>

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
	m_cityTileMax = floor(0.4 * m_totalTiles);
	m_cityTileCount = 0;
	m_townTileMax = floor(0.2 * m_totalTiles);
	m_townTileCount = 0;
	m_totalTownCount = 0;
	m_ruralTileCount = 0;
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

void GameMap::generateMap() {
	generateCity();
	setRuralArea();
	generateAllTowns();
}

void GameMap::generateCity() {
	generateCityCenter();
	//fillCity()
	//reduceCity()
}

void GameMap::reduceCity() {

}

void GameMap::generateTown(MapTile* center, int size) {
	center->setType("town");
	m_townTileCount++; //increment town tiles used
	int townTileCount = 1; //track this towns tiles
	std::vector<MapTile*> townTiles = { center };
	std::set<MapTile*> neighbours;


	//ok need to do a few more things here. 
		//need to remove tiles if all neighbours are town and/or weight = -1
		//need to make tempNeigh a set so no duplicates
		//instead of passing around so many goddamn vectors, i should delete the lowest weighted tiles out of tempNeigh, its a temporary collection anyway who cares about losing elements we have stored elsewhere
		//dont add any tiles in townTiles to tempneigh <-
	while (townTileCount <= size) {
		std::set<MapTile*> tempNeigh;
		for (int i = 0; i < townTiles.size(); ++i) {
			std::vector<MapTile*> newNeigh = getNeighbouringTiles(townTiles.at(i));
			//std::copy(newNeigh.begin(), newNeigh.end(), std::inserter(tempNeigh, tempNeigh.end()));
			for (int j = 0; j < newNeigh.size(); ++j) {
				if ((newNeigh.at(j)->getType().compare("town") != 0) && (newNeigh.at(j)->getType().compare("city") != 0)) {
					tempNeigh.insert(newNeigh.at(j));
				}
			}
		}
		std::vector<MapTile*> bestNeigh = getMaxWeightTiles(tempNeigh);
		int randIndex = getRandomNumber(0, (bestNeigh.size() - 1));
		MapTile* townExpansion = bestNeigh.at(randIndex);
		townExpansion->setType("town");
		townExpansion->setTileType(TileType::Town);
		townTiles.push_back(townExpansion);
		m_townTileCount++;
		townTileCount++;
	}

	//for (int i = 0; i < tempNeigh.size(); ++i) {
	//	if (tempNeigh.at(i)->getType().compare("city") != 0 || tempNeigh.at(i)->getType().compare("town") != 0) {
	//		neighbours.insert(tempNeigh.at(i));
	//	}
	//}
	////std::set<MapTile*> neighbours(tempNeigh.begin(), tempNeigh.end());
	//while (townTileCount <= size) {
	//	for (int i = 0; i < townTiles.size(); ++i) {
	//		std::vector<MapTile*> newNeighbours = getNeighbouringTiles(townTiles.at(i));
	//		for (int j = 0; j < newNeighbours.size(); ++j) {
	//			if (tempNeigh.at(i)->getType().compare("city") != 0 || tempNeigh.at(i)->getType().compare("town") != 0) {
	//				neighbours.insert(newNeighbours.at(i));
	//			}
	//		}
	//	}
	//	std::set<MapTile*>::iterator it = neighbours.begin();
	//	std::advance(it, getRandomNumber(0, neighbours.size() - 1));
	//	MapTile* townExpansion = *it;
	//	neighbours.erase(it);
	//	townExpansion->setType("town");
	//	townExpansion->setTileType(TileType::Town);
	//	townTiles.push_back(townExpansion);
	//	m_townTileCount++;
	//	townTileCount++;
	//}
}

std::vector<MapTile*> GameMap::getMaxWeightTiles(std::set<MapTile*> candidates) {
	std::vector<MapTile*> victors;
	int maxWeight = INT_MIN;
	std::set<MapTile*>::iterator it;
	for (it = candidates.begin(); it != candidates.end(); ++it) {
		if (m_currentWeights[(*it)->getX()][(*it)->getY()] > maxWeight) {
			maxWeight = m_currentWeights[(*it)->getX()][(*it)->getY()];
		}
	}
	for (it = candidates.begin(); it != candidates.end(); ++it) {
		if (m_currentWeights[(*it)->getX()][(*it)->getY()] = maxWeight) {
			victors.push_back((*it));
		}
	}
	return victors;
}

void GameMap::generateAllTowns() {
	int totalTowns = getRandomNumber(m_minTowns, m_maxTowns);
	for (int i = 0; i < totalTowns; ++i) {
		int townSize = getRandomNumber(m_townMinSize, m_townMaxSize); //set this towns size, random number between min and max
		if (((townSize + m_townTileCount) > m_townTileMax) && ((townSize + m_townTileCount) > m_townTileMax)) {
			//add tiles to existing towns and quit?
			//change tile count and add to city/rural count evenly? 
				//would have to call reduce city after towns to use updated counts
				//in a way would invalidate the town placement, but reducing the city just means theyd be further away so no issue
			//or do nothing?
		}
		MapTile* next = getNextTownCenter();
		generateTown(next, townSize);
	}
}

MapTile* GameMap::getNextTownCenter() {
	//set up weights - map boundary/town/city tiles to -1, unexplored tiles to INT_MIN
	int** m_currentWeights = new int*[m_size];

	for (int i = 0; i < m_size; ++i) {
		m_currentWeights[i] = new int[m_size];
		if (i == 0 || (i + 1) == m_size) {
			std::fill(m_currentWeights[i], m_currentWeights[i] + sizeof(m_currentWeights[i]), -1);
		}
		else {
			std::fill(m_currentWeights[i], m_currentWeights[i] + sizeof(m_currentWeights[i]), INT_MIN);
			m_currentWeights[i][0] = -1;
			m_currentWeights[i][(m_size - 1)] = -1;
		}

		for (int j = 0; j < m_size; ++j) {
			if (m_gameMap[i][j]->getType().compare("town") == 0 || m_gameMap[i][j]->getType().compare("city") == 0) {
				m_currentWeights[i][j] = -1;
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
			if (m_currentWeights[i][j] == -1) {
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
					if (m_currentWeights[current->getX()][current->getY()] < minAdjWeight) {
						minAdjWeight = m_currentWeights[current->getX()][current->getY()];
					}
					unvisited.push_back(tempTile);
				}
			}

			if (minAdjWeight != INT_MAX) {
				newWeight = minAdjWeight + 1;
			} else {
				std::cerr << "error getting next town - could not find adjacent unvisited tile";
			}

			m_currentWeights[current->getX()][current->getY()] = newWeight;

			visited.push_back(current);
			explored.push_back(current);
			unexplored.remove(current);
		}
		//scan from new spot
		MapTile* newSpot = unexplored.front();
		unvisited.push_back(newSpot);
	}

	int maxWeight = INT_MIN;
	std::vector<MapTile*> possibleTowns;
	MapTile* candidate = NULL;
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			if (m_currentWeights[i][j] > maxWeight) {
				candidate = m_gameMap[i][j];
				possibleTowns.clear();
				maxWeight = m_currentWeights[i][j];
				possibleTowns.push_back(candidate);
			} else if (m_currentWeights[i][j] == maxWeight) {
				candidate = m_gameMap[i][j];
				possibleTowns.push_back(candidate);
			}
		}
	}
	int randIndex = getRandomNumber(0, (possibleTowns.size() - 1));
	return possibleTowns.at(randIndex);
	//MapTile* current = m_gameMap[1][1];
	//if (m_currentWeights[1][1] == INT_MIN) {
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
	//		if (m_currentWeights[current->getX()][current->getY()] == INT_MIN) {
	//			start == current;
	//		}
	//	}
	//}
	//if (start == NULL) {
	//	std::cerr << "error getting next town - could not find position to start assigning m_currentWeights" << std::endl;
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
	//				if (m_currentWeights[tempTile->getX()][tempTile->getY()] < minAdjWeight) {
	//					minAdjWeight = m_currentWeights[tempTile->getX()][tempTile->getY()];
	//				}
	//			}
	//		}
	//	}
	//}
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
	std::list<MapTile*> path;
	double euclideanDistance = sqrt(((pow((start->getX() - end->getX()), 2)) + (pow((start->getY() - end->getY()), 2))));
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
	testMap.generateMap();
	testMap.printMap();
	
	return 0;
}*/
