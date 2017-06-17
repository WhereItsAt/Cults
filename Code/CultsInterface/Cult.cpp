/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cult.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 5:07 PM
 */

#include "Cult.h"

Cult::Cult() {
}

Cult::Cult(const Cult& orig) {
}

Cult::~Cult() {
}

void Cult::coup(Leader* newLeader) {
    //need to determine what exactly this represents and how it will occur
    //may need to take uniquespecialist as argument
    //convert them to leader and replace current leader
    //update any references to leader (pics, menu entries, cult history etc)
    //recalculate cult stats
    //recalculate cult relations
    m_leader = newLeader;
}

Government* Cult::getMaster() {
    return m_master;
}

TierFlag Cult::getTier() {
    return m_tier;
}

void Cult::levelUp() {
    //not sure if next line works... (ie tier++), may need to add int values to enum decleration
    //yep it doesnt work
    //m_tier++;
    //if tier 1, set tier 2, etc
    //other stuff here, ie increase respect, change homezone/base, etc
}

void Cult::setMaster(Government* newMaster) {
    m_master = newMaster;
}

void Cult::setTier(TierFlag newTier) {
    m_tier = newTier;
}

