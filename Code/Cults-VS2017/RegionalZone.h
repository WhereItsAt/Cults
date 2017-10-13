/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RegionalZone.h
 * Author: scott
 *
 * Created on 7 June 2017, 8:36 PM
 */

#ifndef REGIONALZONE_H
#define REGIONALZONE_H

#include <list>
#include "Zone.h"
#include "Assett.h"

class RegionalZone: public Zone {
public:
    RegionalZone();
    RegionalZone(const RegionalZone& orig);
    virtual ~RegionalZone();
    std::list<Assett*> getAssetts();
    void addAssett(Assett* ass);
    Assett* removeAssett(Assett* ass);
    virtual std::string getType();
private:
    std::list<Assett*> m_assetts;
};

#endif /* REGIONALZONE_H */

