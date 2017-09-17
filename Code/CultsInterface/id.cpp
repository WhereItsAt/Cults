/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   id.cpp
 * Author: scott
 * 
 * Created on 29 July 2017, 5:53 PM
 */

#include "id.h"
#include <iostream>

id::id() {
}

id::id(const id& orig) {
}

id::~id() {
}

std::string id::getName() {
    return m_name;
}

std::string id::getCountry() {
    return m_country;
}

int id::getAge() {
    return m_age;
}

void id::setName(std::string name) {
    m_name = name;
}

void id::setCountry(std::string country) {
    m_country = country;
}

void id::setAge(int age) {
    m_age = age;
}

bool id::isMale() {
    return m_male;
}

void id::setGender(bool isMale) {
    m_male = isMale;
}

void id::printID() {
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Age: " << m_age << std::endl;
    std::string gender;
    if (m_male) {
        gender = "Male";
    } else {
        gender = "Female";
    }
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Birthplace: " << m_country << std::endl;
}