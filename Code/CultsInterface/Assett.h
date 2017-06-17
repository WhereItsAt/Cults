/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assett.h
 * Author: scott
 *
 * Created on 3 June 2017, 8:31 PM
 */

#ifndef ASSETT_H
#define ASSETT_H

#include "GoverningBody.h"

class Assett {
public:
    Assett();
    Assett(const Assett& orig);
    virtual ~Assett();
    GoverningBody* getOwner();
    void setOwner(GoverningBody* gbod);
protected:
    GoverningBody* m_owner;
private:

};

#endif /* ASSETT_H */

