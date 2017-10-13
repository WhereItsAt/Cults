/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Politician.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:28 PM
 */

#ifndef POLITICIAN_H
#define POLITICIAN_H

#include "Leader.h"

class Politician: public Leader {
public:
    Politician();
    Politician(const Politician& orig);
    virtual ~Politician();
private:

};

#endif /* POLITICIAN_H */

