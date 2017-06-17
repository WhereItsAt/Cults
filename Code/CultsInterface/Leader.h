/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Leader.h
 * Author: scott
 *
 * Created on 3 June 2017, 6:25 PM
 */

#ifndef LEADER_H
#define LEADER_H

#include "Individual.h"
#include "CImg.h"

class Leader: public Individual {
public:
    Leader();
    Leader(const Leader& orig);
    virtual ~Leader();
    void editAppearance(cimg_library::CImg<unsigned char> newPortrait);
    int getInsanity();
    int getRespect();
    void setInsanity(int ins);
    void setRespect(int resp);
    cimg_library::CImg<unsigned char> getPortrait();
protected:
    int m_insanity;
    int m_respect;
    cimg_library::CImg<unsigned char> m_portrait;
private:

};

#endif /* LEADER_H */

