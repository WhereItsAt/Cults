/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   id.h
 * Author: scott
 *
 * Created on 29 July 2017, 5:53 PM
 */

#ifndef ID_H
#define ID_H

#include <string>

class id {
public:
    id();
    id(const id& orig);
    virtual ~id();
    std::string getName();
    std::string getCountry();
    int getAge();
    bool isMale();
    void setName(std::string name);
    void setCountry(std::string country);
    void setAge(int age);
    void setGender(bool isMale);
    void printID();
private:
    std::string m_country;
    std:: string m_name;
    bool m_male;
    int m_age;
};

#endif /* ID_H */

