/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Improvement.cpp
 * Author: scott
 * 
 * Created on 11 June 2017, 10:44 PM
 */

#include "Improvement.h"

Improvement::Improvement() {
}

Improvement::Improvement(const Improvement& orig) {
}

Improvement::~Improvement() {
}

void Improvement::setZone(Zone* home) {
    m_homeZone = home;
}

Zone* Improvement::getZone() {
    return m_homeZone;
}

void Improvement::operate() {
    //here we calculate how much of what attributes this building costs & delivers
    //by checking the effects list, then we apply the effects to the owner
}

void Improvement::addEffect(std::string attribute, int amount) {
    m_effects.insert(std::pair<std::string,int>(attribute,amount));
}

void Improvement::removeEffect(std::string attribute, int amount) {
    //if using multiple effects with same attribute, 
    //we will have to handle this differently
    std::map<std::string,int>::iterator it;
    it = m_effects.find(attribute);
    m_effects.erase(it);
}

std::map<std::string,int> Improvement::getEffects() {
    return m_effects;
}