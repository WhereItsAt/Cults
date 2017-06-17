/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Suburb.cpp
 * Author: scott
 * 
 * Created on 4 June 2017, 12:36 AM
 */

#include "Suburb.h"

Suburb::Suburb() {
}

Suburb::Suburb(const Suburb& orig) {
}

Suburb::~Suburb() {
}

std::list<Assett*> Suburb::getAssetts() {
    return m_assetts;
}

void Suburb::addAssett(Assett* ass) {
    m_assetts.push_back(ass);
}

Assett* Suburb::removeAssett(Assett* ass) {
    m_assetts.remove(ass);
    return ass;
}

std::string Suburb::getType() {
    return "suburb";
}
