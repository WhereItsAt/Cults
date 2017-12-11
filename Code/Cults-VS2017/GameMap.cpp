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
	m_cityTileCount = 0;
	m_townTileMax = 0.2 * m_totalTiles;
	m_townTileCount = 0;
	m_totalTownCount = 0;
	m_ruralTileCount = 0;
	m_townMinSize = m_size * 0.5;
	m_townMaxSize = m_size * 1.5;
	m_maxTowns = (m_townTileMax / 2) / m_townMinSize;
	m_minTowns = (m_townTileMax / 2) / m_townMaxSize;
	//m_maxTowns = 20;
	//m_minTowns = 10;
	int x = 0;
}

GameMap::GameMap(const GameMap& orig) {

}

GameMap::~GameMap() {

}

void GameMap::printMap() {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			MapTile* tempTile = m_gameMap[j][i];
			std::cout << tempTile->getType() << ", "; /*<< "(" << tempTile->getX() << "," << tempTile->getY() << "); "*/
		}
		std::cout << std::endl;
	}
}

void GameMap::printOnly(std::string type) {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			MapTile* tempTile = m_gameMap[j][i];
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

MapTile* GameMap::getMiddle() {
	MapTile* mid = m_gameMap[m_size / 2][m_size / 2];
	return mid;
}

void GameMap::generateCityCenter() {
	/*
	MASSIVE REWORK HERE
	find vertexes using same formula for distance,
	then randomly shift north and south horizontally,
	and randomly shift east and west vertically.
	need to meet a minimum distance between vertexes

	still need to generate a path between center and vertexes
	then the boundary and fill functions should still work
	- may need to tweak the fill function calls in generatecityboundaries
	- start with city center, get all neighbours and fill from all the ones that arent city tiles
	- if a tile is in the queue that gets filled from the call on a neighbour in the same quadrant
	- then finish as job is already done

	also while were on the subject of refactoring
	increase the starting weight on boundary tiles to like 3 to shift towns outwards a bit ey
	stop em bunching up in a circle around the city as much ey
	specially the corners ey, maybe weight them up a bit more ey
	*/



	//set center tile to city
	MapTile* midPoint = this->getMiddle();
	m_cityCenter = midPoint;
	midPoint->setType("city");
	m_cityTileCount++;
	midPoint->setRoad(true);
	//generate average city "radius" ie length from center to edge
	int cityRadius = m_size / 4;
	//iterate in 4 directions, ie north/south/east/west
	for (int i = 0; i < 4; ++i) {
		//generate random length to change radius by with 50/50 odds of shrinking or growing
		int radiusChange = getRandomNumber(0, (m_size / 8));
		if (getRandomNumber(0, 6) == 0) {
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
	std::cout << "	-generating city now *build* *build* *build*" << std::endl;
	generateCity();
	std::cout << "	-finished generating city *hoorah*" << std::endl;
	setRuralArea();
	std::cout << "	-generating towns now *build* *build* *build*" << std::endl;
	generateAllTowns();
	std::cout << "	-finished generating towns *hoorah*" << std::endl;
	int numberOfRivers = getRandomNumber(0, 3);
	int numberOfMountainRanges = getRandomNumber(0, 3);
	//use town generation method for mountain ranges
	//use bezier curves to generate rivers
	std::cout << "	-generating rivers now *woosh* *woosh* *woosh*" << std::endl;
	generateRivers(getRandomNumber(1, 3), (m_size / 1.5));
	std::cout << "	-finished generating rivers *hoorah*" << std::endl;
	//use voroni diagrams for road
}

void GameMap::generateCity() {
	generateCityCenter();
	generateCityBoundaries();
	//fillCity()
	//reduceCity()
}

void GameMap::reduceCity() {

}

void GameMap::fillCity(std::list<MapTile*> boundary, MapTile* startPosition) {
	std::list<MapTile*> validNeighbours = { startPosition };
	std::unordered_set<MapTile*> visited;
	while (!validNeighbours.empty()) {
		MapTile* current = validNeighbours.front();
		current->setTileType(TileType::City);
		current->setType("city");
		current->setWeight(-1);
		m_cityTileCount++;
		validNeighbours.pop_front();
		visited.insert(current);
		std::vector<MapTile*> neighbours = getNonDiagonallyAdjacentNeighbours(current);
		for (int i = 0; i < neighbours.size(); ++i) {
			MapTile* temp = neighbours.at(i);
			if ((neighbours.at(i)->getType().compare("city") != 0) && (visited.find(neighbours.at(i)) == visited.end())) {
				if (std::find(validNeighbours.begin(), validNeighbours.end(), neighbours.at(i)) == validNeighbours.end()) {
					validNeighbours.push_back(neighbours.at(i));
				}
			}
		}
	}
}

void GameMap::generateCityBoundaries() {
	/*std::list<MapTile*> p1 = aStar(m_cityNorthVertex, m_cityEastVertex);
	std::list<MapTile*> p2 = aStar(m_cityEastVertex, m_citySouthVertex);
	std::list<MapTile*> p3 = aStar(m_citySouthVertex, m_cityWestVertex);
	std::list<MapTile*> p4 = aStar(m_cityWestVertex, m_cityNorthVertex);*/
	//to fix path intersecting axis we are going to have to pass a parameter indicating which quadrant we are in
	//then add checks so that the x/y co-ordinates dont meet the axis
	std::list<MapTile*> p1 = recursivePathSolution(m_cityNorthVertex, m_cityEastVertex, m_pathThreshold, m_moveRange, 1);
	std::list<MapTile*> p2 = recursivePathSolution(m_cityEastVertex, m_citySouthVertex, m_pathThreshold, m_moveRange, 2);
	std::list<MapTile*> p3 = recursivePathSolution(m_citySouthVertex, m_cityWestVertex, m_pathThreshold, m_moveRange, 3);
	std::list<MapTile*> p4 = recursivePathSolution(m_cityWestVertex, m_cityNorthVertex, m_pathThreshold, m_moveRange, 4);

	//convert to city tiles here
	std::vector<std::list<MapTile*> > collection = { p1, p2, p3, p4 };
	for (int i = 0; i < collection.size(); ++i) {
		for (std::list<MapTile*>::iterator it = collection.at(i).begin(); it != collection.at(i).end(); ++it) {
			if (((*it)->getTileType() != TileType::City) && ((*it)->getType().compare("city") != 0)) {
				m_cityTileCount++;
			}
			(*it)->setTileType(TileType::City);
			(*it)->setType("city");
			(*it)->setWeight(-1);
		}
	}

	//change this when generatecitycenter is refactored						<<<
	fillCity(p1, m_gameMap[(m_cityCenter->getX() + 1)][(m_cityCenter->getY() - 1)]);
	fillCity(p2, m_gameMap[(m_cityCenter->getX() + 1)][(m_cityCenter->getY() + 1)]);
	fillCity(p3, m_gameMap[(m_cityCenter->getX() - 1)][(m_cityCenter->getY() + 1)]);
	fillCity(p4, m_gameMap[(m_cityCenter->getX() - 1)][(m_cityCenter->getY() - 1)]);

	//std::vector<std::list<MapTile*> > collection = { p1, p2, p3, p4 };
	//for (int i = 0; i < collection.size(); ++i) {
	//	for (std::list<MapTile*>::iterator it = collection.at(i).begin(); it != collection.at(i).end(); ++it) {
	//		if (((*it)->getTileType() != TileType::City) && ((*it)->getType().compare("city") != 0)) {
	//			m_cityTileCount++;
	//		}
	//		(*it)->setTileType(TileType::City);
	//		(*it)->setType("city");
	//		(*it)->setWeight(-1);
	//		int x = (*it)->getX();
	//		switch (i) {
	//		case 0:
	//			//north -> east, spread south/west
	//			for (int i = (*it)->getY(); i < m_cityCenter->getY(); ++i) {
	//				m_gameMap[x][i]->setTileType(TileType::City);
	//				m_gameMap[x][i]->setType("city");
	//				m_gameMap[x][i]->setWeight(-1);
	//			}
	//			break;
	//		case 1:
	//			//east -> south, spread spread north/west
	//			for (int i = (*it)->getY(); i > m_cityCenter->getY(); --i) {
	//				m_gameMap[x][i]->setTileType(TileType::City);
	//				m_gameMap[x][i]->setType("city");
	//				m_gameMap[x][i]->setWeight(-1);
	//			}
	//			break;
	//		case 2:
	//			//south -> west, spread north/east
	//			for (int i = (*it)->getY(); i > m_cityCenter->getY(); --i) {
	//				m_gameMap[x][i]->setTileType(TileType::City);
	//				m_gameMap[x][i]->setType("city");
	//				m_gameMap[x][i]->setWeight(-1);
	//			}
	//			break;
	//		case 3:
	//			//west -> north, spread south/east
	//			for (int i = (*it)->getY(); i < m_cityCenter->getY(); ++i) {
	//				m_gameMap[x][i]->setTileType(TileType::City);
	//				m_gameMap[x][i]->setType("city");
	//				m_gameMap[x][i]->setWeight(-1);
	//			}
	//			break;
	//		default:
	//			//shouldnt get here
	//			std::cerr << "error filling town" << std::endl;
	//			break;
	//		}
	//	}
	//}

	//convert to city tiles here
	//std::vector<std::list<MapTile*> > collection = { p1, p2, p3, p4 };
	//for (int i = 0; i < collection.size(); ++i) {
	//	for (std::list<MapTile*>::iterator it = collection.at(i).begin(); it != collection.at(i).end(); ++it) {
	//		if (((*it)->getTileType() != TileType::City) && ((*it)->getType().compare("city") != 0)) {
	//			m_cityTileCount++;
	//		}
	//		(*it)->setTileType(TileType::City);
	//		(*it)->setType("city");
	//		(*it)->setWeight(-1);
	//	}
	//}
	//fill in city up to path (boundary)
	//east
	//for (int i = m_cityCenter->getX() + 1; i < m_cityEastVertex->getX(); ++i) {
	//	//north
	//	for (int j = m_cityCenter->getY() - 1; j > m_cityNorthVertex->getY(); --j) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		} else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//	//south
	//	for (int j = m_cityCenter->getY() + 1; j < m_citySouthVertex->getY(); ++j) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//}
	////west
	//for (int i = m_cityCenter->getX() - 1; i > m_cityWestVertex->getX(); --i) {
	//	//north
	//	for (int j = m_cityCenter->getY() - 1; j > m_cityNorthVertex->getY(); --j) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//	//south
	//	for (int j = m_cityCenter->getY() + 1; j < m_citySouthVertex->getY(); ++j) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//}
	//
	//repeat process from north and south going out horizontally to fill in gaps.
	////north
	//for (int j = m_cityCenter->getY() - 1; j > m_cityNorthVertex->getY(); --j) {
	//	//west
	//	for (int i = m_cityCenter->getX() - 1; i > m_cityWestVertex->getX(); --i) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//	//east
	//	for (int i = m_cityCenter->getX() + 1; i < m_cityEastVertex->getX(); ++i) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//}
	////south
	//for (int j = m_cityCenter->getY() + 1; j < m_citySouthVertex->getY(); ++j) {
	//	//west
	//	for (int i = m_cityCenter->getX() - 1; i > m_cityWestVertex->getX(); --i) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//	//east
	//	for (int i = m_cityCenter->getX() + 1; i < m_cityEastVertex->getX(); ++i) {
	//		if (m_gameMap[i][j]->getType().compare("city") == 0) {
	//			break;
	//		}
	//		else {
	//			m_gameMap[i][j]->setType("city");
	//			m_gameMap[i][j]->setTileType(TileType::City);
	//			m_gameMap[i][j]->setWeight(-1);
	//		}
	//	}
	//}
}

std::vector<MapTile*> GameMap::selectCityBoundaryPoints(MapTile* start, MapTile* end) {
	std::vector<MapTile*> boundaryPoints;

	//need to find series of points between vertexes
	//number of points determined by distance between vertexes
	//ie larger distances will have more points and more intricate paths
	//ie smaller cities will trend towards more circular/diamond shapes, whereas larger ones will appear more polygonal
	//need to ensure path will not cross itself
	//could be achieved by always picking points that only increase/decrease along x or y axis <- could lead to predicatable paths
	//maybe path crossing itself isnt such a big deal since it will get filled in anyway
	//make the next point selection based on distance from previous point, until it gets within that distance of the end point

	//astar with random obstacles inserted







	return boundaryPoints;
}

std::list<MapTile*> GameMap::recursivePathSolution(MapTile* start, MapTile* end, int threshold, int moveRange, int quadrant) {
	//generate straight line, find midpoint and move it, generate subsequent lines, find half way point of those lines, rinse and repeat...
	std::list<MapTile*> path;
	if (getEuclideanDistance(start, end) < threshold) {
		//call astar between points and return path
		path = aStar(start, end);
		return path;
	}
	else {
		//capture midpoint, move it, call recursivepath on both halves then join the results and return it
		MapTile* midpoint = getMidPoint(start, end);

		int randomXDisplacement = getRandomNumber((-1 * moveRange), moveRange);
		int randomYDisplacement = getRandomNumber((-1 * moveRange), moveRange);

		if ((midpoint->getX() + randomXDisplacement) < 0 || (midpoint->getX() + randomXDisplacement) >= m_size) {
			randomXDisplacement = 0;
		}

		if ((midpoint->getY() + randomYDisplacement) < 0 || (midpoint->getY() + randomYDisplacement) >= m_size) {
			randomYDisplacement = 0;
		}

		int startX = start->getX();
		int startY = start->getY();
		int endX = end->getX();
		int endY = end->getY();
		int potentialX = midpoint->getX() + randomXDisplacement;
		int potentialY = midpoint->getY() + randomYDisplacement;

		switch (quadrant) {
		case 1:
			//north -> east - keep x greater than startX and less than endX, keep y less than endY and greater than startY
			while (potentialX <= startX) {
				randomXDisplacement++;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialX >= endX) {
				randomXDisplacement--;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialY >= endY) {
				randomYDisplacement--;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			while (potentialY <= startY) {
				randomYDisplacement++;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			break;
		case 2:
			//east -> south - keep x greater than eastX and less than southX, keep y greater than eastY and less than southY
			while (potentialX >= startX) {
				randomXDisplacement--;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialX <= endX) {
				randomXDisplacement++;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialY >= endY) {
				randomYDisplacement--;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			while (potentialY <= startY) {
				randomYDisplacement++;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			break;
		case 3:
			//south -> west - keep x greater than westX and less than southX, keep y less than southY and greater than westY
			while (potentialX <= endX) {
				randomXDisplacement++;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialX >= startX) {
				randomXDisplacement--;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialY <= endY) {
				randomYDisplacement++;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			while (potentialY >= startY) {
				randomYDisplacement--;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			break;
		case 4:
			//west -> north - keep x greater than westX and less than northX, keep y greater than northY and less than westY
			while (potentialX <= startX) {
				randomXDisplacement++;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialX >= endX) {
				randomXDisplacement--;
				potentialX = midpoint->getX() + randomXDisplacement;
			}
			while (potentialY <= endY) {
				randomYDisplacement++;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			while (potentialY >= startY) {
				randomYDisplacement--;
				potentialY = midpoint->getY() + randomYDisplacement;
			}
			break;
		default:
			//should never occur
			std::cerr << "incorrect parameter 'quadrant' pass to function 'recursivePathSolution'" << std::endl;
			break;
		}

		MapTile* newMidpoint = m_gameMap[(midpoint->getX() + randomXDisplacement)][(midpoint->getY() + randomYDisplacement)];
		path = recursivePathSolution(start, newMidpoint, threshold, moveRange, quadrant);
		std::list<MapTile*> secondPath = recursivePathSolution(newMidpoint, end, threshold, moveRange, quadrant);
		path.splice(path.end(), secondPath);
	}
	return path;
}

MapTile* GameMap::getMidPoint(MapTile* start, MapTile* end) {
	MapTile* midpoint = start;
	if (start->getX() > end->getX() && start->getY() > end->getY()) {
		//start is south east of end
		midpoint = m_gameMap[end->getX() + ((start->getX() - end->getX()) / 2)][end->getY() + ((start->getY() - end->getY()) / 2)];
	}
	else if (start->getX() < end->getX() && start->getY() < end->getY()) {
		//start is north west of end
		midpoint = m_gameMap[start->getX() + ((end->getX() - start->getX()) / 2)][start->getY() + ((end->getY() - start->getY()) / 2)];
	}
	else if (start->getX() > end->getX() && start->getY() < end->getY()) {
		//start is north east of end
		midpoint = m_gameMap[end->getX() + ((start->getX() - end->getX()) / 2)][start->getY() + ((end->getY() - start->getY()) / 2)];
	}
	else if (start->getX() < end->getX() && start->getY() > end->getY()) {
		//start is south west of end
		midpoint = m_gameMap[start->getX() + ((end->getX() - start->getX()) / 2)][end->getY() + ((start->getY() - end->getY()) / 2)];
	}
	return midpoint;
}

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
		//get two points on different boundaries
		//partition distance in 2
		//get midpoint (slightly closer to one point than the other)
		//generate 2 bezier curves from each point to the midpoint
		//cubic bezier in the larger partition and a quadratic bezier curve in the smaller
		std::vector<MapTile*> result;
		enum Edge { N, E, S, W };
		std::vector<Edge> boundaries = { N, E, S, W };
		Edge e1, e2;
		int index = getRandomNumber(0, (boundaries.size() - 1));
		std::vector<Edge>::iterator it = (boundaries.begin() + index);
		e1 = (*it);
		boundaries.erase(it);
		index = getRandomNumber(0, (boundaries.size() - 1));
		it = (boundaries.begin() + index);
		e2 = (*it);
		boundaries.erase(it);
		MapTile *start, *mid, *end;
		start = getRandomBoundaryTile(e1, 0);
		end = getRandomBoundaryTile(e2, getStartingPointShiftValue(e1, e2, start, minDistance));
		//decide if first half or second half is going to be bigger/cubic or smaller/quadratic bezier curve
		bool startIsQuadratic = (getRandomNumber(2, 3) == 2);
		//pick meeting point of both halfs
		int xHalfway = (start->getX() + end->getX()) / 2;
		int yHalfway = (start->getY() + end->getY()) / 2;
		int xPoint, yPoint;
		if (start->getX() < end->getX()) {
			xPoint = start->getX() + xHalfway;
		}
		else {
			xPoint = end->getX() + xHalfway;
		}
		if (xPoint >= m_size) {
			xPoint = m_size - 1;
		}
		else if (xPoint < 0) {
			xPoint = 0;
		}
		if (start->getY() < end->getY()) {
			yPoint = start->getY() + yHalfway;
		}
		else {
			yPoint = end->getY() + yHalfway;
		}
		if (yPoint >= m_size) {
			yPoint = m_size - 1;
		}
		else if (yPoint < 0) {
			yPoint = 0;
		}
		MapTile* midpoint = getRandomTileInRange(m_gameMap[xPoint][yPoint], 10);
		//add points to vector and return it
		result = { start, midpoint, end };
		std::list<MapTile*> river1 = generateBezierCurve(start, midpoint, startIsQuadratic);
		std::list<MapTile*> river2 = generateBezierCurve(midpoint, end, (!startIsQuadratic));
		int fsadsdsdf = 0;
		for (std::list<MapTile*>::iterator it = river1.begin(); it != river1.end(); ++it) {
			(*it)->setRiver(true);
		}
		for (std::list<MapTile*>::iterator it = river2.begin(); it != river2.end(); ++it) {
			(*it)->setRiver(true);
		}
	}
}

std::list<MapTile*> GameMap::generateBezierCurve(MapTile* start, MapTile* end, bool quadratic) {
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
		while ((q1Point->getX() + xDisplacement1) >= m_size) {
			xDisplacement1--;
		}
		while ((q1Point->getY() + yDisplacement1) < 0) {
			yDisplacement1++;
		}
		while ((q1Point->getY() + yDisplacement1) >= m_size) {
			yDisplacement1--;
		}
		while ((q2Point->getX() + xDisplacement2) < 0) {
			xDisplacement2++;
		}
		while ((q2Point->getX() + xDisplacement2) >= m_size) {
			xDisplacement2--;
		}
		while ((q2Point->getY() + yDisplacement2) < 0) {
			yDisplacement2++;
		}
		while ((q2Point->getY() + yDisplacement2) >= m_size) {
			yDisplacement2--;
		}
		MapTile* p2 = m_gameMap[q1Point->getX() + xDisplacement1][q1Point->getY() + yDisplacement1];
		MapTile* p3 = m_gameMap[q2Point->getX() + xDisplacement2][q2Point->getY() + yDisplacement2];

		path = cubicBezier(start, p2, p3, end);
	}
	else {
		int xDisplacement = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		int yDisplacement = getRandomNumberInRangePositiveOrNegative((0.3*dist), (0.55*dist), 0.5);
		while ((actualMidpoint->getX() + xDisplacement) < 0) {
			xDisplacement++;
		}
		while ((actualMidpoint->getX() + xDisplacement) >= m_size) {
			xDisplacement--;
		}
		while ((actualMidpoint->getY() + yDisplacement) < 0) {
			yDisplacement++;
		}
		while ((actualMidpoint->getY() + yDisplacement) >= m_size) {
			yDisplacement--;
		}
		MapTile* p2 = m_gameMap[actualMidpoint->getX() + xDisplacement][actualMidpoint->getY() + yDisplacement];
		path = quadraticBezier(start, p2, end);
	}
	return path;
}

int GameMap::getRandomNumberInRangePositiveOrNegative(int num1, int num2, float chanceToFlip) {
	int result = getRandomNumber(num1, num2);
	if (getRandomNumber(0, 100) < (100 * chanceToFlip)) {
		result *= -1;
	}
	return result;
}

std::list<MapTile*> GameMap::quadraticBezier(MapTile* p1, MapTile* p2, MapTile* p3) {
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
		if (std::find(path.begin(), path.end(), m_gameMap[x][y]) == path.end()) {
			path.push_back(m_gameMap[x][y]);
		}
	}
	return path;
}

std::list<MapTile*> GameMap::cubicBezier(MapTile* p1, MapTile* p2, MapTile* p3, MapTile* p4) {
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
		if (std::find(path.begin(), path.end(), m_gameMap[x][y]) == path.end()) {
			path.push_back(m_gameMap[x][y]);
		}
	}
	return path;
}
/*
std::vector<MapTile*> GameMap::getRiverPoints(int minDistance) {
std::vector<MapTile*> result;
enum Edge {N, E, S, W};
std::vector<Edge> boundaries = { N, E, S, W };
Edge e1, e2;
int index = getRandomNumber(0, (boundaries.size() - 1));
std::vector<Edge>::iterator it = (boundaries.begin() + index);
e1 = (*it);
boundaries.erase(it);
index = getRandomNumber(0, (boundaries.size() - 1));
it = (boundaries.begin() + index);
e2 = (*it);
boundaries.erase(it);
MapTile *start, *mid, *end;
start = getRandomBoundaryTile(e1, 0);
end = getRandomBoundaryTile(e2, getStartingPointShiftValue(e1, e2, start, minDistance));
//decide if first half or second half is going to be bigger/cubic or smaller/quadratic bezier curve
bool startIsQuadratic = (getRandomNumber(2, 3) == 2);
//pick meeting point of both halfs
int xHalfway = (start->getX() + end->getX()) / 2;
int yHalfway = (start->getY() + end->getY()) / 2;
int xPoint, yPoint;
if (start->getX() < end->getX()) {
xPoint = start->getX() + xHalfway;
} else {
xPoint = end->getX() + xHalfway;
}
if (xPoint >= m_size) {
xPoint = m_size - 1;
}
else if (xPoint < 0) {
xPoint = 0;
}
if (start->getY() < end->getY()) {
yPoint = start->getY() + yHalfway;
} else {
yPoint = end->getY() + yHalfway;
}
if (yPoint >= m_size) {
yPoint = m_size - 1;
}
else if (yPoint < 0) {
yPoint = 0;
}
MapTile* midpoint = getRandomTileInRange(m_gameMap[xPoint][yPoint], 10);
//add points to vector and return it
result = { start, midpoint, end };
std::list<MapTile*> river1 = generateBezierCurve(start,midpoint,startIsQuadratic);
std::list<MapTile*> river2 = generateBezierCurve(start, midpoint, (!startIsQuadratic));
return result;
}
*/
MapTile* GameMap::getRandomBoundaryTile(int edge, int startingPoint) {
	MapTile* result = NULL;
	//N = {x,y=0}, E = {x=m_size-1,y}, S = {x=m_size-1,y}, W = {x=0,y}
	int randomX, randomY;
	switch (edge) {
	case 0:
		randomX = getRandomNumber(startingPoint, (m_size - 1));
		result = m_gameMap[randomX][0];
		break;
	case 1:
		randomY = getRandomNumber(startingPoint, (m_size - 1));
		result = m_gameMap[(m_size - 1)][randomY];
		break;
	case 2:
		randomX = getRandomNumber(startingPoint, (m_size - 1));
		result = m_gameMap[randomX][(m_size - 1)];
		break;
	case 3:
		randomY = getRandomNumber(startingPoint, (m_size - 1));
		result = m_gameMap[0][randomY];
		break;
	default:
		//shouldnt happen
		break;
	}
	return result;
}

MapTile* GameMap::getRandomTileInRange(MapTile* tile, int range) {
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

int GameMap::getStartingPointShiftValue(int startEdge, int endEdge, MapTile* start, int minDistance) {
	//find how far along end edge to shift starting point to meet min distance value
	int result = 0;
	int x, y;
	MapTile* end;
	switch (endEdge) {
	case 0:
		x = 0;
		end = m_gameMap[x][0];
		while (getEuclideanDistance(start, end) < minDistance) {
			x++;
			end = m_gameMap[x][0];
		}
		result = x;
		break;
	case 1:
		y = 0;
		end = m_gameMap[(m_size - 1)][y];
		while (getEuclideanDistance(start, end) < minDistance) {
			y++;
			end = m_gameMap[(m_size - 1)][y];
		}
		result = y;
		break;
	case 2:
		x = 0;
		end = m_gameMap[x][(m_size - 1)];
		while (getEuclideanDistance(start, end) < minDistance) {
			x++;
			end = m_gameMap[x][(m_size - 1)];
		}
		result = x;
		break;
	case 3:
		y = 0;
		end = m_gameMap[0][y];
		while (getEuclideanDistance(start, end) < minDistance) {
			y++;
			end = m_gameMap[0][y];
		}
		result = y;
		break;
	default:
		//shouldnt happen
		break;
	}
	return result;
}

void GameMap::test() {

}

std::list<MapTile*> GameMap::aStar(MapTile* start, MapTile* end) {
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
		//std::unordered_set<MapTile*> bestNeighbours = getTilesWithWeight(0, true, neighbours);
		std::map<int, std::unordered_set<MapTile*> > adjustedWeights;
		//for (std::unordered_set<MapTile*>::iterator it = bestNeighbours.begin(); it != bestNeighbours.end(); ++it) {
		for (std::unordered_set<MapTile*>::iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
			//adjustedWeights.insert(std::make_pair(((*it)->getWeight() - 1),(*it)));
			adjustedWeights[((*it)->getWeight() - getEuclideanDistance((*it), center))].insert((*it));
		}
		std::vector<int> keys;
		for (std::map<int, std::unordered_set<MapTile*> >::iterator it = adjustedWeights.begin(); it != adjustedWeights.end(); ++it) {
			keys.push_back(it->first);
		}
		int max = *max_element(keys.begin(), keys.end());
		std::unordered_set<MapTile*> bestNeighbours = adjustedWeights[max];
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

std::vector<MapTile*> GameMap::getNeighbouringTiles(MapTile* tile, bool startOnTileBelow) {
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
		if (((tX + (deltas.at(i).first)) >= 0) && ((tX + (deltas.at(i).first)) < m_size) && ((tY + (deltas.at(i).second)) >= 0) && ((tY + (deltas.at(i).second)) < m_size)) {
			//std::cout << "old x: " << tX << ", old y: " << tY << ". new x: " << (tX + (deltas.at(i).first)) << ", new y: " << (tY + (deltas.at(i).second)) << std::endl;
			//neighbours.push_back(m_gameMap[(tY + (deltas.at(i).second))][(tX + (deltas.at(i).first))]);
			neighbours.push_back(m_gameMap[(tX + (deltas.at(i).first))][(tY + (deltas.at(i).second))]);
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

std::vector<MapTile*> GameMap::getNonDiagonallyAdjacentNeighbours(MapTile* tile) {
	std::vector<MapTile*> neighbours;
	std::vector<std::pair<int, int> > deltas = { std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, 1), std::make_pair(0, -1) };
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
			//fs << m_gameMap[i][j]->getType() << ",";
			fs << "(" << m_gameMap[i][j]->getX() << "," << m_gameMap[i][j]->getY() << ");";
		}
		fs << std::endl;
	}
	fs.close();
}

void GameMap::visualiseMapAsPpm() {
	std::fstream fs;
	std::string fileName = getDateTimeNow() + "_mapOutput.ppm";
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
			if (m_gameMap[j][i]->hasRiver()) {
				fs << "0 0 255" << "	";
			}
			else {
				if (m_gameMap[j][i]->getType().compare("blank") == 0) {
					fs << "255 0 0" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("city") == 0) {
					fs << "115 115 115" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("town") == 0) {
					fs << "153 76 0" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("rural") == 0) {
					fs << "0 255 0" << "	";
				}
			}
		}
		fs << std::endl;
	}
	fs.close();
}

void GameMap::visualiseMapWithPathAsPpm(MapTile* start, MapTile* end, std::list<MapTile*> path) {
	std::fstream fs;
	std::string fileName = getDateTimeNow() + "_mapPathOutput.ppm";
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
			if (std::find(path.begin(), path.end(), m_gameMap[j][i]) != path.end()) {
				fs << "255 0 0" << "	";
			}
			else {
				if (m_gameMap[j][i]->hasRiver()) {
					fs << "0 0 255" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("blank") == 0) {
					fs << "0 0 0" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("city") == 0) {
					fs << "115 115 115" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("town") == 0) {
					fs << "153 76 0" << "	";
				}
				else if (m_gameMap[j][i]->getType().compare("rural") == 0) {
					fs << "0 255 0" << "	";
				}
			}
		}
		fs << std::endl;
	}
	fs.close();
}

std::string GameMap::getDateTimeNow() {
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(p);
	return std::ctime(&t);
}

void GameMap::printPath(std::list<MapTile*> path) {
	for (int i = 0; i < m_gameMap.size(); ++i) {
		for (int j = 0; j < m_gameMap.at(i).size(); ++j) {
			if (std::find(path.begin(), path.end(), m_gameMap[j][i]) != path.end()) {
				std::cout << "X ";
			}
			else {
				std::cout << "O ";
			}
		}
		std::cout << std::endl;
	}
}

MapTile* GameMap::getTileAt(int x, int y) {
	return m_gameMap[x][y];
}

int main(int ac, char** av) {
	std::srand(time(0));

	std::cout << "creating map now" << std::endl;
	GameMap testMap = GameMap(100);
	std::cout << "finished creating map" << std::endl;

	std::cout << "generating map now" << std::endl;
	testMap.generateMap();
	std::cout << "finished generating map" << std::endl;
	//testMap.printMap();

	//MapTile* a = new MapTile("blank", false, 10, 20);
	//MapTile* b = new MapTile("city", true, 10, 20);
	//MapTile* c = new MapTile("blank", false, 15, 45);
	//MapTile* d = new MapTile("blank", false, 12, 90);
	//MapTile* e = new MapTile("blank", false, 12, 90);
	//
	//std::cout << a->toString() << " == " << b->toString() << "? " << ((*a == *b) ? "true" : "false") << std::endl;
	//std::cout << a->toString() << " == " << c->toString() << "? " << ((*a == *c) ? "true" : "false") << std::endl;
	//std::cout << a->toString() << " == " << d->toString() << "? " << ((*a == *d) ? "true" : "false") << std::endl;
	//std::cout << e->toString() << " == " << d->toString() << "? " << ((*e == *d) ? "true" : "false") << std::endl;

	//testMap.PrintToFile("gameMap_Output.txt");
	std::cout << "Writing map to image file" << std::endl;
	testMap.visualiseMapAsPpm();
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
