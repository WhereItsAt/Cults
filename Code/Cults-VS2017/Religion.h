/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Religion.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:08 PM
 */

#ifndef RELIGION_H
#define RELIGION_H

#include "Cult.h"

class Religion: public Cult {
public:
    Religion();
    Religion(const Religion& orig);
    virtual ~Religion();
private:

};

#endif /* RELIGION_H */

