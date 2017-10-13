/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Manager.h
 * Author: scott
 *
 * Created on 3 June 2017, 5:41 PM
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "GoverningBody.h"

class Manager {
public:
    Manager();
    Manager(const Manager& orig);
    virtual ~Manager();
    virtual void relinquish(GoverningBody* enemy) = 0;
    GoverningBody* getGBody();
    void setGBody(GoverningBody* gbod);
protected:
    GoverningBody* m_gBody;
private:

};

#endif /* MANAGER_H */

