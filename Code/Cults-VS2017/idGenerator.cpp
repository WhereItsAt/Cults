/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   idGenerator.cpp
 * Author: scott
 * 
 * Created on 29 July 2017, 4:48 PM
 */

#include "idGenerator.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

idGenerator::idGenerator() {
    initializeContinents();
}

idGenerator::idGenerator(const idGenerator& orig) {
}

idGenerator::~idGenerator() {
}

int idGenerator::generateAge() {
    //return random age between 18 and 80
    //possibly weight ages so 18-30 most common, and less likely further out
    //possibly weight attributes based on age, ie more likely to be impulsive if younger, more likely to be skilled/rich if older, etc
    return 18 + (rand() % 64);
}

//possible continents:
//"Asia", "Europe", "Middle East", "Africa", "North America", "South America"
std::string idGenerator::generateCountry(std::string continent) {
    std::string result;
    std::string conts[] = {"Asia", "Europe", "Middle East", "Africa", "North America", "South America"};
    int numConts = 6;
    int contIndex = numConts;
    for (int i = 0; i < numConts; i++) {
        if (conts[i].compare(continent) == 0) {
            contIndex = i;
        }
    }
    
    switch (contIndex) {
        case 0:
            //asia
            result = m_asiaCountries.at(rand() % m_asiaCountries.size());
            break;
        case 1:
            //europe
            result = m_europeCountries.at(rand() % m_europeCountries.size());
            break;
        case 2:
            //middle east
            result = m_arabCountries.at(rand() % m_arabCountries.size());
            break;
        case 3:
            //Africa
            result = m_africaCountries.at(rand() % m_africaCountries.size());
            break;
        case 4:
            //north america
            result = m_nAmericaCountries.at(rand() % m_nAmericaCountries.size());
            break;
        case 5:
            //south america
            result = m_sAmericaCountries.at(rand() % m_sAmericaCountries.size());
            break;
        default:
            result = m_allCountries.at(rand() % m_allCountries.size());
            break;
    }
    
    return result;
}

bool idGenerator::generateGender() {
    return ((rand() % 2) == 1);
}

void idGenerator::initializeContinents() {
    nameByCountry* tempCountry;
    
    //africa
    m_africaCountries.push_back("Nigeria");
    tempCountry = new nameByCountry("Nigeria");
    m_nameGenerators.push_back(tempCountry);
    m_africaCountries.push_back("South Africa");
    tempCountry = new nameByCountry("South Africa");
    m_nameGenerators.push_back(tempCountry);
    m_africaCountries.push_back("Egypt");
    tempCountry = new nameByCountry("Egypt");
    m_nameGenerators.push_back(tempCountry);
    m_africaCountries.push_back("Sudan");
    tempCountry = new nameByCountry("Sudan");
    m_nameGenerators.push_back(tempCountry);
    
    //middle east
    m_arabCountries.push_back("Israel");
    tempCountry = new nameByCountry("Israel");
    m_nameGenerators.push_back(tempCountry);
    m_arabCountries.push_back("Saudi Arabia");
    tempCountry = new nameByCountry("Saudi Arabia");
    m_nameGenerators.push_back(tempCountry);
    m_arabCountries.push_back("Iraq");
    tempCountry = new nameByCountry("Iraq");
    m_nameGenerators.push_back(tempCountry);
    m_arabCountries.push_back("Iran");
    tempCountry = new nameByCountry("Iran");
    m_nameGenerators.push_back(tempCountry);
    
    //asia
    m_asiaCountries.push_back("China");
    tempCountry = new nameByCountry("China");
    m_nameGenerators.push_back(tempCountry);
    m_asiaCountries.push_back("Japan");
    tempCountry = new nameByCountry("Japan");
    m_nameGenerators.push_back(tempCountry);
    m_asiaCountries.push_back("Korea");
    tempCountry = new nameByCountry("Korea");
    m_nameGenerators.push_back(tempCountry);
    m_asiaCountries.push_back("Russia");
    tempCountry = new nameByCountry("Russia");
    m_nameGenerators.push_back(tempCountry);
    m_asiaCountries.push_back("India");
    tempCountry = new nameByCountry("India");
    m_nameGenerators.push_back(tempCountry);
    m_asiaCountries.push_back("Vietnam");
    tempCountry = new nameByCountry("Vietnam");
    m_nameGenerators.push_back(tempCountry);
    
    //north america
    m_nAmericaCountries.push_back("US");
    tempCountry = new nameByCountry("US");
    m_nameGenerators.push_back(tempCountry);
    m_nAmericaCountries.push_back("Mexico");
    tempCountry = new nameByCountry("Mexico");
    m_nameGenerators.push_back(tempCountry);
    m_nAmericaCountries.push_back("Canada");
    tempCountry = new nameByCountry("Canada");
    m_nameGenerators.push_back(tempCountry);
    
    //south america
    m_sAmericaCountries.push_back("Brazil");
    tempCountry = new nameByCountry("Brazil");
    m_nameGenerators.push_back(tempCountry);
    m_sAmericaCountries.push_back("Chile");
    tempCountry = new nameByCountry("Chile");
    m_nameGenerators.push_back(tempCountry);
    m_sAmericaCountries.push_back("Peru");
    tempCountry = new nameByCountry("Peru");
    m_nameGenerators.push_back(tempCountry);
    m_sAmericaCountries.push_back("Argentina");
    tempCountry = new nameByCountry("Argentina");
    m_nameGenerators.push_back(tempCountry);
            
    //europe
    m_europeCountries.push_back("Italy");
    tempCountry = new nameByCountry("Italy");
    m_nameGenerators.push_back(tempCountry);
    m_europeCountries.push_back("France");
    tempCountry = new nameByCountry("France");
    m_nameGenerators.push_back(tempCountry);
    m_europeCountries.push_back("Denmark");
    tempCountry = new nameByCountry("Denmark");
    m_nameGenerators.push_back(tempCountry);
    m_europeCountries.push_back("Germany");
    tempCountry = new nameByCountry("Germany");
    m_nameGenerators.push_back(tempCountry);
    m_europeCountries.push_back("England");
    tempCountry = new nameByCountry("England");
    m_nameGenerators.push_back(tempCountry);
    m_europeCountries.push_back("Spain");
    tempCountry = new nameByCountry("Spain");
    m_nameGenerators.push_back(tempCountry);
    
    int totalSize = m_africaCountries.size() + m_arabCountries.size() + m_asiaCountries.size() + m_nAmericaCountries.size() + m_sAmericaCountries.size() + m_europeCountries.size();
    m_allCountries.reserve(totalSize);
    m_allCountries.insert(m_allCountries.end(), m_africaCountries.begin(), m_africaCountries.end());
    m_allCountries.insert(m_allCountries.end(), m_arabCountries.begin(), m_arabCountries.end());
    m_allCountries.insert(m_allCountries.end(), m_asiaCountries.begin(), m_asiaCountries.end());
    m_allCountries.insert(m_allCountries.end(), m_nAmericaCountries.begin(), m_nAmericaCountries.end());
    m_allCountries.insert(m_allCountries.end(), m_sAmericaCountries.begin(), m_sAmericaCountries.end());
    m_allCountries.insert(m_allCountries.end(), m_europeCountries.begin(), m_europeCountries.end());
}

std::string idGenerator::generateFullName(std::string country, bool isMale) {
    std::string result;
    for (int i = 0; i < m_nameGenerators.size(); i++) {
        if (m_nameGenerators.at(i)->getCountryName().compare(country) == 0) {
            result = m_nameGenerators.at(i)->generateName(isMale, false);
            result += " ";
            result += m_nameGenerators.at(i)->generateName(isMale, true);
        }
    }
    return result;
}

id idGenerator::generateIdentity(std::string continent) {
    id result;
    result.setGender(generateGender());
    result.setAge(generateAge());
    result.setCountry(generateCountry(continent));
    //get country and generate name for it
    result.setName(this->generateFullName(result.getCountry(),result.isMale()));
    return result;
}
