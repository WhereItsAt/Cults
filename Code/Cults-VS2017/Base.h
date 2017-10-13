/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Base.h
 * Author: scott
 *
 * Created on 4 June 2017, 12:35 AM
 */

#ifndef BASE_H
#define BASE_H

#include <list>
#include "Assett.h"
#include "Zone.h"
//#include "Building.h"

class Building;

class Base: public Assett {
public:
    Base();
    Base(const Base& orig);
    virtual ~Base();
    virtual void upgrade() = 0;
    Zone* getZone();
    void setZone(Zone* home);
    void collectFromBuildings();
    void addBuilding(Building* build);
    void removeBuilding(Building* build);
    void replaceBuilding(Building* oldBuild, Building* newBuild);
    std::list<Building*> getBuildings();
protected:
     Zone* m_homeZone;
     std::list<Building*> m_buildings;
private:

};

#endif /* BASE_H */

