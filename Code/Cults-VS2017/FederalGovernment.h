/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FederalGovernment.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:09 PM
 */

#ifndef FEDERALGOVERNMENT_H
#define FEDERALGOVERNMENT_H

#include "Government.h"

class FederalGovernment: public Government {
public:
    FederalGovernment();
    FederalGovernment(const FederalGovernment& orig);
    virtual ~FederalGovernment();
private:

};

#endif /* FEDERALGOVERNMENT_H */

