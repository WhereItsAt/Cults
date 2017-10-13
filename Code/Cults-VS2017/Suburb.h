/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Suburb.h
 * Author: scott
 *
 * Created on 4 June 2017, 12:36 AM
 */

#ifndef SUBURB_H
#define SUBURB_H

#include <list>
#include "Zone.h"
#include "Assett.h"

class Suburb: public Zone {
public:
    Suburb();
    Suburb(const Suburb& orig);
    virtual ~Suburb();
    std::list<Assett*> getAssetts();
    void addAssett(Assett* ass);
    Assett* removeAssett(Assett* ass);
    virtual std::string getType();
private:
    std::list<Assett*> m_assetts;
};

#endif /* SUBURB_H */

