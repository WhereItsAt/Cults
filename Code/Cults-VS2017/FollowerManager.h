/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FollowerManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:41 PM
 */

#ifndef FOLLOWERMANAGER_H
#define FOLLOWERMANAGER_H

#include <list>
#include "Manager.h"
#include "UniqueFollower.h"
#include "Specialist.h"

class FollowerManager: public Manager {
public:
    FollowerManager();
    FollowerManager(const FollowerManager& orig);
    virtual ~FollowerManager();
    virtual void relinquish(GoverningBody* enemy);
    void setFollowerCount(int count);
    int getFollowerCount();
    void setUniqueFollowerCount(int count);
    int getUniqueFollowerCount();
    std::list<UniqueFollower*> getUniqueFollowers();
    void addUniqueFollower(UniqueFollower* follower);
    UniqueFollower* removeUniqueFollower(UniqueFollower* follower);
    void setHappiness(int happy);
    int getHappiness();
    std::list<Specialist*> getSpecialists();
    void addSpecialist(Specialist* spec);
    Specialist* removeSpecialist(Specialist* spec);
private:
    int m_followerCount;
    int m_uniqueFollowerCount;
    std::list<UniqueFollower*> m_uniqueFollowers;
    int m_happiness;
    std::list<Specialist*> m_specialists;
};

#endif /* FOLLOWERMANAGER_H */

