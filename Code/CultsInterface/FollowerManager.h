/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FollowerManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:41 PM
 */

#ifndef FOLLOWERMANAGER_H
#define FOLLOWERMANAGER_H

#include "Manager.h"

class FollowerManager: public Manager {
public:
    FollowerManager();
    FollowerManager(const FollowerManager& orig);
    virtual ~FollowerManager();
private:

};

#endif /* FOLLOWERMANAGER_H */

