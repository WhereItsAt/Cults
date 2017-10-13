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
#include "City.h"
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
    virtual void relinquish(GoverningBody* enemy);
    void addSuburb(Suburb* burb);
    void addRegion(RegionalZone* rz);
    void addCountry(Country* cnt);
    void addCity(City* city);
    void setEmpire(Empire* emp);
    void setHomeLand(Zone* home);
    void setBase(Base* hq);
    Suburb* removeSuburb(Suburb* burb);
    RegionalZone* removeRegion(RegionalZone* rz);
    Country* removeCountry(Country* cnt);
    City* removeCity(City* city);
    Empire* getEmpire();
    Zone* getHomeLand();
    Base* getHQ();
private:
    Empire* m_empire;
    std::list<Suburb*> m_suburbs;
    std::list<RegionalZone*> m_regions;
    std::list<Country*> m_countries;
    std::list<City*> m_cities;
    Zone* m_homeland;
    Base* m_hq;
};

#endif /* ZONEMANAGER_H */

