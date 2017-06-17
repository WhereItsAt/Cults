/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FollowerManager.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 5:41 PM
 */

#include "FollowerManager.h"

FollowerManager::FollowerManager() {
}

FollowerManager::FollowerManager(const FollowerManager& orig) {
}

FollowerManager::~FollowerManager() {
}

void FollowerManager::addSpecialist(Specialist* spec) {
    m_specialists.push_back(spec);
    spec->setGBody(getGBody());
}

void FollowerManager::addUniqueFollower(UniqueFollower* follower) {
    m_uniqueFollowers.push_back(follower);
    follower->setGBody(getGBody());
}

int FollowerManager::getFollowerCount() {
    return m_followerCount;
}

int FollowerManager::getHappiness() {
    return m_happiness;
}

std::list<Specialist*> FollowerManager::getSpecialists() {
    return m_specialists;
}

int FollowerManager::getUniqueFollowerCount() {
    return m_uniqueFollowerCount;
}

std::list<UniqueFollower*> FollowerManager::getUniqueFollowers() {
    return m_uniqueFollowers;
}

Specialist* FollowerManager::removeSpecialist(Specialist* spec) {
    //dont call die() on specialist here
    //they could be being absorbed by another gbod
    m_specialists.remove(spec);
    return spec;
}

UniqueFollower* FollowerManager::removeUniqueFollower(UniqueFollower* follower) {
    m_uniqueFollowers.remove(follower);
    return follower;
}

void FollowerManager::setFollowerCount(int count) {
    m_followerCount = count;
}

void FollowerManager::setHappiness(int happy) {
    m_happiness = happy;
}

void FollowerManager::setUniqueFollowerCount(int count) {
    m_uniqueFollowerCount = count;
}

void FollowerManager::relinquish(GoverningBody* enemy) {
    FollowerManager* adversary = enemy->getFollowerManager();
    //happiness - possibly go down or go up less than other variables
    //followers - split so some go to enemy, rest go to government
    //unique followers - same as above
    //specialists - same as above
    //lots to consider in how to handle this
    //different cult types, various stats, circumstances under which this occurs
    //watch this space yo
}