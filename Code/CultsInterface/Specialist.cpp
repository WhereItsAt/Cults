/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Specialist.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 8:33 PM
 */

#include "Specialist.h"

Specialist::Specialist() {
}

Specialist::Specialist(const Specialist& orig) {
}

Specialist::~Specialist() {
}

void Specialist::contribute() {
    //this is where the specialist adds resources to their governing body on each turn
    //akin to the operate function in building/improvement files
    //what or how much is "contributed" will depend on type of specialist and specialaists level
    //this function could be pure virtual in the base class with different implementations in the derived classes
}

void Specialist::die(GoverningBody* murderer) {
    //should give some bonus or resources to murderer? or possibly owner of zone in which they die
    m_cult->removeSpecialist(this);
    //commit suicide
    delete this;
}

int Specialist::getLevel() {
    return m_level;
}

Zone* Specialist::getLocation() {
    return m_location;
}

void Specialist::setLevel(int newLevel) {
    m_level = newLevel;
}

void Specialist::setLocation(Zone* newLocation) {
    m_location = newLocation;
}

void Specialist::upgrade() {
    //increase the specialists level
    //...anything else? change appearance to reflect levelling up?
    //once again could be pure virtual with different implementations for derived classes
}
