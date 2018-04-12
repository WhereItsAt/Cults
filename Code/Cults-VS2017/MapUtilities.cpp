#pragma warning(disable : 4996)

#include "MapUtilities.h"
#include "GameMap.h"
#include "PathNode.h"

#include <iostream>
#include <cmath>
#include <chrono>
#include <map>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>


MapUtilities::MapUtilities(GameMap* map)
{
	m_map = map;
}


MapUtilities::~MapUtilities()
{
}

void MapUtilities::printMap() {
	for (int i = 0; i < m_map->getSize(); ++i) {
		for (int j = 0; j < m_map->getSize(); ++j) {
			MapTile* tempTile = (*(m_map->getMap()))[j][i];
			std::cout << tempTile->getType() << ", "; /*<< "(" << tempTile->getX() << "," << tempTile->getY() << "); "*/
		}
		std::cout << std::endl;
	}
}

void MapUtilities::printOnly(std::string type) {
	for (int i = 0; i < m_map->getSize(); ++i) {
		for (int j = 0; j < m_map->getSize(); ++j) {
			MapTile* tempTile = (*(m_map->getMap()))[j][i];
			//if (tempTile->getTileType() == i) {
			if (tempTile->getType().compare(type) == 0) {
				std::cout << tempTile->getType() /*<< "(" << tempTile->getX() << "," << tempTile->getY() << "); "*/ << ", ";
			}
			else {
				std::cout << " , ";
			}
		}
		std::cout << std::endl;
	}
}

MapTile* MapUtilities::getMiddle() {
	MapTile* mid = (*(m_map->getMap()))[m_map->getSize() / 2][m_map->getSize() / 2];
	return mid;
}

MapTile* MapUtilities::getMidPoint(MapTile* start, MapTile* end) {
	MapTile* midpoint = start;
	if (start->getX() > end->getX() && start->getY() > end->getY()) {
		//start is south east of end
		midpoint = (*(m_map->getMap()))[end->getX() + ((start->getX() - end->getX()) / 2)][end->getY() + ((start->getY() - end->getY()) / 2)];
	}
	else if (start->getX() < end->getX() && start->getY() < end->getY()) {
		//start is north west of end
		midpoint = (*(m_map->getMap()))[start->getX() + ((end->getX() - start->getX()) / 2)][start->getY() + ((end->getY() - start->getY()) / 2)];
	}
	else if (start->getX() > end->getX() && start->getY() < end->getY()) {
		//start is north east of end
		midpoint = (*(m_map->getMap()))[end->getX() + ((start->getX() - end->getX()) / 2)][start->getY() + ((end->getY() - start->getY()) / 2)];
	}
	else if (start->getX() < end->getX() && start->getY() > end->getY()) {
		//start is south west of end
		midpoint = (*(m_map->getMap()))[start->getX() + ((end->getX() - start->getX()) / 2)][end->getY() + ((start->getY() - end->getY()) / 2)];
	}
	return midpoint;
}

int MapUtilities::getRandomNumberInRangePositiveOrNegative(int num1, int num2, float chanceToFlip) {
	int result = getRandomNumber(num1, num2);
	if (getRandomNumber(0, 100) < (100 * chanceToFlip)) {
		result *= -1;
	}
	return result;
}

MapTile* MapUtilities::getRandomBoundaryTile(int edge, int startingPoint) {
	MapTile* result = NULL;
	//N = {x,y=0}, E = {x=m_map->getSize()-1,y}, S = {x=m_map->getSize()-1,y}, W = {x=0,y}
	int randomX, randomY;
	switch (edge) {
	case 0:
		randomX = getRandomNumber(startingPoint, (m_map->getSize() - 1));
		result = (*(m_map->getMap()))[randomX][0];
		break;
	case 1:
		randomY = getRandomNumber(startingPoint, (m_map->getSize() - 1));
		result = (*(m_map->getMap()))[(m_map->getSize() - 1)][randomY];
		break;
	case 2:
		randomX = getRandomNumber(startingPoint, (m_map->getSize() - 1));
		result = (*(m_map->getMap()))[randomX][(m_map->getSize() - 1)];
		break;
	case 3:
		randomY = getRandomNumber(startingPoint, (m_map->getSize() - 1));
		result = (*(m_map->getMap()))[0][randomY];
		break;
	default:
		//shouldnt happen
		break;
	}
	return result;
}

MapTile* MapUtilities::getRandomTileInRange(MapTile* tile, int range) {
	std::unordered_set<MapTile*> possibleTiles;
	int previousSize = 0;
	possibleTiles.insert(tile);
	while (previousSize != possibleTiles.size()) {
		for (std::unordered_set<MapTile*>::iterator it = possibleTiles.begin(); it != possibleTiles.end(); ++it) {
			std::vector<MapTile*> neighbours = getNeighbouringTiles((*it));
			for (int i = 0; i < neighbours.size(); ++i) {
				if (getEuclideanDistance(tile, neighbours.at(i)) < range) {
					possibleTiles.insert(neighbours.at(i));
				}
			}
		}
		previousSize = possibleTiles.size();
	}
	int randomIndex = getRandomNumber(0, (possibleTiles.size() - 1));
	std::unordered_set<MapTile*>::iterator it = possibleTiles.begin();
	std::advance(it, randomIndex);
	return (*it);
}

int MapUtilities::getStartingPointShiftValue(int startEdge, int endEdge, MapTile* start, int minDistance) {
	//find how far along end edge to shift starting point to meet min distance value
	int result = 0;
	int x, y;
	MapTile* end;
	switch (endEdge) {
	case 0:
		x = 0;
		end = (*(m_map->getMap()))[x][0];
		while (getEuclideanDistance(start, end) < minDistance) {
			x++;
			end = (*(m_map->getMap()))[x][0];
		}
		result = x;
		break;
	case 1:
		y = 0;
		end = (*(m_map->getMap()))[(m_map->getSize() - 1)][y];
		while (getEuclideanDistance(start, end) < minDistance) {
			y++;
			end = (*(m_map->getMap()))[(m_map->getSize() - 1)][y];
		}
		result = y;
		break;
	case 2:
		x = 0;
		end = (*(m_map->getMap()))[x][(m_map->getSize() - 1)];
		while (getEuclideanDistance(start, end) < minDistance) {
			x++;
			end = (*(m_map->getMap()))[x][(m_map->getSize() - 1)];
		}
		result = x;
		break;
	case 3:
		y = 0;
		end = (*(m_map->getMap()))[0][y];
		while (getEuclideanDistance(start, end) < minDistance) {
			y++;
			end = (*(m_map->getMap()))[0][y];
		}
		result = y;
		break;
	default:
		//shouldnt happen
		break;
	}
	return result;
}

int MapUtilities::getMapSize()
{
	return m_map->getSize();
}

std::list<MapTile*> MapUtilities::aStar(MapTile* start, MapTile* end) {
	std::list<MapTile*> path;
	//discovered = open, visited = closed
	//std::unordered_set<PathNode*> visited;
	std::unordered_set<PathNode*> closed;
	std::unordered_set<PathNode*> open;
	//std::unordered_set<PathNode*> discovered;

	PathNode* first = new PathNode(start);
	first->g = 0;
	first->h = getEuclideanDistance(start, end);
	first->f = first->g + first->h;
	first->previous = NULL;
	open.insert(first);

	while (!open.empty()) {
		int minF = INT_MAX;
		PathNode* minElement;
		for (std::unordered_set<PathNode*>::iterator it = open.begin(); it != open.end(); ++it) {
			if ((*it)->f < minF) {
				minF = (*it)->f;
				minElement = (*it);
			}
		}
		open.erase(minElement);

		if (*(minElement->tile) == *end) {
			PathNode* previousNode = NULL;
			PathNode* currentNode = minElement;
			currentNode->next = NULL;
			while (currentNode->previous != NULL) {
				path.push_front(currentNode->tile);
				previousNode = currentNode;
				currentNode = currentNode->previous;
				currentNode->next = previousNode;
			}
			//printPath(path);
			return path;
		}
		else {
			std::vector<MapTile*> neighbours = getNeighbouringTiles(minElement->tile);
			for (int i = 0; i < neighbours.size(); ++i) {
				bool inClosedList = false;
				bool inOpenList = false;
				PathNode* openNode = NULL;
				for (std::unordered_set<PathNode*>::iterator it = closed.begin(); it != closed.end(); ++it) {
					if (*((*it)->tile) == *(neighbours.at(i))) {
						inClosedList = true;
					}
				}
				for (std::unordered_set<PathNode*>::iterator it = open.begin(); it != open.end(); ++it) {
					if (*((*it)->tile) == *(neighbours.at(i))) {
						inOpenList = true;
						openNode = (*it);
					}
				}

				if (!inClosedList) {
					PathNode* neighbourNode = new PathNode(neighbours.at(i));
					neighbourNode->previous = minElement;
					neighbourNode->g = minElement->g + 1;
					neighbourNode->h = getEuclideanDistance(neighbours.at(i), end);
					neighbourNode->f = neighbourNode->g + neighbourNode->h;
					if (!inOpenList) {
						//add to open and closed?
						open.insert(neighbourNode);
						closed.insert(neighbourNode);
					}
					else {
						//if version in open list, swap them
						if (openNode->g > neighbourNode->g) {
							open.erase(openNode);
							open.insert(neighbourNode);
						}
					}
				}
			}
		}
	}

	return path;
}

double MapUtilities::getEuclideanDistance(MapTile* a, MapTile* b) {
	return sqrt(((pow((a->getX() - b->getX()), 2)) + (pow((a->getY() - b->getY()), 2))));
}

int MapUtilities::getDiagonalDistance(MapTile* a, MapTile* b) {
	return std::max(std::abs(a->getX() - b->getX()), std::abs(a->getY() - b->getY()));
}

int MapUtilities::getManhattanDistance(MapTile* a, MapTile* b) {
	return std::abs(a->getX() - b->getY()) + std::abs(a->getY() - b->getY());
}

int MapUtilities::getMaxWeight() {
	int maxWeight = 0;
	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap()))[i].size(); ++j) {
			if (((*(m_map->getMap()))[i][j]->getWeight() > maxWeight) && ((*(m_map->getMap()))[i][j]->getWeight() != INT_MAX)) {
				maxWeight = (*(m_map->getMap()))[i][j]->getWeight();
			}
		}
	}
	return maxWeight;
}

std::unordered_set<MapTile*> MapUtilities::getTilesWithWeight(int weight, bool findMax) {
	std::map<int, std::unordered_set<MapTile*> > weights;

	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap()))[i].size(); ++j) {
			/*if (weights.find((*(m_map->getMap()))[i][j]->getWeight()) != weights.end()) {
			std::unordered_set<MapTile*> s = { (*(m_map->getMap()))[i][j] };
			weights[(*(m_map->getMap()))[i][j]->getWeight()] = s;
			} else {*/
			weights[(*(m_map->getMap()))[i][j]->getWeight()].insert((*(m_map->getMap()))[i][j]);
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

std::unordered_set<MapTile*> MapUtilities::getTilesWithWeight(int weight, bool findMax, std::unordered_set<MapTile*> tiles) {
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

std::vector<MapTile*> MapUtilities::getNeighbouringTiles(MapTile* tile, bool startOnTileBelow) {
	std::vector<MapTile*> neighbours;
	std::vector<std::pair<int, int> > deltas;
	if (startOnTileBelow) {
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
		if (((tX + (deltas.at(i).first)) >= 0) && ((tX + (deltas.at(i).first)) < m_map->getSize()) && ((tY + (deltas.at(i).second)) >= 0) && ((tY + (deltas.at(i).second)) < m_map->getSize())) {
			//std::cout << "old x: " << tX << ", old y: " << tY << ". new x: " << (tX + (deltas.at(i).first)) << ", new y: " << (tY + (deltas.at(i).second)) << std::endl;
			//neighbours.push_back((*(m_map->getMap()))[(tY + (deltas.at(i).second))][(tX + (deltas.at(i).first))]);
			neighbours.push_back((*(m_map->getMap()))[(tX + (deltas.at(i).first))][(tY + (deltas.at(i).second))]);
		}
	}

	//validation
	//for (int i = 0; i < neighbours.size(); ++i) {
	//	int xDiff = neighbours.at(i)->getX() - tile->getX();
	//	int yDiff = neighbours.at(i)->getY() - tile->getY();
	//	if ((xDiff > 1 || xDiff < -1) || (yDiff > 1 || yDiff < -1)) {
	//		std::string message = "incorrect neighbour selected. original:" + tile->toString() + " neighbour: " + neighbours.at(i)->toString();
	//		std::cout << message << std::endl;
	//	}
	//}

	return neighbours;
}

std::vector<MapTile*> MapUtilities::getNonDiagonallyAdjacentNeighbours(MapTile* tile) {
	std::vector<MapTile*> neighbours;
	std::vector<std::pair<int, int> > deltas = { std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, 1), std::make_pair(0, -1) };
	int tX = tile->getX();
	int tY = tile->getY();
	for (int i = 0; i < deltas.size(); ++i) {
		if (((tX + (deltas.at(i).first)) >= 0) && ((tX + (deltas.at(i).first)) < m_map->getSize()) && ((tY + (deltas.at(i).second)) >= 0) && ((tY + (deltas.at(i).second)) < m_map->getSize())) {
			neighbours.push_back((*(m_map->getMap()))[(tX + (deltas.at(i).first))][(tY + (deltas.at(i).second))]);
		}
	}
	return neighbours;
}

void MapUtilities::initialiseWeights() {
	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap()))[i].size(); ++j) {
			if ((i == 0) || (j == 0) || (i == (m_map->getSize() - 1)) || (j == (m_map->getSize() - 1))) {
				(*(m_map->getMap()))[i][j]->setWeight(-1);
			} else if (((i == 1) || (j == 1) || (i == (m_map->getSize() - 2)) || (j == (m_map->getSize() - 2))) && ((((*(m_map->getMap()))[i][j]->getType().compare("town") != 0) && ((*(m_map->getMap()))[i][j]->getType().compare("city") != 0)) && ((*(m_map->getMap()))[i][j]->getType().compare("mountain") != 0))) {
				(*(m_map->getMap()))[i][j]->setWeight(m_borderWeightBump);
			} else if (((*(m_map->getMap()))[i][j]->getType().compare("town") == 0) || ((*(m_map->getMap()))[i][j]->getType().compare("city") == 0) || ((*(m_map->getMap()))[i][j]->getType().compare("mountain") == 0)) {
				
				(*(m_map->getMap()))[i][j]->setWeight(-1);
			} else {
				(*(m_map->getMap()))[i][j]->setWeight(INT_MAX);
			}
		}
	}
}

void MapUtilities::calculateWeights() {
	//find all tiles with weight -1, set adj tiles to weight 0
	//repeat until no tiles have weight of int_max

	//need to add tiles with weight of 3 initially too to accomodate border weight bump up
	int currentWeight = -1;
	std::unordered_set<MapTile*> currentTier = getTilesWithWeight(-1, false);
	std::unordered_set<MapTile*> bordertiles = getTilesWithWeight(m_borderWeightBump, false);
	for (std::unordered_set<MapTile*>::iterator it = bordertiles.begin(); it != bordertiles.end(); ++it) {
		currentTier.insert((*it));
	}

	while (!currentTier.empty()) {
		std::unordered_set<MapTile*> nextTier;
		for (std::unordered_set<MapTile*>::iterator it = currentTier.begin(); it != currentTier.end(); ++it) {
			std::vector<MapTile*> neighbours = getNeighbouringTiles((*it));
			for (int i = 0; i < neighbours.size(); ++i) {
				if (neighbours[i]->getWeight() == INT_MAX) {
					//neighbours[i]->setWeight(currentWeight + 1);
					neighbours[i]->setWeight((*it)->getWeight() + 1);
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

int MapUtilities::getRandomNumber(int min, int max) {
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

void MapUtilities::PrintToFile(std::string output) {
	std::fstream fs;
	fs.open(output, std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap()))[i].size(); ++j) {
			//fs << (*(m_map->getMap()))[i][j]->getType() << ",";
			fs << "(" << (*(m_map->getMap()))[i][j]->getX() << "," << (*(m_map->getMap()))[i][j]->getY() << ");";
		}
		fs << std::endl;
	}
	fs.close();
}

void MapUtilities::visualiseMapAsPpm() {
	std::fstream fs;
	std::string fileName = datePretty() + "_mapOutput.ppm";
	boost::replace_all(fileName, ":", "");
	boost::replace_all(fileName, "\n", "");
	boost::replace_all(fileName, " ", "_");
	fs.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs << "P3" << std::endl;
	std::string size = std::to_string(m_map->getSize());
	fs << size << " " << size << std::endl;
	fs << "255" << std::endl;
	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap()))[i].size(); ++j) {
			if ((*(m_map->getMap()))[j][i]->hasRiver()) {
				fs << "0 0 255" << "	";
			}
			else if ((*(m_map->getMap()))[j][i]->hasRoad()) {
				fs << "0 0 0" << "	";
			}
			else {
				if ((*(m_map->getMap()))[j][i]->getType().compare("blank") == 0) {
					fs << "255 20 147" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("city") == 0) {
					fs << "115 115 115" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("town") == 0) {
					fs << "153 76 0" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("rural") == 0) {
					fs << "0 255 0" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("mountain") == 0) {
					fs << "255 255 255" << "	";
				}
			}
		}
		fs << std::endl;
	}
	fs.close();
}

void MapUtilities::visualiseMapWithPathAsPpm(MapTile* start, MapTile* end, std::list<MapTile*> path) {
	std::fstream fs;
	std::string fileName = datePretty() + "_mapPathOutput.ppm";
	boost::replace_all(fileName, ":", "");
	boost::replace_all(fileName, "\n", "");
	boost::replace_all(fileName, " ", "_");
	fs.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs << "P3" << std::endl;
	std::string size = std::to_string(m_map->getSize());
	fs << size << " " << size << std::endl;
	fs << "255" << std::endl;
	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap()))[i].size(); ++j) {
			if (std::find(path.begin(), path.end(), (*(m_map->getMap()))[j][i]) != path.end()) {
				fs << "255 0 0" << "	";
			}
			else {
				if ((*(m_map->getMap()))[j][i]->hasRiver()) {
					fs << "0 0 255" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("blank") == 0) {
					fs << "0 0 0" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("city") == 0) {
					fs << "115 115 115" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("town") == 0) {
					fs << "153 76 0" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("rural") == 0) {
					fs << "0 255 0" << "	";
				} else if ((*(m_map->getMap()))[j][i]->getType().compare("mountain") == 0) {
					fs << "0 0 0" << "	";
				}
			}
		}
		fs << std::endl;
	}
	fs.close();
}

std::string MapUtilities::getDateTimeNow() {
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(p);
	return std::ctime(&t);
}

void MapUtilities::printPath(std::list<MapTile*> path) {
	for (int i = 0; i < (*(m_map->getMap())).size(); ++i) {
		for (int j = 0; j < (*(m_map->getMap())).at(i).size(); ++j) {
			if (std::find(path.begin(), path.end(), (*(m_map->getMap()))[j][i]) != path.end()) {
				std::cout << "X ";
			}
			else {
				std::cout << "O ";
			}
		}
		std::cout << std::endl;
	}
}

MapTile* MapUtilities::getTileAt(int x, int y) {
	return (*(m_map->getMap()))[x][y];
}

std::string MapUtilities::datePretty()
{
	std::string date = getDateTimeNow();
	std::vector<std::string> parts = split(date, ' ');
	std::vector<std::string> timeParts = split(parts[3], ':');
	std::string year = "";
	for (int i = 0; i < 4; i++) {
		year += parts[4].at(i);
	}
	std::string betterOutput = year + "-" + convertMonth(parts[1]) + "-" + parts[2] + "_" + parts[0] + "_" + timeParts[0] + timeParts[1] + timeParts[2];
	return betterOutput;
}

GameMap * MapUtilities::getMapReference()
{
	return m_map;
}

bool MapUtilities::tilesAreAdjacent(MapTile * a, MapTile * b)
{
	std::vector<MapTile*> neighbours = getNeighbouringTiles(a);
	for (int i = 0; i < neighbours.size(); ++i) {
		if (neighbours[i] == b) {
			return true;
		}
	}
	return false;
}

std::vector<std::string> MapUtilities::split(std::string s, char c) {
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

std::string MapUtilities::convertMonth(std::string month) {
	std::string monthInt = "0";
	if (month.compare("Jan") == 0) {
		monthInt = "1";
	}
	else if (month.compare("Feb") == 0) {
		monthInt = "2";
	}
	else if (month.compare("Mar") == 0) {
		monthInt = "3";
	}
	else if (month.compare("Apr") == 0) {
		monthInt = "4";
	}
	else if (month.compare("May") == 0) {
		monthInt = "5";
	}
	else if (month.compare("Jun") == 0) {
		monthInt = "6";
	}
	else if (month.compare("Jul") == 0) {
		monthInt = "7";
	}
	else if (month.compare("Aug") == 0) {
		monthInt = "8";
	}
	else if (month.compare("Sep") == 0) {
		monthInt = "9";
	}
	else if (month.compare("Oct") == 0) {
		monthInt = "10";
	}
	else if (month.compare("Nov") == 0) {
		monthInt = "11";
	}
	else if (month.compare("Dec") == 0) {
		monthInt = "12";
	}
	return monthInt;
}

std::list<MapTile*> MapUtilities::generateBezierCurve(MapTile* start, MapTile* end, bool quadratic) {
	//bezier curve - https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/BezierCurve.gif/240px-BezierCurve.gif
	double dist = getEuclideanDistance(start, end);
	std::list<MapTile*> path;
	MapTile* actualMidpoint = getMidPoint(start, end);
	if (quadratic) {
		MapTile* q1Point = getMidPoint(start, actualMidpoint);
		MapTile* q2Point = getMidPoint(actualMidpoint, end);
		int xDisplacement1 = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		int yDisplacement1 = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		int xDisplacement2 = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		int yDisplacement2 = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		while ((q1Point->getX() + xDisplacement1) < 0) {
			xDisplacement1++;
		}
		while ((q1Point->getX() + xDisplacement1) >= getMapSize()) {
			xDisplacement1--;
		}
		while ((q1Point->getY() + yDisplacement1) < 0) {
			yDisplacement1++;
		}
		while ((q1Point->getY() + yDisplacement1) >= getMapSize()) {
			yDisplacement1--;
		}
		while ((q2Point->getX() + xDisplacement2) < 0) {
			xDisplacement2++;
		}
		while ((q2Point->getX() + xDisplacement2) >= getMapSize()) {
			xDisplacement2--;
		}
		while ((q2Point->getY() + yDisplacement2) < 0) {
			yDisplacement2++;
		}
		while ((q2Point->getY() + yDisplacement2) >= getMapSize()) {
			yDisplacement2--;
		}
		MapTile* p2 = getTileAt((q1Point->getX() + xDisplacement1), (q1Point->getY() + yDisplacement1));
		MapTile* p3 = getTileAt((q2Point->getX() + xDisplacement2), (q2Point->getY() + yDisplacement2));

		path = cubicBezier(start, p2, p3, end);
	}
	else {
		int xDisplacement = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		int yDisplacement = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		while ((actualMidpoint->getX() + xDisplacement) < 0) {
			xDisplacement++;
		}
		while ((actualMidpoint->getX() + xDisplacement) >= getMapSize()) {
			xDisplacement--;
		}
		while ((actualMidpoint->getY() + yDisplacement) < 0) {
			yDisplacement++;
		}
		while ((actualMidpoint->getY() + yDisplacement) >= getMapSize()) {
			yDisplacement--;
		}
		MapTile* p2 = getTileAt((actualMidpoint->getX() + xDisplacement), (actualMidpoint->getY() + yDisplacement));
		path = quadraticBezier(start, p2, end);
	}
	return path;
}

std::list<MapTile*> MapUtilities::quadraticBezier(MapTile* p1, MapTile* p2, MapTile* p3) {
	std::list<MapTile*> path;
	for (float i = 0; i < 1; i += 0.01) {
		//generate line between lines
		double linePoint1X = p1->getX() + ((p2->getX() - p1->getX()) * i);
		double linePoint1Y = p1->getY() + ((p2->getY() - p1->getY()) * i);
		double linePoint2X = p2->getX() + ((p3->getX() - p2->getX()) * i);
		double linePoint2Y = p2->getY() + ((p3->getY() - p2->getY()) * i);

		//get bezier curve point
		double bPointX = linePoint1X + ((linePoint2X - linePoint1X) * i);
		double bPointY = linePoint1Y + ((linePoint2Y - linePoint1Y) * i);

		int x = (int)bPointX;
		int y = (int)bPointY;
		if (std::find(path.begin(), path.end(), getTileAt(x, y)) == path.end()) {
			path.push_back(getTileAt(x, y));
		}
	}
	return path;
}

std::list<MapTile*> MapUtilities::cubicBezier(MapTile* p1, MapTile* p2, MapTile* p3, MapTile* p4) {
	std::list<MapTile*> path;
	for (float i = 0; i < 1; i += 0.01) {
		//generate lines between lines
		double linePoint1X = p1->getX() + ((p2->getX() - p1->getX()) * i);
		double linePoint1Y = p1->getY() + ((p2->getY() - p1->getY()) * i);
		double linePoint2X = p2->getX() + ((p3->getX() - p2->getX()) * i);
		double linePoint2Y = p2->getY() + ((p3->getY() - p2->getY()) * i);
		double linePoint3X = p3->getX() + ((p4->getX() - p3->getX()) * i);
		double linePoint3Y = p3->getY() + ((p4->getY() - p3->getY()) * i);

		//generate line between above lines
		double bPointX1 = linePoint1X + ((linePoint2X - linePoint1X) * i);
		double bPointY1 = linePoint1Y + ((linePoint2Y - linePoint1Y) * i);
		double bPointX2 = linePoint2X + ((linePoint3X - linePoint2X) * i);
		double bPointY2 = linePoint2Y + ((linePoint3Y - linePoint2Y) * i);

		//get bezier curve point
		double bPointX = bPointX1 + ((bPointX2 - bPointX1) * i);
		double bPointY = bPointY1 + ((bPointY2 - bPointY1) * i);

		int x = (int)bPointX;
		int y = (int)bPointY;
		if (std::find(path.begin(), path.end(), getTileAt(x, y)) == path.end()) {
			path.push_back(getTileAt(x, y));
		}
	}
	return path;
}

MapTile* MapUtilities::findEmptySpot() {
	initialiseWeights();
	calculateWeights();

	//to prevent circular clustering, get top 3? tiers of tile weights 
	//select randomly from these merged tiers

	int maxWeight = getMaxWeight();
	std::unordered_set<MapTile*> possibleTiles;
	for (int i = 0; i < 3; ++i) {
		std::unordered_set<MapTile*> currentTier = getTilesWithWeight((maxWeight - i), false);
		for (std::unordered_set<MapTile*>::iterator it = currentTier.begin(); it != currentTier.end(); ++it) {
			possibleTiles.insert((*it));
		}
	}
	//std::unordered_set<MapTile*> possibleTiles = getTilesWithWeight(0, true);


	//could pick town by checking which tile has neighbours with highest weights
	int randIndex = getRandomNumber(0, (possibleTiles.size() - 1));
	std::unordered_set<MapTile*>::iterator it(possibleTiles.begin());
	advance(it, randIndex);
	return (*it);
}

std::vector<MapTile*> MapUtilities::getPartitionBoundary(std::vector<MapTile*> partition) {
	if (partition.size() < 3) {
		//convex hull not possible (or already achieved when ya think about it)
		return partition;
	}
	std::sort(partition.begin(),partition.end(),
		[](MapTile* lhs, MapTile* rhs) {
			return lhs->getX() < rhs->getX();
		}
	);
	m_hull.clear();
	MapTile* minX = (*partition.begin()); //get min x tile
	MapTile* maxX = (partition.back()); //get max x tile
	/*
		//sort on any property in place
		std::sort(objs.begin(),
          objs.end(),
          [](const MyClass& lhs, const MyClass& rhs)
			{
			    return lhs.value < rhs.value;
			});

			[](const MapTile& lhs, const MapTile& rhs)
			{
			return lhs.getX() < rhs.getX();
			});
	*/
	quickHull(partition, minX, maxX, 1);
	quickHull(partition, minX, maxX, -1);

	return m_hull;
}

//quickhull algorithm
//takes in set of maptiles (ie a partition of city)
//returns a set of maptiles representing the outermost boundary of the partition
//going to need to get all partitions, check for neighbouring partitions and select boundary from one of them as road (ie one side of boundary where partitions neighbour each other)
void MapUtilities::quickHull(std::vector<MapTile*> partition, MapTile* a, MapTile* b, int side) {
	MapTile* furthestPoint = NULL;
	int maxDistance = 0;

	for (int i = 0; i < partition.size(); ++i) {
		int distance = distanceFromLine(a, b, partition[i]);
		if ((findSide(a, b, partition[i]) == side) && (distance > maxDistance)) {
			furthestPoint = partition[i];
			maxDistance = distance;
		}
	}

	if (furthestPoint == NULL) {
		m_hull.push_back(a);
		m_hull.push_back(b);
		return;
	}

	quickHull(partition, furthestPoint, a, -findSide(furthestPoint,a,b));
	quickHull(partition, furthestPoint, b, -findSide(furthestPoint, b, a));
}

int MapUtilities::distanceFromLine(MapTile* p1, MapTile* p2, MapTile* point) {
	return abs((point->getY() - p1->getY())*(p2->getX() - p1->getX()) - (p2->getY() - p1->getY())*(point->getX() - p1->getX()));
}

int MapUtilities::findSide(MapTile* p1, MapTile* p2, MapTile* point) {
	int aboveLine = (point->getY() - p1->getY())*(p2->getX() - p1->getX()) - (p2->getY() - p1->getY())*(point->getX() - p1->getX());
	if (aboveLine == 0) {
		return 0;
	}
	return (aboveLine > 0) ? 1 : -1;
}