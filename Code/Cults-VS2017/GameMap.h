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
#include "River.h"
#include "Mountain.h"
#include "City.h"
#include "Town.h"
#include "MapUtilities.h"
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <list>

class GameMap {
public:
	GameMap();
	GameMap(int size);
	GameMap(const GameMap& orig);
	virtual ~GameMap();
	//overall map functions
	void generateMap();
	void setRuralArea();
	void initializeGameMap(int size);
	int getSize();
	std::vector< std::vector<MapTile*> >* getMap();	
	MapUtilities * getController();
	//town functions
	void generateAllTowns();
	//feature functions
	void generateRivers(int numberOfRivers, int minDistance);
	void generateMountains(int numberOfMountains);
	std::list<MapTile*> generateBezierCurve(MapTile * start, MapTile * end, bool quadratic);
	std::list<MapTile*> quadraticBezier(MapTile * p1, MapTile * p2, MapTile * p3);
	std::list<MapTile*> cubicBezier(MapTile * p1, MapTile * p2, MapTile * p3, MapTile * p4);
	std::vector<MapTile*> voroniDiagramSolution(MapTile * start, MapTile * end);

private:
	int m_size;
	const int m_defaultSize = 50;
	int m_townMinSize;
	int m_townMaxSize;
	std::vector< std::vector<MapTile*> > m_gameMap;
	int m_totalTiles;
	int m_cityTileMax;
	int m_townTileMax;
	int m_ruralTileCount;
	int m_maxTowns;
	int m_minTowns;
	std::vector<River*> m_rivers;
	std::vector<Mountain*> m_mountains;
	std::vector<Town*> m_towns;
	City* m_city;
	MapUtilities* m_mapController;
};

#endif /* GAMEMAP_H */
