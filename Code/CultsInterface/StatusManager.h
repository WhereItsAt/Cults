/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatusManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:42 PM
 */

#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <map>
#include <list>
#include "Manager.h"
#include "Policy.h"
#include "StoryEvent.h"
#include "GoverningBody.h"

class StatusManager: public Manager {
public:
    StatusManager();
    StatusManager(const StatusManager& orig);
    virtual ~StatusManager();
    virtual void relinquish(GoverningBody* enemy);
    void changeRelation(GoverningBody* gbod, int relationLevel);
    int getRelationWith(GoverningBody* gbod);
    std::map<GoverningBody*, int> getRelations();
    std::list<Policy> getPolicies();
    void addPolicy(Policy newPol);
    void removePolicy(Policy oldPol);
    void addEvent(StoryEvent ev);
    void removeEvent(StoryEvent ev);
    std::list<StoryEvent> getEvents();
private:
    std::list<Policy> m_selectedPolicies;
    std::list<StoryEvent> m_firedEvents;
    std::map<GoverningBody*, int> m_relations;
};

#endif /* STATUSMANAGER_H */

