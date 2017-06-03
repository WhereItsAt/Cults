/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Individual.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:26 PM
 */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>

class GoverningBody;

class Individual {
public:
    Individual();
    Individual(const Individual& orig);
    virtual ~Individual();
    std::string getName();
    void setName(std::string newName);
    int getAge();
    void setAge(int newAge);
    GoverningBody* getGBody();
    void setGBody(GoverningBody* gbod);
protected:
    std::string name;
    int age;
    GoverningBody* cult;
private:

};

enum SpecType
{
    Beaurocrat,
    Commander,
    Spy,
    Evangelist
};
//specType tempType = Commander;

#endif /* INDIVIDUAL_H */

