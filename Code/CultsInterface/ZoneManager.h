/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:41 PM
 */

#ifndef ZONEMANAGER_H
#define ZONEMANAGER_H

#include <list>
#include "myCity.h"
#include "Manager.h"
#include "Empire.h"
#include "Suburb.h"
#include "RegionalZone.h"
#include "Country.h"
#include "Base.h"
#include "Zone.h"

//class City;
//class Suburb;
//class RegionalZone;
//class Country;

class ZoneManager: public Manager {
public:
    ZoneManager();
    ZoneManager(const ZoneManager& orig);
    virtual ~ZoneManager();
    //virtual void relinquish(GoverningBody* enemy);
    void addSuburb(Suburb* burb);
    void addRegion(RegionalZone* rz);
    void addCountry(Country* cnt);
    void addCity(myCity* city);
    Suburb* removeSuburb(Suburb* burb);
    RegionalZone* removeRegion(RegionalZone* rz);
    Country* removeCountry(Country* cnt);
    myCity* removeCity(myCity* city);
private:
    Empire* empire;
    std::list<Suburb*> suburbs;
    std::list<RegionalZone*> regions;
    std::list<Country*> countries;
    std::list<myCity*> cities;
    Zone* homeland;
    Base* hq;
};

#endif /* ZONEMANAGER_H */

