/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commander.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:34 PM
 */

#ifndef COMMANDER_H
#define COMMANDER_H

#include "Specialist.h"

class Commander: public Specialist {
public:
    Commander();
    Commander(const Commander& orig);
    virtual ~Commander();
private:

};

#endif /* COMMANDER_H */

