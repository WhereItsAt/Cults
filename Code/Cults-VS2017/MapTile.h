/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapTile.h
 * Author: scott
 *
 * Created on 4 June 2017, 12:37 AM
 */

#ifndef MAPTILE_H
#define MAPTILE_H

#include <string>
#include "TileType.h"

class MapTile {
	public:
		MapTile();
		MapTile(std::string type, bool road);
		MapTile(std::string type, bool road, int x, int y);
		MapTile(const MapTile& orig);
		virtual ~MapTile();
		std::string getType();
		void setType(std::string type);
		bool hasRoad();
		void setRoad(bool road);
		int getX();
		int getY();
		int peekX() const;
		int peekY() const;
		void printTile();
		void setTileType(TileType::t_tileType tt);
		TileType::t_tileType translateStringToType(std::string type);
		std::string translateTypeToString(TileType::t_tileType type);
		TileType::t_tileType getTileType();
		bool operator<(const MapTile& rhs) const;
		bool operator==(const MapTile & rhs) const;
	
	private:
		bool m_hasRoad;
		std::string m_stringType;
		TileType::t_tileType m_type;
		int m_x;
		int m_y;
};

#endif /* MAPTILE_H */

