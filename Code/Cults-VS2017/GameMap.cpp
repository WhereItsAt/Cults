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

}

double GameMap::getEuclideanDistance(MapTile* a, MapTile* b) {
	return sqrt(((pow((a->getX() - b->getX()), 2)) + (pow((a->getY() - b->getY()), 2))));
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
			std::vector<MapTile*> newNeighbours = getNeighbouringTiles((*townTileIterator), true);
			for (int j = 0; j < newNeighbours.size(); ++j) {
				//if ((newNeighbours.at(j)->getType().compare("town") != 0) && (newNeighbours.at(j)->getType().compare("city") != 0)) {
				if (newNeighbours.at(j)->getWeight() != -1) {
					neighbours.insert(newNeighbours.at(j));
				}
			}
		}
		std::unordered_set<MapTile*> bestNeigh = getTilesWithWeight(0, true, neighbours);
		int randIndex = getRandomNumber(0, (bestNeigh.size() - 1));
		std::unordered_set<MapTile*>::iterator it = bestNeigh.begin();
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

std::vector<MapTile*> GameMap::getNeighbouringTiles(MapTile* tile, bool rightStart) {
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
			std::vector<MapTile*> neighbours = getNeighbouringTiles((*it), true);
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
			}
			else if (m_gameMap[i][j]->getType().compare("city") == 0) {
				fs << "115 115 115" << "	";
			}
			else if (m_gameMap[i][j]->getType().compare("town") == 0) {
				fs << "0 0 255" << "	";
			}
			else if (m_gameMap[i][j]->getType().compare("rural") == 0) {
				fs << "0 255 0" << "	";
			}
		}
		fs << std::endl;
	}
	fs.close();
}

void GameMap::visualiseMapAsBmp() {
	//red 255 0 0 -city
	//green 0 255 0 -rural
	//blue 0 0 255 -town
	//white 255 255 255 -blank
	unsigned char *img = NULL;
	int filesize = 54 + (3 * m_size*m_size);
	int **red = new int*[m_size];
	int **green = new int*[m_size];
	int **blue = new int*[m_size];
	for (int i = 0; i < m_size; ++i) {
		red[i] = new int[m_size];
		green[i] = new int[m_size];
		blue[i] = new int[m_size];
	}

	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			if (m_gameMap[i][j]->getType().compare("blank") == 0) {
				red[i][j] = 255;
				green[i][j] = 255;
				blue[i][j] = 255;
			}
			else if (m_gameMap[i][j]->getType().compare("city") == 0) {
				red[i][j] = 255;
				green[i][j] = 0;
				blue[i][j] = 0;
			}
			else if (m_gameMap[i][j]->getType().compare("town") == 0) {
				red[i][j] = 0;
				green[i][j] = 0;
				blue[i][j] = 255;
			}
			else if (m_gameMap[i][j]->getType().compare("rural") == 0) {
				red[i][j] = 0;
				green[i][j] = 255;
				blue[i][j] = 0;
			}
		}
	}

	img = (unsigned char *)malloc(3 * m_size*m_size);
	memset(img, 0, 3 * m_size*m_size);

	for (int i = 0; i<m_size; i++)
	{
		for (int j = 0; j<m_size; j++)
		{
			int x = i;
			int y = (m_size - 1) - j;
			int r = red[i][j] * 255;
			int g = green[i][j] * 255;
			int b = blue[i][j] * 255;
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			img[(x + y*m_size) * 3 + 2] = (unsigned char)(r);
			img[(x + y*m_size) * 3 + 1] = (unsigned char)(g);
			img[(x + y*m_size) * 3 + 0] = (unsigned char)(b);
		}
	}

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(m_size);
	bmpinfoheader[5] = (unsigned char)(m_size >> 8);
	bmpinfoheader[6] = (unsigned char)(m_size >> 16);
	bmpinfoheader[7] = (unsigned char)(m_size >> 24);
	bmpinfoheader[8] = (unsigned char)(m_size);
	bmpinfoheader[9] = (unsigned char)(m_size >> 8);
	bmpinfoheader[10] = (unsigned char)(m_size >> 16);
	bmpinfoheader[11] = (unsigned char)(m_size >> 24);

	std::fstream fs;
	fs.open("output.bmp", std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (int i = 0; i < 14; ++i) {
		fs << bmpfileheader[i];
	}
	for (int i = 0; i < 40; ++i) {
		fs << bmpinfoheader[i];
	}
	//fwrite(bmpfileheader, 1, 14, fs);
	//fwrite(bmpinfoheader, 1, 40, fs);
	for (int i = 0; i < m_size; ++i)
	{
		//fwrite(img + (m_size*(m_size - i - 1) * 3), 3, m_size, fs);
		unsigned char* tempChar = img + (m_size*(m_size - i - 1) * 3);
		for (int j = 0; j < m_size; ++j) {
			fs << tempChar;
			tempChar += 3;
		}

		//fwrite(bmppad, 1, (4 - (m_size * 3) % 4) % 4, fs);
		unsigned char* tempBmpChar = bmppad;
		for (int j = 0; j < ((4 - (m_size * 3) % 4) % 4); ++j) {
			fs << tempChar;
			tempBmpChar++;
		}
	}

	free(img);
	fs.close();
}

//void GameMap::calculateWeights() {
//	//keep list of all explored and unexplored tiles, finish when all tiles explored
//	//add all unusable (boundary/city/town) tiles to explored, the rest to unexplored
//	//add first tile to unvisited, use two while loops to maintain search of current reachable tiles and all tiles
//	//find neighbours, add to unvisited if not in visited, check to see if adj tile has the minimum weight of all neighbours
//	//update current tile weight to be min adj weight plus one
//	//add tile to visited/explored, and remove from unexplored, already removed from visited at start of loop
//	//if we have visited all adjacent tiles, but there are still unexplored tiles we grab the next one add to unvisited and start again
//	std::vector<MapTile*> visited, explored;
//	std::list<MapTile*> unvisited, unexplored;
//	for (int i = 0; i < m_size; ++i) {
//		for (int j = 0; j < m_size; ++j) {
//			if (m_currentWeights[i][j] == -1) {
//				if (!TileIsInVector(m_gameMap[i][j], explored)) {
//					explored.push_back(m_gameMap[i][j]);
//				}
//			}
//			else {
//				if (!TileIsInList(m_gameMap[i][j], unexplored)) {
//					unexplored.push_back(m_gameMap[i][j]);
//				}
//			}
//		}
//	}
//
//	MapTile* current = m_gameMap[0][0];
//	unvisited.push_back(current);
//	while (!unexplored.empty()) {
//		while (!unvisited.empty()) {
//			current = unvisited.front();
//			unvisited.pop_front();
//
//			int minAdjWeight = INT_MAX;
//			int newWeight = -1;
//			std::vector<MapTile*> neigh = getNeighbouringTiles(current, true);
//			for (int i = 0; i < neigh.size(); ++i) {
//				MapTile* tempTile = neigh.at(i);
//				if (TileIsInVector(tempTile, explored)) {
//					if (m_currentWeights[tempTile->getX()][tempTile->getY()] < minAdjWeight) {
//						minAdjWeight = m_currentWeights[tempTile->getX()][tempTile->getY()];
//					}
//				}
//				//if tile isnt visited
//				//if ((!TileIsInList(tempTile, unvisited)) && (!TileIsInList(tempTile, unexplored))) {
//				if ((!TileIsInVector(tempTile, visited)) && (!TileIsInList(tempTile, unvisited))) {
//					unvisited.push_back(tempTile);
//				}
//			}
//
//			if (minAdjWeight != INT_MAX) {
//				newWeight = minAdjWeight + 1;
//				if (m_currentWeights[current->getX()][current->getY()] != -1) {
//					m_currentWeights[current->getX()][current->getY()] = newWeight;
//				}
//			}
//			else {
//				std::cerr << "error getting next town - could not find adjacent unvisited tile" << std::endl;
//			}
//
//			if (!TileIsInVector(current, visited)) {
//				visited.push_back(current);
//			}
//			if (!TileIsInVector(current, explored)) {
//				explored.push_back(current);
//			}
//			unexplored.remove(current);
//		}
//		//scan from new spot
//		if (!unexplored.empty()) {
//			MapTile* newSpot = unexplored.front();
//			if (!TileIsInList(newSpot, unvisited)) {
//				unvisited.push_back(newSpot);
//			}
//		}
//	}
//}

//bool GameMap::TileIsInList(MapTile* tile, std::list<MapTile*> queue) {
//	
//	std::list<MapTile*>::iterator it;
//	for (it = queue.begin(); it != queue.end(); ++it) {
//		if ((tile->getX() == (*it)->getX()) && (tile->getY() == (*it)->getY())) {
//			return true;
//		}
//	}
//	return false;
//}

//std::list<MapTile*> GameMap::removeTileFromList(std::list<MapTile*> original, MapTile* tile) {
//	std::list<MapTile*> newList;
//	std::copy(original.begin(), original.end(), std::back_inserter(newList));
//	std::list<MapTile*>::iterator finder = std::find(original.begin(), original.end(), tile);
//	newList.splice(newList.end(), newList, finder);
//	newList.pop_back();
//	return newList;
//}

//std::vector<MapTile*> GameMap::removeTileFromVector(std::vector<MapTile*> original, MapTile* tile) {
//	std::vector<MapTile*> newVector;
//	std::copy(original.begin(), original.end(), std::back_inserter(newVector));
//	newVector.erase(std::remove(newVector.begin(), newVector.end(), tile), newVector.end());
//	return newVector;
//}

//bool GameMap::TileIsInVector(MapTile* tile, std::vector<MapTile*> queue) {
//	for (int i = 0; i < queue.size(); ++i) {
//		if ((tile->getX() == queue.at(i)->getX()) && (tile->getY() == queue.at(i)->getY())) {
//			return true;
//		}
//	}
//	return false;
//}
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