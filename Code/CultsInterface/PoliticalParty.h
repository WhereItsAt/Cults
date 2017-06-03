/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PoliticalParty.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:08 PM
 */

#ifndef POLITICALPARTY_H
#define POLITICALPARTY_H

#include "Cult.h"

class PoliticalParty: public Cult {
public:
    PoliticalParty();
    PoliticalParty(const PoliticalParty& orig);
    virtual ~PoliticalParty();
private:

};

#endif /* POLITICALPARTY_H */

