/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Country.h
 * Author: scott
 *
 * Created on 4 June 2017, 12:37 AM
 */

#ifndef COUNTRY_H
#define COUNTRY_H

#include "Zone.h"

class Country: public Zone {
public:
    Country();
    Country(const Country& orig);
    virtual ~Country();
private:
    
};

#endif /* COUNTRY_H */

