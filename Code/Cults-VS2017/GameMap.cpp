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
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include <chrono>


GameMap::GameMap() {
	initializeGameMap(m_defaultSize);
}

GameMap::GameMap(int size) {

	initializeGameMap(size);
}

void GameMap::initializeGameMap(int size) {
	m_size = size;

	for (int i = 0; i < size; ++i) {
		std::vector<MapTile*> tileRow;
		for (int j = 0; j < size; ++j) {
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
	m_cityTileCount++;
	midPoint->setRoad(true);
	//generate average city "radius" ie length from center to edge
	int cityRadius = m_size / 4;
	//iterate in 4 directions, ie north/south/east/west
	for (int i = 0; i < 4; ++i) {
		//generate random length to change radius by with 50/50 odds of shrinking or growing
		int radiusChange = getRandomNumber(0, (m_size / 8));
		if (getRandomNumber(0, 2) == 0) {
			radiusChange = 0 - radiusChange;
		}
		//flip tiles to city for length of radius + random change to radius
		for (int j = 0; j < (cityRadius + radiusChange); ++j) {
			MapTile* tempTile = NULL;
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

			if (tempTile != NULL) {
				tempTile->setType("city");
				m_cityTileCount++;
			}
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

void GameMap::findPath(MapTile* start, MapTile* end) {
	std::list<MapTile*> path;
	double ed = getEuclideanDistance(start, end);
	//int subRanges = floor(ed / 4);
	//split in to sub areas, 
	//generate random points within sub area, 
	//form sub path through points, 
	//link sub paths together to form actual path

}

struct pathNode {
public:
	pathNode() { tile = NULL; };
	pathNode(MapTile* nodeTile) { tile = nodeTile; };
	int f;
	int g;
	int h;
	MapTile* tile;
	MapTile* next;
	MapTile* previous;
	bool pathNode::operator==(const pathNode& rhs) const { return ((f == rhs.f) && (g == rhs.g) && (h == rhs.h) && (tile == rhs.tile) && (next == rhs.next) && (previous == rhs.previous)); };
};

std::list<MapTile*> GameMap::aStar(MapTile* start, MapTile* end) {
	std::list<pathNode> nodePath;
	std::list<MapTile*> path;
	//std::map<MapTile*, pathNode> tileToNode;
	//discovered = open, visited = closed
	std::unordered_set<pathNode> visited, discovered;
	pathNode first(start);
	first.g = 0;
	first.h = getEuclideanDistance(start, end);
	first.f = first.g + first.h;
	first.previous = NULL;
	discovered.insert(first);
	nodePath.push_back(first);
	//tileToNode.insert(std::make_pair(start, first));

	while (!discovered.empty()) {
		//find discovered element, de, with lowerst f
		//remove de from discovered
		//get neighbours for de and set neighbours previous to de
		//for each neighbour, check if its the goal, else g = previous.g + 1, h = euclidean distance to end, f = h+g
		int minF = INT_MAX;
		pathNode minElement;
		for (std::unordered_set<pathNode>::iterator it = discovered.begin(); it != discovered.end(); ++it) {
			if ((*it).f < minF) {
				minF = (*it).f;
				minElement = (*it);
			}
		}
		discovered.erase(minElement);
		std::vector<MapTile*> neighbours = getNeighbouringTiles(minElement.tile);
		for (int i = 0; i < neighbours.size(); ++i) {
			pathNode nextNode(neighbours.at(i));
			nextNode.previous = minElement.tile;
			if (neighbours.at(i) == end) {
				//found goal node, path complete, end search
				//iterate backwards, call push front on list for each node until previous == null, then return list
			}
			nextNode.g = minElement.g + 1;
			nextNode.h = getEuclideanDistance(neighbours.at(i), end);
			nextNode.f = nextNode.g + nextNode.h;
			
			bool skip = false;

			//if (pathnode with same tile is in open/discovered list and has lower f, skip)
			for (std::unordered_set<pathNode>::iterator it = discovered.begin(); it != discovered.end(); ++it) {
				if ((*it).tile == neighbours.at(i) && (*it).f < nextNode.f) {
					//skip
					skip = true;
				}
			}
			if (!skip) {
				//if (pathnode with same tile is in closed/visited list and has lower f, skip. else add node to open list
				for (std::unordered_set<pathNode>::iterator it = visited.begin(); it != visited.end(); ++it) {
					if ((*it).tile == neighbours.at(i) && (*it).f < nextNode.f) {
						//skip
						skip = true;
					}
				}
			}
			if (!skip) {
				discovered.insert(nextNode);
			}
		}
		visited.insert(minElement);
	}

	return path;
}

double GameMap::getEuclideanDistance(MapTile* a, MapTile* b) {
	return sqrt(((pow((a->getX() - b->getX()), 2)) + (pow((a->getY() - b->getY()), 2))));
}

int GameMap::getDiagonalDistance(MapTile* a, MapTile* b) {
	return std::max(std::abs(a->getX() - b->getX()), std::abs(a->getY() - b->getY()));
}

int GameMap::getManhattanDistance(MapTile* a, MapTile* b) {
	return std::abs(a->getX() - b->getY()) + std::abs(a->getY() - b->getY());
}

void GameMap::generateAllTowns() {
	int totalTowns = getRandomNumber(m_minTowns, m_maxTowns);
	for (int i = 0; i < totalTowns; ++i) {
		int townSize = getRandomNumber(m_townMinSize, m_townMaxSize); //set this towns size, random number between min and max
																	  //if all town tiles are used, create minimum sized town and finish
		if ((townSize + m_townTileCount) > m_townTileMax) {
			townSize = m_townTileMax - m_townTileCount;
			if (townSize >= m_townMinSize) {
				MapTile* next = getNextTownCenter();
				generateTown(next, townSize);
			}
			return;
		}
		MapTile* next = getNextTownCenter();
		generateTown(next, townSize);
	}
}

void GameMap::generateTown(MapTile* center, int size) {
	center->setType("town");
	m_townTileCount++; //increment town tiles used
	int townTileCount = 1; //track this towns tiles
	std::unordered_set<MapTile*> townTiles = { center };
	std::unordered_set<MapTile*> neighbours;

	while (townTileCount <= size) {
		std::unordered_set<MapTile*>::iterator townTileIterator;
		for (townTileIterator = townTiles.begin(); townTileIterator != townTiles.end(); ++townTileIterator) {
			std::vector<MapTile*> newNeighbours = getNeighbouringTiles((*townTileIterator));
			for (int j = 0; j < newNeighbours.size(); ++j) {
				//if ((newNeighbours.at(j)->getType().compare("town") != 0) && (newNeighbours.at(j)->getType().compare("city") != 0)) {
				if (newNeighbours.at(j)->getWeight() != -1) {
					neighbours.insert(newNeighbours.at(j));
				}
			}
		}
		std::unordered_set<MapTile*> bestNeighbours = getTilesWithWeight(0, true, neighbours);
		std::map<int, std::unordered_set<MapTile*> > adjustedWeights;
		for (std::unordered_set<MapTile*>::iterator it = bestNeighbours.begin(); it != bestNeighbours.end(); ++it) {
			//adjustedWeights.insert(std::make_pair(((*it)->getWeight() - /* distance from center */1),(*it)));
			adjustedWeights[((*it)->getWeight() - getDiagonalDistance((*it),center))].insert((*it));
		}
		std::unordered_set<MapTile*> evenBetterNeighbours;
		int randIndex = getRandomNumber(0, (bestNeighbours.size() - 1));
		std::unordered_set<MapTile*>::iterator it = bestNeighbours.begin();
		advance(it, randIndex);
		MapTile* townExpansion = (*it);
		townExpansion->setType("town");
		townExpansion->setTileType(TileType::Town);
		townExpansion->setWeight(-1);
		townTiles.insert(townExpansion);
		neighbours.erase(townExpansion);
		m_townTileCount++;
		townTileCount++;
	}
}

MapTile* GameMap::getNextTownCenter() {
	initialiseWeights();
	calculateWeights();
	//backpropagateWeights();

	int maxWeight = INT_MIN;
	std::unordered_set<MapTile*> possibleTowns = getTilesWithWeight(0, true);
	MapTile* candidate = NULL;


	//could pick town by checking which tile has neighbours with highest weights
	int randIndex = getRandomNumber(0, (possibleTowns.size() - 1));
	std::unordered_set<MapTile*>::iterator it(possibleTowns.begin());
	advance(it, randIndex);
	return (*it);
}

std::unordered_set<MapTile*> GameMap::getTilesWithWeight(int weight, bool findMax) {
	std::map<int, std::unordered_set<MapTile*> > weights;

	for (int i = 0; i < m_gameMap.size(); ++i) {
		for (int j = 0; j < m_gameMap[i].size(); ++j) {
			/*if (weights.find(m_gameMap[i][j]->getWeight()) != weights.end()) {
			std::unordered_set<MapTile*> s = { m_gameMap[i][j] };
			weights[m_gameMap[i][j]->getWeight()] = s;
			} else {*/
			weights[m_gameMap[i][j]->getWeight()].insert(m_gameMap[i][j]);
			/*}*/
		}
	}

	if (findMax) {
		std::vector<int> keys;
		for (std::map<int, std::unordered_set<MapTile*> >::iterator it = weights.begin(); it != weights.end(); ++it) {
			keys.push_back(it->first);
		}
		int max = *max_element(keys.begin(), keys.end());
		return weights[max];
	}

	return weights[weight];
}

std::unordered_set<MapTile*> GameMap::getTilesWithWeight(int weight, bool findMax, std::unordered_set<MapTile*> tiles) {
	std::map<int, std::unordered_set<MapTile*> > weights;

	for (std::unordered_set<MapTile*>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		if (weights.find((*it)->getWeight()) != weights.end()) {
			std::unordered_set<MapTile*> s = { (*it) };
			weights[(*it)->getWeight()] = s;
		}
		else {
			weights[(*it)->getWeight()].insert((*it));
		}
	}

	if (findMax) {
		std::vector<int> keys;
		for (std::map<int, std::unordered_set<MapTile*> >::iterator it = weights.begin(); it != weights.end(); ++it) {
			keys.push_back(it->first);
		}
		int max = *max_element(keys.begin(), keys.end());
		return weights[max];
	}

	return weights[weight];
}

std::vector<MapTile*> GameMap::getNeighbouringTiles(MapTile* tile, bool rightStart = true) {
	std::vector<MapTile*> neighbours;
	std::vector<std::pair<int, int> > deltas;
	if (rightStart) {
		//right, bottom right, bottom, bottom left, left, left top, top, top right
		//{ { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1,0 }, { -1, -1 }, { 0, -1 }, { 1, -1 } };
		deltas.push_back(std::make_pair(1, 0));
		deltas.push_back(std::make_pair(1, 1));
		deltas.push_back(std::make_pair(0, 1));
		deltas.push_back(std::make_pair(-1, 1));
		deltas.push_back(std::make_pair(-1, 0));
		deltas.push_back(std::make_pair(-1, -1));
		deltas.push_back(std::make_pair(0, -1));
		deltas.push_back(std::make_pair(1, -1));
	}
	else {
		//left, left top, top, top right, right, bottom right, bottom, bottom left
		//{ -1,0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }
		deltas.push_back(std::make_pair(-1, 0));
		deltas.push_back(std::make_pair(-1, -1));
		deltas.push_back(std::make_pair(0, -1));
		deltas.push_back(std::make_pair(1, -1));
		deltas.push_back(std::make_pair(1, 0));
		deltas.push_back(std::make_pair(1, 1));
		deltas.push_back(std::make_pair(0, 1));
		deltas.push_back(std::make_pair(-1, 1));
	}

	int tX = tile->getX();
	int tY = tile->getY();
	for (int i = 0; i < deltas.size(); ++i) {
		if (((tX + (deltas.at(i).first)) >= 0) && ((tX + (deltas.at(i).first)) < m_size) && ((tY + (deltas.at(i).second)) >= 0) && ((tY + (deltas.at(i).second)) < m_size)) {
			neighbours.push_back(m_gameMap[(tX + (deltas.at(i).first))][(tY + (deltas.at(i).second))]);
		}
	}
	return neighbours;
}

void GameMap::initialiseWeights() {
	for (int i = 0; i < m_gameMap.size(); ++i) {
		for (int j = 0; j < m_gameMap[i].size(); ++j) {
			if ((i == 0) || (j == 0) || (i == (m_size - 1)) || (j == (m_size - 1)) || (m_gameMap[i][j]->getType().compare("town") == 0) || (m_gameMap[i][j]->getType().compare("city") == 0)) {
				m_gameMap[i][j]->setWeight(-1);
			}
			else {
				m_gameMap[i][j]->setWeight(INT_MAX);
			}
		}
	}
}

void GameMap::calculateWeights() {
	//find all tiles with weight -1, set adj tiles to weight 0
	//repeat until no tiles have weight of int_max
	int currentWeight = -1;
	std::unordered_set<MapTile*> currentTier = getTilesWithWeight(-1, false);

	while (!currentTier.empty()) {
		std::unordered_set<MapTile*> nextTier;
		for (std::unordered_set<MapTile*>::iterator it = currentTier.begin(); it != currentTier.end(); ++it) {
			std::vector<MapTile*> neighbours = getNeighbouringTiles((*it));
			for (int i = 0; i < neighbours.size(); ++i) {
				if (neighbours[i]->getWeight() == INT_MAX) {
					neighbours[i]->setWeight(currentWeight + 1);
					nextTier.insert(neighbours[i]);
				}
			}
		}
		currentWeight++;
		currentTier.clear();
		currentTier = nextTier;
		nextTier.clear();
	}
}

int GameMap::getRandomNumber(int min, int max) {
	std::random_device rd; //obtain rand num from hw
	std::mt19937 eng(rd()); //seed generator
							//handle case if numbers in reverse order
	if (min > max) {
		std::uniform_int_distribution<> distr(max, min); //define range
		return distr(eng);
	}
	std::uniform_int_distribution<> distr(min, max); //define range
	return distr(eng);
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

void GameMap::PrintToFile(std::string output) {
	std::fstream fs;
	fs.open(output, std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (int i = 0; i < m_gameMap.size(); ++i) {
		for (int j = 0; j < m_gameMap[i].size(); ++j) {
			fs << m_gameMap[i][j]->getType() << ",";
		}
		fs << std::endl;
	}
	fs.close();
}

void GameMap::visualiseMapAsPpm() {
	std::fstream fs;
	fs.open("output.ppm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs << "P3" << std::endl;
	std::string size = std::to_string(m_size);
	fs << size << " " << size << std::endl;
	fs << "255" << std::endl;
	for (int i = 0; i < m_gameMap.size(); ++i) {
		for (int j = 0; j < m_gameMap[i].size(); ++j) {
			if (m_gameMap[i][j]->getType().compare("blank") == 0) {
				fs << "255 0 0" << "	";
			} else if (m_gameMap[i][j]->getType().compare("city") == 0) {
				fs << "115 115 115" << "	";
			} else if (m_gameMap[i][j]->getType().compare("town") == 0) {
				fs << "0 0 255" << "	";
			} else if (m_gameMap[i][j]->getType().compare("rural") == 0) {
				fs << "0 255 0" << "	";
			}
		}
		fs << std::endl;
	}
	fs.close();
}

void GameMap::visualiseMapWithPathAsPpm(MapTile* start, MapTile* end) {
	std::list<MapTile*> path = aStar(start, end);
	std::fstream fs;
	std::string fileName = getDateTimeNow() + "_mapImageOutput.ppm";
	boost::replace_all(fileName, ":", "");
	boost::replace_all(fileName, "\n", "");
	boost::replace_all(fileName, " ", "_");
	fs.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs << "P3" << std::endl;
	std::string size = std::to_string(m_size);
	fs << size << " " << size << std::endl;
	fs << "255" << std::endl;
	for (int i = 0; i < m_gameMap.size(); ++i) {
		for (int j = 0; j < m_gameMap[i].size(); ++j) {
			if (std::find(path.begin(), path.end(), m_gameMap[i][j]) != path.end()) {
				fs << "255 0 0" << "	";
			} else {
				if (m_gameMap[i][j]->getType().compare("blank") == 0) {
					fs << "0 0 0" << "	";
				} else if (m_gameMap[i][j]->getType().compare("city") == 0) {
					fs << "115 115 115" << "	";
				} else if (m_gameMap[i][j]->getType().compare("town") == 0) {
					fs << "0 0 255" << "	";
				} else if (m_gameMap[i][j]->getType().compare("rural") == 0) {
					fs << "0 255 0" << "	";
				}
			}
		}
		fs << std::endl;
	}
	fs.close();
}

std::string getDateTimeNow() {
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(p);
	return std::ctime(&t);
}

/*
int main(int ac, char** av) {
	std::srand(time(0));
	GameMap testMap = GameMap(125);
	testMap.generateMap();
	testMap.printMap();

	testMap.PrintToFile("gameMap_Output.txt");
	testMap.visualiseMapAsPpm();

	std::cin.get();

	return 0;
}
*/