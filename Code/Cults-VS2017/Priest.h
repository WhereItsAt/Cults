/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Priest.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:28 PM
 */

#ifndef PRIEST_H
#define PRIEST_H

#include "Leader.h"

class Priest: public Leader {
public:
    Priest();
    Priest(const Priest& orig);
    virtual ~Priest();
private:

};

#endif /* PRIEST_H */

