/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Individual.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 10:26 PM
 */

#include "Individual.h"

Individual::Individual() {
}

Individual::Individual(const Individual& orig) {
}

Individual::~Individual() {
}

GoverningBody* Individual::getGBody() {
    return m_cult;
}

void Individual::setGBody(GoverningBody* gbod) {
    m_cult = gbod;
}

int Individual::getAge() {
    return m_age;
}

std::string Individual::getName() {
    return m_name;
}

void Individual::setAge(int newAge) {
    m_age = newAge;
}

void Individual::setName(std::string newName) {
    m_name = newName;
}

