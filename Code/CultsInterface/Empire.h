/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Empire.h
 * Author: scott
 *
 * Created on 4 June 2017, 12:34 AM
 */

#ifndef EMPIRE_H
#define EMPIRE_H

#include "Zone.h"

class Empire: public Zone {
public:
    Empire();
    Empire(const Empire& orig);
    virtual ~Empire();
private:
    
};

#endif /* EMPIRE_H */

