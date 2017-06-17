/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Base.cpp
 * Author: scott
 * 
 * Created on 4 June 2017, 12:35 AM
 */

#include "Base.h"

Base::Base() {
}

Base::Base(const Base& orig) {
}

Base::~Base() {
}

Zone* Base::getZone() {
    return m_homeZone;
}

void Base::setZone(Zone* home) {
    m_homeZone = home;
}

void Base::collectFromBuildings() {
    //iterate through list of buildings and call operate on them
    //operate function in building will allocate resources to owner
}

void Base::addBuilding(Building* build) {
    m_buildings.push_back(build);
}

void Base::removeBuilding(Building* build) {
    m_buildings.remove(build);
}

void Base::replaceBuilding(Building* oldBuild, Building* newBuild) {
    Base::removeBuilding(oldBuild);
    Base::addBuilding(newBuild);
}

//change this to return pointer to list
std::list<Building*> Base::getBuildings() {
    return m_buildings;
}