/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cult.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:07 PM
 */

#ifndef CULT_H
#define CULT_H

#include "GoverningBody.h"
#include "Government.h"

class Cult: public GoverningBody {
public:
    Cult();
    Cult(const Cult& orig);
    virtual ~Cult();
    void levelUp();
    Government* getMaster();
    void setMaster(Government* newMaster);
    void coup(Leader* newLeader);
protected:
    Government* m_master;
private:

};

#endif /* CULT_H */

