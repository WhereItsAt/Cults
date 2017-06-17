/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Policy.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 8:32 PM
 */

#include <string>

#include "Policy.h"

Policy::Policy() {
}

Policy::Policy(const Policy& orig) {
}

Policy::~Policy() {
}

bool Policy::operator==(const Policy& pol) const {
    bool result = false;
    if (m_name.compare(pol.getName()) == 0) {
        result = true;
    }
    return result;
}

std::string Policy::getName() const {
    return m_name;
}

void Policy::setName(std::string name) {
    m_name = name;
}
