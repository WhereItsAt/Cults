/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CEO.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:28 PM
 */

#ifndef CEO_H
#define CEO_H

#include "Leader.h"

class CEO: public Leader {
public:
    CEO();
    CEO(const CEO& orig);
    virtual ~CEO();
private:

};

#endif /* CEO_H */

