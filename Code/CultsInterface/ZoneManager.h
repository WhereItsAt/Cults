/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneManager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:41 PM
 */

#ifndef ZONEMANAGER_H
#define ZONEMANAGER_H

#include "Manager.h"

class ZoneManager: public Manager {
public:
    ZoneManager();
    ZoneManager(const ZoneManager& orig);
    virtual ~ZoneManager();
private:

};

#endif /* ZONEMANAGER_H */

