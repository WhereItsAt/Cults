/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Building.h
 * Author: scott
 *
 * Created on 11 June 2017, 10:43 PM
 */

#ifndef BUILDING_H
#define BUILDING_H

#include <map>
#include <string>
#include "Assett.h"
#include "Base.h"

class Building: public Assett {
public:
    Building();
    Building(const Building& orig);
    virtual ~Building();
    void setBase(Base* home);
    Base* getBase();
    int getPurchaseCost();
    void setPurchaseCost(int cost);
    int getTurnCost();
    void setTurnCost(int cost);
    void operate();
    void addEffect(std::string attribute, int amount);
    void removeEffect(std::string attribute);
private:
    Base* m_homeBase;
    int m_purchaseCost;
    int m_turnCost;
    std::map<std::string,int> m_effects;
};

#endif /* BUILDING_H */

