/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameMap.h
 * Author: scott
 *
 * Created on 4 June 2017, 12:37 AM
 */

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "MapTile.h"
#include <vector>
#include <string>
#include <set>

class GameMap {
	public:
		GameMap();
		GameMap(int size);
		GameMap(const GameMap& orig);
		virtual ~GameMap();
		void printMap();
		MapTile* getMiddle();
		void generateCityCenter();
		void generateMap();
		void printOnly(std::string type);
		void generateCity();
		void reduceCity();
		void generateTown(MapTile* center, int size);
		std::vector<MapTile*> getMaxWeightTiles(std::set<MapTile*> candidates);
		void generateAllTowns();
		void findPath(MapTile* start, MapTile* end);
		void countTilesFor(std::string type);
		MapTile * getNextTownCenter();
		void setRuralArea();
		void initializeGameMap(int size);
		std::vector<MapTile*> getNeighbouringTiles(MapTile* tile);
		int getRandomNumber(int min, int max);
		
	private:
		int m_size;
		const int m_defaultSize = 25;
		const int m_townMinSize = 10;
		const int m_townMaxSize = 25;
		std::vector< std::vector<MapTile*> > m_gameMap;
		int m_totalTiles;
		int m_cityTileMax;
		int m_cityTileCount;
		int m_townTileMax;
		int m_townTileCount;
		int m_townCount;
		int m_totalTownCount;
		int m_ruralTileCount;
		int m_maxTowns;
		int m_minTowns;
		std::vector<MapTile*> townCenters;
		MapTile* m_cityNorthVertex;
		MapTile* m_citySouthVertex;
		MapTile* m_cityWestVertex;
		MapTile* m_cityEastVertex;
		int** m_currentWeights;
    
};

#endif /* GAMEMAP_H */

