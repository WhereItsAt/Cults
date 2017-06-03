/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalGovernment.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:09 PM
 */

#ifndef LOCALGOVERNMENT_H
#define LOCALGOVERNMENT_H

#include "Government.h"

class LocalGovernment: public Government {
public:
    LocalGovernment();
    LocalGovernment(const LocalGovernment& orig);
    virtual ~LocalGovernment();
private:

};

#endif /* LOCALGOVERNMENT_H */

