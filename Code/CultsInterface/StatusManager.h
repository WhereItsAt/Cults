/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatusManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:42 PM
 */

#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include "Manager.h"

class StatusManager: public Manager {
public:
    StatusManager();
    StatusManager(const StatusManager& orig);
    virtual ~StatusManager();
private:

};

#endif /* STATUSMANAGER_H */

