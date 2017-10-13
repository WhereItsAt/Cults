/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Specialist.h
 * Author: scott
 *
 * Created on 3 June 2017, 8:33 PM
 */

#ifndef SPECIALIST_H
#define SPECIALIST_H

#include "Individual.h"
#include "Zone.h"

class GoverningBody;

class Specialist: public Individual {
public:
    Specialist();
    Specialist(const Specialist& orig);
    virtual ~Specialist();
    void contribute();
    void upgrade();
    void die(GoverningBody* murderer);
    int getLevel();
    void setLevel(int newLevel);
    Zone* getLocation();
    void setLocation(Zone* newLocation);
protected:
    int m_level;
    Zone* m_location;
private:

};

#endif /* SPECIALIST_H */

