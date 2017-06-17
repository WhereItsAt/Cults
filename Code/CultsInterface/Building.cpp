/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Building.cpp
 * Author: scott
 * 
 * Created on 11 June 2017, 10:43 PM
 */

#include "Building.h"

Building::Building() {
}

Building::Building(const Building& orig) {
}

Building::~Building() {
}

void Building::setBase(Base* home) {
    m_homeBase = home;
}

Base* Building::getBase() {
    return m_homeBase;
}

int Building::getPurchaseCost() {
    return m_purchaseCost;
}

void Building::setPurchaseCost(int cost) {
    m_purchaseCost = cost;
}

int Building::getTurnCost() {
    return m_turnCost;
}

void Building::setTurnCost(int cost) {
    m_turnCost = cost;
}

void Building::operate() {
    //here we calculate how much of what attributes this building costs & delivers
    //by checking the effects list, then we apply the effects to the owner
}

void Building::addEffect(std::string attribute, int amount) {
    m_effects.insert(std::pair<std::string,int>(attribute,amount));
}

void Building::removeEffect(std::string attribute) {
    //if using multiple effects with same attribute, 
    //we will have to handle this differently
    std::map<std::string,int>::iterator it;
    it = m_effects.find(attribute);
    m_effects.erase(it);
}