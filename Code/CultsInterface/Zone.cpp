/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zone.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 8:31 PM
 */

#include "Zone.h"
#include "Assett.h"

Zone::Zone() {
}

Zone::Zone(const Zone& orig) {
}

Zone::~Zone() {
}

GoverningBody* Zone::getCurrentRuler() {
    return m_currentRuler;
}

void Zone::setCurrentRuler(GoverningBody* gbody) {
    m_currentRuler = gbody;
}

Zone* Zone::getParentZone() {
    return m_parentZone;
}

void Zone::setParentZone(Zone* parent) {
    m_parentZone = parent;
}

std::list<Zone*> Zone::getChildZones() {
    return m_childZones;
}

void Zone::addChildZone(Zone* child) {
    m_childZones.push_back(child);
}

Zone* Zone::removeChildZone(Zone* child) {
    m_childZones.remove(child);
    return child;
}

int Zone::getPopulation() {
    return m_population;
}

void Zone::setPopulation(int pop) {
    m_population = pop;
}

int Zone::getFollowerCount(GoverningBody* gbod) {
    std::map<GoverningBody*,int>::iterator it;
    it = m_cultFollowers.find(gbod);
    int count;
    if (it == m_cultFollowers.end()) {
        //not found
        count = -1;
    } else {
        count = it->second; 
    }
    return count;
}

void Zone::transferFollowers(GoverningBody* recruiter, GoverningBody* loser, int amount) {
    std::map<GoverningBody*,int>::iterator it;
    
    it = m_cultFollowers.find(recruiter);
    int tempCount = it->second;
    it->second = tempCount + amount;
    //get recruiter follower manager and increase amount there as well
    
    it = m_cultFollowers.find(loser);
    tempCount = it->second;
    it->second = tempCount - amount;
    //get loser follower manager and decrease amount there as well
}