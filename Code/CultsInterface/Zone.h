/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zone.h
 * Author: scott
 *
 * Created on 3 June 2017, 8:31 PM
 */

#ifndef ZONE_H
#define ZONE_H

#include <map>
#include <list>
#include "GoverningBody.h"

class Zone {
public:
    Zone();
    Zone(const Zone& orig);
    virtual ~Zone();
    GoverningBody* getCurrentRuler();
    void setCurrentRuler(GoverningBody* gbody);
    Zone* getParentZone();
    void setParentZone(Zone* parent);
    std::list<Zone*> getChildZones();
    void addChildZone(Zone* child);
    Zone* removeChildZone(Zone* child);
    int getPopulation();
    void setPopulation(int pop);
    int getFollowerCount(GoverningBody* gbod);
    void transferFollowers(GoverningBody* recruiter, GoverningBody* loser, int amount);
    virtual std::string getType() = 0;
protected: 
    GoverningBody* m_currentRuler;
    int m_population;
    std::map<GoverningBody*,int> m_cultFollowers;
    Zone* m_parentZone;
    std::list<Zone*> m_childZones;
private:

};

#endif /* ZONE_H */

