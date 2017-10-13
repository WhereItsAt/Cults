/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spy.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:34 PM
 */

#ifndef SPY_H
#define SPY_H

#include "Specialist.h"

class Spy: public Specialist {
public:
    Spy();
    Spy(const Spy& orig);
    virtual ~Spy();
private:

};

#endif /* SPY_H */

