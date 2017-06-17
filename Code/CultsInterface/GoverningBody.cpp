/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GoverningBody.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 5:07 PM
 */
#include <string>
#include "GoverningBody.h"
#include "ResourceManager.h"
#include "StatusManager.h"
#include "FollowerManager.h"
#include "Bureaucrat.h"
#include "Spy.h"
#include "Evangelist.h"
#include "Commander.h"
#include "ZoneManager.h"

GoverningBody::GoverningBody() {
}

GoverningBody::GoverningBody(const GoverningBody& orig) {
}

GoverningBody::~GoverningBody() {
}

FollowerManager* GoverningBody::getFollowerManager() {
    return m_HR;
}

void GoverningBody::addAssett(Assett* acquired) {
    m_paperPusher->addAssett(acquired);
}

void GoverningBody::addPolicy(Policy pol) {
    m_statusManager->addPolicy(pol);
}

void GoverningBody::addSpecialist(SpecType type) {
    //need to set specialist location to homebase/unassigned initially
    //then user brings up menu of specialists and picks new spec to assign them somewhere
    if (type == t_beaurocrat) {
        Bureaucrat* beau = new Bureaucrat();
        m_HR->addSpecialist(beau);
    } else if (type == t_commander) {
        Commander* comm = new Commander();
        m_HR->addSpecialist(comm);
    } else if (type == t_evangelist) {
        Evangelist* ev = new Evangelist();
        m_HR->addSpecialist(ev);
    } else if (type == t_spy) {
        Spy* sam = new Spy();
        m_HR->addSpecialist(sam);
    } else {
        //type doesnt exist, go fuck yourself
    }
}

void GoverningBody::addZone(Zone* newZone) {
    std::string type = newZone->getType();
    if (type.compare("empire") == 0) {
        //this shouldnt really happen
            //its more that an empire gets broken apart and all children zones are added
            //this is dealt with during consume/relinqusih functions
    } else if (type.compare("country") == 0) {
        Country* cnt = dynamic_cast<Country *>(newZone);
        m_realEstateManager->addCountry(cnt);
    } else if (type.compare("city") == 0) {
        myCity* cit = dynamic_cast<myCity *>(newZone);
        m_realEstateManager->addCity(cit);
    } else if (type.compare("suburb") == 0) {
        Suburb* sub = dynamic_cast<Suburb *>(newZone);
        m_realEstateManager->addSuburb(sub);
    } else if (type.compare("region") == 0) {
        RegionalZone* rz = dynamic_cast<RegionalZone *>(newZone);
        m_realEstateManager->addRegion(rz);
    }
    
}

void GoverningBody::consume(GoverningBody* enemy) {
    enemy->getFollowerManager()->relinquish(this);
    enemy->getResourceManager()->relinquish(this);
    enemy->getStatusManager()->relinquish(this);
    enemy->getZoneManager()->relinquish(this);
}

Leader* GoverningBody::getLeader() {
    return m_leader;
}

std::string GoverningBody::getName() {
    return m_name;
}

ResourceManager* GoverningBody::getResourceManager() {
    return m_paperPusher;
}

StatusManager* GoverningBody::getStatusManager() {
    return m_statusManager;
}

ZoneManager* GoverningBody::getZoneManager() {
    return m_realEstateManager;
}

Assett* GoverningBody::removeAssett(Assett* lost) {
    return m_paperPusher->removeAssett(lost);
}

void GoverningBody::removePolicy(Policy pol) {
    m_statusManager->removePolicy(pol);
}

void GoverningBody::removeSpecialist(Specialist* dead) {
    m_HR->removeSpecialist(dead);
}

Zone* GoverningBody::removeZone(Zone* oldZone) {
    std::string type = oldZone->getType();
    if (type.compare("empire") == 0) {
        //this shouldnt really happen
        //its more that an empire gets broken apart and all children zones are added
        //this is dealt with during consume/relinqusih functions
    } else if (type.compare("country") == 0) {
        Country* tempCountry = dynamic_cast<Country *>(oldZone);
        return m_realEstateManager->removeCountry(tempCountry);
    } else if (type.compare("region") == 0) {
        RegionalZone* tempRegion = dynamic_cast<RegionalZone *>(oldZone);
        return m_realEstateManager->removeRegion(tempRegion);
    } else if (type.compare("suburb") == 0) {
        Suburb* tempSuburb = dynamic_cast<Suburb *>(oldZone);
        return m_realEstateManager->removeSuburb(tempSuburb);
    } else if (type.compare("city") == 0) {
        myCity* tempCity = dynamic_cast<myCity *>(oldZone);
        return m_realEstateManager->removeCity(tempCity);
    }
    return oldZone;
}

void GoverningBody::setFollowerManager(FollowerManager* fm) {
    m_HR = fm;
}

void GoverningBody::setLeader(Leader* lead) {
    m_leader = lead;
}

void GoverningBody::setName(std::string name) {
    m_name = name;
}

void GoverningBody::setResourceManager(ResourceManager* rm) {
    m_paperPusher = rm;
}

void GoverningBody::setStatusManager(StatusManager* sm) {
    m_statusManager = sm;
}

void GoverningBody::setZoneManager(ZoneManager* zm) {
    m_realEstateManager = zm;
}

void GoverningBody::updateStats() {
    //this will be for collecting resources each turn
    //ie calling operate on all assetts and buildings
}
