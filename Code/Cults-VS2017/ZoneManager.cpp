/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneManager.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 5:41 PM
 */

#include "ZoneManager.h"

ZoneManager::ZoneManager() {
}

ZoneManager::ZoneManager(const ZoneManager& orig) {
}

ZoneManager::~ZoneManager() {
}

void ZoneManager::addCity(City* city) {
    m_cities.push_back(city);
}

void ZoneManager::addCountry(Country* cnt) {
    m_countries.push_back(cnt);
}

void ZoneManager::addRegion(RegionalZone* rz) {
    m_regions.push_back(rz);
}

void ZoneManager::addSuburb(Suburb* burb) {
    m_suburbs.push_back(burb);
}

Empire* ZoneManager::getEmpire() {
    return m_empire;
}

Base* ZoneManager::getHQ() {
    return m_hq;
}

Zone* ZoneManager::getHomeLand() {
    return m_homeland;
}

void ZoneManager::relinquish(GoverningBody* enemy) {
    //zones
    //see notes in follower manager
}

City* ZoneManager::removeCity(City* city) {
    m_cities.remove(city);
    return city;
}

Country* ZoneManager::removeCountry(Country* cnt) {
    m_countries.remove(cnt);
    return cnt;
}

RegionalZone* ZoneManager::removeRegion(RegionalZone* rz) {
    m_regions.remove(rz);
    return rz;
}

Suburb* ZoneManager::removeSuburb(Suburb* burb) {
    m_suburbs.remove(burb);
    return burb;
}

void ZoneManager::setBase(Base* hq) {
    m_hq = hq;
}

void ZoneManager::setEmpire(Empire* emp) {
    m_empire = emp;
}

void ZoneManager::setHomeLand(Zone* home) {
    m_homeland = home;
}
