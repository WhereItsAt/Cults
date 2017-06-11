/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Improvement.h
 * Author: scott
 *
 * Created on 11 June 2017, 10:44 PM
 */

#ifndef IMPROVEMENT_H
#define IMPROVEMENT_H

#include "Assett.h"
#include "Zone.h"

class Improvement: public Assett {
public:
    Improvement();
    Improvement(const Improvement& orig);
    virtual ~Improvement();
    void setZone(Zone* home);
    Zone* getZone();
    void operate();
    void addEffect(std::string attribute, int amount);
    void removeEffect(std::string attribute, int amount);
private:
    Zone* homeZone;
    std::map<std::string,int> effects;
};

#endif /* IMPROVEMENT_H */

