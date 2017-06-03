/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UniqueFollower.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:27 PM
 */

#ifndef UNIQUEFOLLOWER_H
#define UNIQUEFOLLOWER_H

#include "Individual.h"
#include "Leader.h"

class UniqueFollower: public Individual {
public:
    UniqueFollower();
    UniqueFollower(const UniqueFollower& orig);
    virtual ~UniqueFollower();
    void contribute();
    void jumpShip();
    Leader* convertToLeader();
private:
    int opinion;
    GoverningBody* preferredGBody;
    SpecType type;
    int level;
    int fear;
};

#endif /* UNIQUEFOLLOWER_H */

