/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Government.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:07 PM
 */

#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "GoverningBody.h"

class Government: public GoverningBody {
public:
    Government();
    Government(const Government& orig);
    virtual ~Government();
private:

};

#endif /* GOVERNMENT_H */

