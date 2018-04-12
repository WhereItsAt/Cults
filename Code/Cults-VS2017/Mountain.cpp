#include "Mountain.h"


Mountain::Mountain(MapUtilities* controller)
{
	m_mapController = controller;
	int mountainRangeSize = m_mapController->getRandomNumber(2, 4);
	MapTile* center = m_mapController->findEmptySpot();
	m_center = center;
	generateMountain(m_center);
}


Mountain::~Mountain()
{
}

void Mountain::generateMountain(MapTile* center)
{
	//use same method as town generation, limited to mountain min/max size
	//possibly make single mountains and/or mountain ranges
	
	//for number of mountains in mountain range
	//generate center point for each mountain, with mountain width as distance between points (get point in range function)
	//connect center points with a line, at each mountain center bloom outwards
	center->setTileType(TileType::Mountain);
	center->setType("mountain");
	m_tiles.insert(center);
	std::vector<MapTile*> neighbours = m_mapController->getNeighbouringTiles(center);
	for (int i = 0; i < neighbours.size(); ++i) {
		if ((neighbours[i]->getTileType() != TileType::City) && (neighbours[i]->getTileType() != TileType::Town)) {
			neighbours[i]->setTileType(TileType::Mountain);
			neighbours[i]->setType("mountain");
			m_tiles.insert(neighbours[i]);
		}
	}
	if ((center->getY() - m_radius) >= 0) {
		MapTile* north = m_mapController->getTileAt(center->getX(), (center->getY() - m_radius));
		if ((north->getTileType() != TileType::City) && (north->getTileType() != TileType::Town)) {
			north->setTileType(TileType::Mountain);
			north->setType("mountain"); 
			m_tiles.insert(north);
		}
	}
	if ((center->getX() + m_radius) < m_mapController->getMapSize()) {
		MapTile* east = m_mapController->getTileAt((center->getX() + m_radius), center->getY());
		if ((east->getTileType() != TileType::City) && (east->getTileType() != TileType::Town)) {
			east->setTileType(TileType::Mountain);
			east->setType("mountain");
			m_tiles.insert(east);
		}
	}
	if ((center->getY() + m_radius) < m_mapController->getMapSize()) {
		MapTile* south = m_mapController->getTileAt(center->getX(), (center->getY() + m_radius));
		if ((south->getTileType() != TileType::City) && (south->getTileType() != TileType::Town)) {
			south->setTileType(TileType::Mountain);
			south->setType("mountain");
			m_tiles.insert(south);
		}
	}
	if ((center->getX() - m_radius) >= 0) {
		MapTile* west = m_mapController->getTileAt((center->getX() - m_radius), center->getY());
		if ((west->getTileType() != TileType::City) && (west->getTileType() != TileType::Town)) {
			west->setTileType(TileType::Mountain);
			west->setType("mountain");
			m_tiles.insert(west);
		}
	}
	

}
