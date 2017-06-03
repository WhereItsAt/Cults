/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:41 PM
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <list>
#include "Manager.h"

class ResourceManager: public Manager {
public:
    ResourceManager();
    ResourceManager(const ResourceManager& orig);
    virtual ~ResourceManager();
    void relinquish(GoverningBody* enemy);
    int getInfluence();
    int getMoney();
    int getThreatLevel();
    int getStability();
    void setInfluence(int inf);
    void setMoney(int cash);
    void setStability(int stab);
    void setThreatLevel(int threat);
    void addAssett(Assett* newAssett);
    Assett* removeAssett(Assett* oldAssett);
private:
    int influence;
    int money;
    int threatLevel;
    int stability;
    list<Assett> assetts;
};

#endif /* RESOURCEMANAGER_H */

