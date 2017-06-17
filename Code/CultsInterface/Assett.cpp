/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assett.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 8:31 PM
 */

#include "Assett.h"

Assett::Assett() {
}

Assett::Assett(const Assett& orig) {
}

Assett::~Assett() {
}

GoverningBody* Assett::getOwner(){
    return m_owner;
}

void Assett::setOwner(GoverningBody* gbod) {
    m_owner = gbod;
}