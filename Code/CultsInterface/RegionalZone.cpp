/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RegionalZone.cpp
 * Author: scott
 * 
 * Created on 7 June 2017, 8:36 PM
 */

#include "RegionalZone.h"

RegionalZone::RegionalZone() {
}

RegionalZone::RegionalZone(const RegionalZone& orig) {
}

RegionalZone::~RegionalZone() {
}

std::list<Assett*> RegionalZone::getAssetts() {
    return m_assetts;
}

void RegionalZone::addAssett(Assett* ass) {
    m_assetts.push_back(ass);
}

Assett* RegionalZone::removeAssett(Assett* ass) {
    m_assetts.remove(ass);
    return ass;
}

std::string RegionalZone::getType() {
    return "region";
}
