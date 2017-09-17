/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   idGenerator.h
 * Author: scott
 *
 * Created on 29 July 2017, 4:48 PM
 */

#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <vector>
#include <string>
#include "id.h"
#include "nameByCountry.h"

class idGenerator {
public:
    idGenerator();
    idGenerator(const idGenerator& orig);
    virtual ~idGenerator();
    std::string generateFullName(std::string country, bool isMale);
    int generateAge();
    std::string generateCountry(std::string continent);
    bool generateGender();
    void initializeContinents();
    id generateIdentity(std::string continent); 
    
private:
    std::vector<std::string> m_asiaCountries;
    std::vector<std::string> m_europeCountries;
    std::vector<std::string> m_arabCountries;
    std::vector<std::string> m_africaCountries;
    std::vector<std::string> m_nAmericaCountries;
    std::vector<std::string> m_sAmericaCountries;
    std::vector<std::string> m_allCountries;
    std::vector<nameByCountry*> m_nameGenerators;
    
};

#endif /* IDGENERATOR_H */

