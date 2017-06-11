/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myCity.h
 * Author: scott
 *
 * Created on 10 June 2017, 9:55 PM
 */

#ifndef MYCITY_H
#define MYCITY_H

#include "Zone.h"

class myCity: public Zone {
public:
    myCity();
    myCity(const myCity& orig);
    virtual ~myCity();
private:

};

#endif /* MYCITY_H */

