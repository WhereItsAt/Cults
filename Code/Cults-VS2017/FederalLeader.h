/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FederalLeader.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:28 PM
 */

#ifndef FEDERALLEADER_H
#define FEDERALLEADER_H

#include "GovernmentLeader.h"

class FederalLeader: public GovernmentLeader {
public:
    FederalLeader();
    FederalLeader(const FederalLeader& orig);
    virtual ~FederalLeader();
private:

};

#endif /* FEDERALLEADER_H */

