/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalLeader.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:27 PM
 */

#ifndef LOCALLEADER_H
#define LOCALLEADER_H

#include "GovernmentLeader.h"

class LocalLeader: public GovernmentLeader {
public:
    LocalLeader();
    LocalLeader(const LocalLeader& orig);
    virtual ~LocalLeader();
private:

};

#endif /* LOCALLEADER_H */

