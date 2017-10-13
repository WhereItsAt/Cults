/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   City.h
 * Author: scott
 *
 * Created on 10 June 2017, 9:55 PM
 */

#ifndef CITY_H
#define CITY_H

#include "Zone.h"

class City: public Zone {
public:
    City();
    City(const City& orig);
    virtual ~City();
    virtual std::string getType();
private:

};

#endif /* CITY_H */

