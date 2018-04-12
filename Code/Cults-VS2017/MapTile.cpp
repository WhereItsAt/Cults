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

bool MapTile::hasRiver()
{
	return m_hasRiver;
}

void MapTile::setRiver(bool river)
{
	m_hasRiver = river;
}

int MapTile::getX() {
	return m_x;
}

int MapTile::getY() {
	return m_y;
}

int MapTile::getWeight() {
	return m_weight;
}
void MapTile::setWeight(int weight) {
	m_weight = weight;
}

int MapTile::peekX() const {
	return m_x;
}

int MapTile::peekY() const {
	return m_y;
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
	} else if (type.compare("mountain") == 0) {
		return TileType::Mountain;
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
		case 4:
			return "mountain";
		default:
			return "blank";
	}
}

bool MapTile::operator<(const MapTile& rhs) const
{
	return ((m_x < rhs.peekX()) && (m_y < rhs.peekY()));
}

bool MapTile::operator==(const MapTile& rhs) const
{
	return ((m_x == rhs.peekX()) && (m_y == rhs.peekY()));
}

std::string MapTile::toString() 
{
	return ("type: " + m_stringType + ". has road: " + (m_hasRoad ? "true " : "false ") + ". has river: " + (m_hasRiver ? "true" : "false") + " at: (" + std::to_string(m_x) + "," + std::to_string(m_y) + ")");
}