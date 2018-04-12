#include "City.h"
#include <iostream>
#include <set>
#include <map>


City::City()
{
}

City::City(std::vector<std::vector<MapTile*>>* gameMap, MapUtilities* controller)
{
	m_map = gameMap;
	m_mapController = controller;
	generateCity();
}


City::~City()
{

}

void City::generateCity() {
	generateCityAxis();
	generateCityBoundaries();
	generateRoads(m_numberOfVoroniPoints);
}

void City::generateCityAxis() {
	//generate average city "radius" ie length from center to edge
	int cityRadius = (*m_map).size() / 4;
	int vertexHorizontalShiftValue, vertexVerticalShiftValue, x, y;
	enum Direction { North, East, South, West };
	std::vector<Direction> directions = { North, East, South, West };

	MapTile* midPoint = m_mapController->getMiddle();
	m_cityCenter = midPoint;
	midPoint->setType("city");
	midPoint->setRoad(true);
	m_cityTiles.insert(midPoint);

	for (int i = 0; i < directions.size(); ++i) {
		switch (directions.at(i)) {
		case 0:
			//generate random length to change radius by with 1/6 odds of shrinking, 5/6 odds of growing
			vertexVerticalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 8));
			if (m_mapController->getRandomNumber(1, 4) == 1) {
				vertexVerticalShiftValue *= -1;
			}
			vertexHorizontalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 12));
			if (m_mapController->getRandomNumber(1, 2) == 1) {
				vertexHorizontalShiftValue *= -1;
			}
			x = midPoint->getX() + vertexHorizontalShiftValue;
			y = midPoint->getY() - (cityRadius + vertexVerticalShiftValue);
			m_northVertex = (*m_map)[x][y];
			m_northVertex->setType("city");
			m_northVertex->setTileType(TileType::City);
			m_cityTiles.insert(m_northVertex);
			break;
		case 1:
			vertexVerticalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 12));
			if (m_mapController->getRandomNumber(1, 2) == 1) {
				vertexVerticalShiftValue *= -1;
			}
			vertexHorizontalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 8));
			if (m_mapController->getRandomNumber(1, 4) == 1) {
				vertexHorizontalShiftValue *= -1;
			}
			x = midPoint->getX() + cityRadius + vertexHorizontalShiftValue;
			y = midPoint->getY() + vertexVerticalShiftValue;
			m_eastVertex = (*m_map)[x][y];
			m_eastVertex->setType("city");
			m_eastVertex->setTileType(TileType::City);
			m_cityTiles.insert(m_eastVertex);
			break;
		case 2:
			vertexVerticalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 8));
			if (m_mapController->getRandomNumber(1, 4) == 1) {
				vertexVerticalShiftValue *= -1;
			}
			vertexHorizontalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 12));
			if (m_mapController->getRandomNumber(1, 2) == 1) {
				vertexHorizontalShiftValue *= -1;
			}
			x = midPoint->getX() + vertexHorizontalShiftValue;
			y = midPoint->getY() + cityRadius + vertexVerticalShiftValue;
			m_southVertex = (*m_map)[x][y];
			m_southVertex->setType("city");
			m_southVertex->setTileType(TileType::City);
			m_cityTiles.insert(m_southVertex);
			break;
		case 3:
			vertexVerticalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 12));
			if (m_mapController->getRandomNumber(1, 2) == 1) {
				vertexVerticalShiftValue *= -1;
			}
			vertexHorizontalShiftValue = m_mapController->getRandomNumber(0, ((*m_map).size() / 8));
			if (m_mapController->getRandomNumber(1, 4) == 1) {
				vertexHorizontalShiftValue *= -1;
			}
			x = midPoint->getX() - (cityRadius + vertexHorizontalShiftValue);
			y = midPoint->getY() + vertexVerticalShiftValue;
			m_westVertex = (*m_map)[x][y];
			m_westVertex->setType("city");
			m_westVertex->setTileType(TileType::City);
			m_cityTiles.insert(m_westVertex);
			break;
		default:
			//shouldnt happen
			break;
		}
	}
}

void City::fillCity(MapTile* startPosition) {
	std::list<MapTile*> validNeighbours = { startPosition };
	std::unordered_set<MapTile*> visited;
	while (!validNeighbours.empty()) {
		MapTile* current = validNeighbours.front();
		current->setTileType(TileType::City);
		current->setType("city");
		current->setWeight(-1);
		m_cityTiles.insert(current);
		validNeighbours.pop_front();
		visited.insert(current);
		std::vector<MapTile*> neighbours = m_mapController->getNonDiagonallyAdjacentNeighbours(current);
		//std::vector<MapTile*> neighbours = getNeighbouringTiles(current);
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

void City::generateCityBoundaries() {
	std::list<MapTile*> p1 = recursivePathSolution(m_northVertex, m_eastVertex, m_pathThreshold, m_moveRange, 1);
	std::list<MapTile*> p2 = recursivePathSolution(m_eastVertex, m_southVertex, m_pathThreshold, m_moveRange, 2);
	std::list<MapTile*> p3 = recursivePathSolution(m_southVertex, m_westVertex, m_pathThreshold, m_moveRange, 3);
	std::list<MapTile*> p4 = recursivePathSolution(m_westVertex, m_northVertex, m_pathThreshold, m_moveRange, 4);

	std::vector<std::list<MapTile*> > collection = { p1, p2, p3, p4 };
	for (int i = 0; i < collection.size(); ++i) {
		for (std::list<MapTile*>::iterator it = collection.at(i).begin(); it != collection.at(i).end(); ++it) {
			(*it)->setTileType(TileType::City);
			(*it)->setType("city");
			m_cityTiles.insert((*it));
			(*it)->setWeight(-1);
		}
	}

	fillCity(m_cityCenter);
	m_boundary.splice(m_boundary.end(), p1);
	m_boundary.splice(m_boundary.end(), p2);
	m_boundary.splice(m_boundary.end(), p3);
	m_boundary.splice(m_boundary.end(), p4);
}

std::list<MapTile*> City::recursivePathSolution(MapTile* start, MapTile* end, int threshold, int moveRange, int quadrant) {
	//generate straight line, find midpoint and move it, generate subsequent lines, find half way point of those lines, rinse and repeat...
	std::list<MapTile*> path;
	if (m_mapController->getEuclideanDistance(start, end) < threshold) {
		//call astar between points and return path
		path = m_mapController->aStar(start, end);
		return path;
	}
	else {
		//capture midpoint, move it, call recursivepath on both halves then join the results and return it
		MapTile* midpoint = m_mapController->getMidPoint(start, end);

		int randomXDisplacement = m_mapController->getRandomNumber((-1 * moveRange), moveRange);
		int randomYDisplacement = m_mapController->getRandomNumber((-1 * moveRange), moveRange);

		if ((midpoint->getX() + randomXDisplacement) < 0 || (midpoint->getX() + randomXDisplacement) >= m_mapController->getMapSize()) {
			randomXDisplacement = 0;
		}

		if ((midpoint->getY() + randomYDisplacement) < 0 || (midpoint->getY() + randomYDisplacement) >= m_mapController->getMapSize()) {
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

		MapTile* newMidpoint = (*m_map)[(midpoint->getX() + randomXDisplacement)][(midpoint->getY() + randomYDisplacement)];
		path = recursivePathSolution(start, newMidpoint, threshold, moveRange, quadrant);
		std::list<MapTile*> secondPath = recursivePathSolution(newMidpoint, end, threshold, moveRange, quadrant);
		path.splice(path.end(), secondPath);
	}
	return path;
}

int City::getCityTileCount()
{
	return m_cityTiles.size();
}

void City::generateRoads(int numPoints)
{
	//grab numPoints random points in city
	//assign each point to a "partition"
	//grow each partition be grabbing neighbouring points that do not belong to a partition
	//when no more points can be assigned, set partition boundaries to be roads

	//the vector of partitions which are composed of: a vector of levels where the first is the center and the last is the boundary, where a level is: a vector of neighbouring tiles
	std::vector<std::vector<std::vector<MapTile*> > > partitions;
	std::map<MapTile*, bool> partitionTileMap;


	//generate random indexes of city tiles to fetch
	std::set<int> randomIndexes;
	while (randomIndexes.size() < numPoints) {
		int index = m_mapController->getRandomNumber(0, m_cityTiles.size());
		randomIndexes.insert(index);
	}
	
	//fetch city tiles at randomly determined indexes
	int i = 0;
	for (std::unordered_set<MapTile*>::iterator it = m_cityTiles.begin(); it != m_cityTiles.end(); it++) {
		if (randomIndexes.find(i) != randomIndexes.end()) {
			std::vector<MapTile*> level1 = { (*it) };
			std::vector<std::vector<MapTile*> > tempPartition = { level1 };
			partitions.push_back(tempPartition);
			partitionTileMap.insert(std::pair<MapTile*,bool>((*it), true));
		} else {
			partitionTileMap.insert(std::pair<MapTile*, bool>((*it), false));
		}
		i++;
	}

	//getting the boundary of a partition from a set of all its points will be a challenge
	//need to represent each partition as a series of levels - https://i.makeagif.com/media/10-16-2013/62MYPf.mp4
	//when setting the road we just use the final level of a partition (making sure not to do the same on its neighbouring partition so as to not have "double roads")
	/*
	  * pseudocode:
		* while(at least one map value is false) {
		* 	visit each partition once {
		* 		get last level of partition {
		* 			set next level = all neighbouring unclaimed tiles
		* 			partition.add(next level)
		* 		}
		* 	}
		* }
	  *
	*/


	//road generation is stopping as soon as any partitions meet, move hasneighbours logic outside of lastlevel for loop************
	//std::unordered_set<MapTile*> roadTiles;

	bool finished = false;
	std::set<int> completedPartitionIndexes;
	while (!finished) {
		for (int i = 0; i < partitions.size(); ++i) {
			if (std::find(completedPartitionIndexes.begin(), completedPartitionIndexes.end(), i) == completedPartitionIndexes.end()) {
				int lastLevelIndex = partitions[i].size() - 1;
				std::vector<MapTile*> lastLevel = partitions[i][lastLevelIndex];
				std::vector<MapTile*> nextLevel;
				bool hasFreeNeighbours = false;
				for (int j = 0; j < lastLevel.size(); ++j) {
					std::vector<MapTile*> neighbours = m_mapController->getNeighbouringTiles(lastLevel[j]);
					for (int k = 0; k < neighbours.size(); ++k) {
						if (m_cityTiles.find(neighbours[k]) != m_cityTiles.end()) {
							if (!partitionTileMap[neighbours[k]]) {
								partitionTileMap[neighbours[k]] = true;
								nextLevel.push_back(neighbours[k]);
								hasFreeNeighbours = true;
							}
						}
					}
				}
				if (!hasFreeNeighbours) {
					completedPartitionIndexes.insert(i);
				}
				partitions[i].push_back(nextLevel);
			}
		}

		//check to see if were finished (no unclaimed tiles)
		/*bool foundUnclaimedTile = false;
		for (std::map<MapTile*, bool>::iterator it = partitionTileMap.begin(); it != partitionTileMap.end(); ++it) {
			if (!it->second) {
				foundUnclaimedTile = true;
			}
		}
		if (!foundUnclaimedTile) {
			finished = true;
		}*/
		if (completedPartitionIndexes.size() == partitions.size()) {
			finished = true;
		}

	}

	for (int i = 0; i < partitions.size(); ++i) {
		std::vector<MapTile*> currentPartition;
		for (int j = 0; j < partitions[i].size(); ++j) {
			currentPartition.insert(currentPartition.end(), partitions[i][j].begin(), partitions[i][j].end());
		}
		std::vector<MapTile*> boundary = m_mapController->getPartitionBoundary(currentPartition);
		for (int k = 0; k < boundary.size()-1; ++k) {
			std::list<MapTile*> path = m_mapController->aStar(boundary[k], boundary[k + 1]);
			for (std::list<MapTile*>::iterator it = path.begin(); it != path.end(); ++it) {
				(*it)->setRoad(true);
			}
		}
	}


	//the boundary wont be enough to capture the road
	//we need to build and maintain a path
	//we need to capture a tile when we find it neighbours a partitioned tile

	//for each partition
		//for each layer
			//for each tile
				//for each neighbour of tile
					//if neighbour is a city tile, and not within this partition
					//add original tile to set of road tiles
	//for (int i = 0; i < partitions.size(); ++i) {
	//	for (int j = 0; j < partitions[i].size(); ++j) {
	//		for (int k = 0; k < partitions[i][j].size(); ++k) {
	//			std::vector<MapTile*> neighbours = m_mapController->getNeighbouringTiles(partitions[i][j][k]);
	//			for (int l = 0; l < neighbours.size(); ++l) {
	//				if (m_cityTiles.find(neighbours[l]) != m_cityTiles.end()) {
	//					//if (std::find(neighbours[i][j]))
	//				}
	//			}
	//		}
	//	}
	//}
	

	//visit partitions and set tiles in outer layers to have roads
	/*for (int i = 0; i < partitions.size(); ++i) {
		std::vector<MapTile*> boundary = partitions[i][(partitions[i].size() - 1)];
		for (int j = 0; j < boundary.size(); ++j) {
			boundary[j]->setRoad(true);
		}
	}*/
}