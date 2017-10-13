/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatusManager.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 5:42 PM
 */

#include "StatusManager.h"

StatusManager::StatusManager() {
}

StatusManager::StatusManager(const StatusManager& orig) {
}

StatusManager::~StatusManager() {
}

void StatusManager::addEvent(StoryEvent ev) {
    m_firedEvents.push_back(ev);
}

void StatusManager::addPolicy(Policy newPol) {
    m_selectedPolicies.push_back(newPol);
}

//add or subtract relationLevel from current relation
void StatusManager::changeRelation(GoverningBody* gbod, int relationLevel) {
    std::map<GoverningBody*,int>::iterator it;
    it = m_relations.find(gbod);
    it->second += relationLevel;
}

std::list<StoryEvent> StatusManager::getEvents() {
    return m_firedEvents;
}

std::list<Policy> StatusManager::getPolicies() {
    return m_selectedPolicies;
}

int StatusManager::getRelationWith(GoverningBody* gbod) {
    std::map<GoverningBody*,int>::iterator it;
    it = m_relations.find(gbod);
    return it->second;
}

std::map<GoverningBody*, int> StatusManager::getRelations() {
    return m_relations;
}

void StatusManager::relinquish(GoverningBody* enemy) {
    //relations
    //events
    //policies
    //see notes for relinquish in followermanager
}

void StatusManager::removeEvent(StoryEvent ev) {
    m_firedEvents.remove(ev);
}

void StatusManager::removePolicy(Policy oldPol) {
    m_selectedPolicies.remove(oldPol);
}
