/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapTile.cpp
 * Author: scott
 * 
 * Created on 4 June 2017, 12:37 AM
 */

#include "MapTile.h"
#include <iostream>

MapTile::MapTile() {
}

MapTile::MapTile(std::string type, bool road) {
	m_hasRoad = road;
	m_stringType = type;
	m_type = translateStringToType(type);
}

MapTile::MapTile(std::string type, bool road, int x, int y) {
	m_hasRoad = road;
	m_stringType = type;
	m_type = translateStringToType(type);
	m_x = x;
	m_y = y;
}

MapTile::MapTile(const MapTile& orig) {
}

MapTile::~MapTile() {
}

std::string MapTile::getType() {
	return m_stringType;
}

void MapTile::setType(std::string type) {
	m_stringType = type;
	m_type = translateStringToType(type);
}

bool MapTile::hasRoad() {
	return m_hasRoad;
}

void MapTile::setRoad(bool road) {
	m_hasRoad = road;
}

int MapTile::getX() {
	return m_x;
}

int MapTile::getY() {
	return m_y;
}

void MapTile::printTile() {
	std::cout << m_stringType << "-(" << m_x << "," << m_y << ")";
}

TileType::t_tileType MapTile::getTileType() {
	return m_type;
}

void MapTile::setTileType(TileType::t_tileType tt) {
	m_type = tt;
}

TileType::t_tileType MapTile::translateStringToType(std::string type) {
	if (type.compare("blank") == 0) {
		return TileType::Blank;
	} else if (type.compare("city") == 0) {
		return TileType::City;
	} else if (type.compare("town") == 0) {
		return TileType::Town;
	} else if (type.compare("rural") == 0) {
		return TileType::Rural;
	}
	return TileType::Blank;
}

std::string MapTile::translateTypeToString(TileType::t_tileType type) {
	int t = type;
	switch (t) {
		case 0:
			return "blank";
		case 1:
			return "city";
		case 2:
			return "town";
		case 3:
			return "rural";
		default:
			return "blank";
	}
}