/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Evangelist.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:47 PM
 */

#ifndef EVANGELIST_H
#define EVANGELIST_H

#include "Specialist.h"

class Evangelist: public Specialist {
public:
    Evangelist();
    Evangelist(const Evangelist& orig);
    virtual ~Evangelist();
private:

};

#endif /* EVANGELIST_H */

