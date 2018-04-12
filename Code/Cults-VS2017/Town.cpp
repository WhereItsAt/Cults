#include "Town.h"
#include <map>
#include <algorithm>


Town::Town(MapUtilities * controller, int size)
{
	m_mapController = controller;
	m_center = m_mapController->findEmptySpot();
	generateTown(m_center, size);
}

Town::~Town()
{
}

void Town::generateTown(MapTile* center, int size) {
	center->setType("town");
	int townTileCount = 1; //track this towns tiles
	std::unordered_set<MapTile*> townTiles = { center };
	std::unordered_set<MapTile*> neighbours;

	while (townTileCount <= size) {
		std::unordered_set<MapTile*>::iterator townTileIterator;
		for (townTileIterator = townTiles.begin(); townTileIterator != townTiles.end(); ++townTileIterator) {
			std::vector<MapTile*> newNeighbours = m_mapController->getNeighbouringTiles((*townTileIterator));
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
			adjustedWeights[((*it)->getWeight() - m_mapController->getEuclideanDistance((*it), center))].insert((*it));
		}
		std::vector<int> keys;
		for (std::map<int, std::unordered_set<MapTile*> >::iterator it = adjustedWeights.begin(); it != adjustedWeights.end(); ++it) {
			keys.push_back(it->first);
		}
		int max = *max_element(keys.begin(), keys.end());
		std::unordered_set<MapTile*> bestNeighbours = adjustedWeights[max];
		int randIndex = m_mapController->getRandomNumber(0, (bestNeighbours.size() - 1));
		std::unordered_set<MapTile*>::iterator it = bestNeighbours.begin();
		advance(it, randIndex);
		MapTile* townExpansion = (*it);
		townExpansion->setType("town");
		townExpansion->setTileType(TileType::Town);
		townExpansion->setWeight(-1);
		townTiles.insert(townExpansion);
		neighbours.erase(townExpansion);
		townTileCount++;
	}

	m_townTiles = townTiles;
}

MapTile * Town::getTownCenter()
{
	return m_center;
}

int Town::getTownSize()
{
	return m_townTiles.size();
}
