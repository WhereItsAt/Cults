/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceManager.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 5:41 PM
 */

#include "ResourceManager.h"

ResourceManager::ResourceManager() {
}

ResourceManager::ResourceManager(const ResourceManager& orig) {
}

ResourceManager::~ResourceManager() {
}

void ResourceManager::addAssett(Assett* newAssett) {
    m_assetts.push_back(newAssett);
}

int ResourceManager::getInfluence() {
    return m_influence;
}

int ResourceManager::getMoney() {
    return m_money;
}

int ResourceManager::getStability() {
    return m_stability;
}

int ResourceManager::getThreatLevel() {
    return m_threatLevel;
}

Assett* ResourceManager::removeAssett(Assett* oldAssett) {
    m_assetts.remove(oldAssett);
    return oldAssett;
}

void ResourceManager::setInfluence(int inf) {
    m_influence = inf;
}

void ResourceManager::setMoney(int cash) {
    m_money = cash;
}

void ResourceManager::setStability(int stab) {
    m_stability = stab;
}

void ResourceManager::setThreatLevel(int threat) {
    m_threatLevel = threat;
}

void ResourceManager::relinquish(GoverningBody* enemy) {
    //threat level
    //money
    //influence
    //assetts
    //stability
    //see notes in follower manager
}
