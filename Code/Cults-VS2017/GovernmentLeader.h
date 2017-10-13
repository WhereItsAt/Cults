/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GovernmentLeader.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:27 PM
 */

#ifndef GOVERNMENTLEADER_H
#define GOVERNMENTLEADER_H

#include "Leader.h"

class GovernmentLeader: public Leader {
public:
    GovernmentLeader();
    GovernmentLeader(const GovernmentLeader& orig);
    virtual ~GovernmentLeader();
private:

};

#endif /* GOVERNMENTLEADER_H */

