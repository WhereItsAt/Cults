/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GoverningBody.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:07 PM
 */

#ifndef GOVERNINGBODY_H
#define GOVERNINGBODY_H

#include <string>
#include "Leader.h"
//#include "Zone.h"
//#include "Specialist.h"
#include "Policy.h"
//#include "Assett.h"
#include "Individual.h"

class FollowerManager;
class ZoneManager;
class StatusManager;
class ResourceManager;
class Zone;
class Specialist;
class Assett;

enum TierFlag {
    Suburban,
    City,
    Regional,
    Global
};

class GoverningBody {
public:
    GoverningBody();
    GoverningBody(const GoverningBody& orig);
    virtual ~GoverningBody();
    ResourceManager* getResourceManager();
    ZoneManager* getZoneManager();
    FollowerManager* getFollowerManager();
    StatusManager* getStatusManager();
    void setResourceManager(ResourceManager* rm);
    void setZoneManager(ZoneManager* zm);
    void setFollowerManager(FollowerManager* fm);
    void setStatusManager(StatusManager* sm);
    std::string getName();
    void setName(std::string name);
    Leader* getLeader();
    void setLeader(Leader* lead);
    void consume(GoverningBody* enemy);
    void addZone(Zone* newZone);
    Zone* removeZone(Zone* oldZone); //return the removed zone for convenience
    void updateStats();
    void addPolicy(Policy pol); //may update to take in ID of policy instead
    void removePolicy(Policy pol); //may update to take in ID of policy instead
    void addAssett(Assett* acquired);
    Assett* removeAssett(Assett* lost);
    void addSpecialist(SpecType type);
    void removeSpecialist(Specialist* dead);
protected:
    Leader* m_leader;
    ResourceManager* m_paperPusher;
    ZoneManager* m_realEstateManager;
    FollowerManager* m_HR;
    StatusManager* m_statusManager;
    std::string m_name;
    //cimg_library::CImg<unsigned char> m_flag;
private:

};

#endif /* GOVERNINGBODY_H */

