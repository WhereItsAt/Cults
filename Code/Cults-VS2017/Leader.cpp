/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Leader.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 6:25 PM
 */

#include "Leader.h"

Leader::Leader() {
}

Leader::Leader(const Leader& orig) {
}

Leader::~Leader() {
}


void Leader::editAppearance() {
    //include img somehow
    //m_portrait = newPortrait;
}

int Leader::getInsanity() {
    return m_insanity;
}

int Leader::getPortrait() {
    //get img somehow
    //return m_portrait;
    return 0;
}

int Leader::getRespect() {
    return m_respect;
}

void Leader::setInsanity(int ins) {
    m_insanity = ins;
}

void Leader::setRespect(int resp) {
    m_respect = resp;
}
