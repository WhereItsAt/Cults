/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nameByCountry.cpp
 * Author: scott
 * 
 * Created on 29 July 2017, 8:44 PM
 */

#include "nameByCountry.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <stdlib.h>

nameByCountry::nameByCountry() {
}

nameByCountry::nameByCountry(std::string name) 
{
    //std::string dirPath = "/home/scott/Documents/cults/";
    m_countryName = name;
    m_mgTotalNames = 0;
    m_fgTotalNames = 0;
    m_sTotalNames = 0;
    //std::string surFile = dirPath + name + ".txt";
    //std::string maleFile = dirPath + name + "Male.txt";
    //std::string femaleFile = dirPath + name + "Female.txt";
    std::string surFile = name + ".txt";
    std::string maleFile = name +"Male.txt";
    std::string femaleFile = name + "Female.txt";
    populateNames(surFile, maleFile, femaleFile);
}

nameByCountry::nameByCountry(const nameByCountry& orig) {
}

nameByCountry::~nameByCountry() {
}

std::string nameByCountry::getCountryName()
{
    return m_countryName;
}

void nameByCountry::setCountryName(std::string name)
{
    m_countryName = name;
}

std::vector<std::string> nameByCountry::getNamesStartingWith(std::string type, char first) 
{
    std::vector<std::string> result;
    if (type.compare("surname") == 0) {
            result = m_surnames[first];
    } else if (type.compare("maleGiven") == 0) {
            result = m_maleGivenNames[first];
    } else if (type.compare("femaleGiven") == 0) {
            result = m_femaleGivenNames[first];
    }
    return result;
}

char nameByCountry::pickLastLetterFromVector(std::vector<std::string> valid) 
{
    std::map<char,int> lastLetterFreq;
    for (int i = 0; i < valid.size(); ++i) {
            std::string tempName = valid.at(i);
            //char last = tempName.back();
            char last = tempName.at(tempName.length() - 1);
            lastLetterFreq[last] += 1;
    }

    char result;
    int amount = valid.size();
    int randIndex = rand() % amount;
    std::map<char,int>::iterator it = lastLetterFreq.begin();
    while (it != lastLetterFreq.end()) {
            if (randIndex < it->second) {
                    result = it->first;
                    break;
            } else {
                    randIndex -= it->second;
                    ++it;
            }
    }
    return result;
}

std::string nameByCountry::generateName(bool isMale, bool isSurname)
{
    char firstLetter;
    char lastLetter;
    std::vector<std::string> possibleNames;
    std::string name;

    if (isSurname) {
            firstLetter = this->pickFirstLetter("surname");
            std::vector<std::string> tempNames = this->getNamesStartingWith("surname", firstLetter);
            lastLetter = this->pickLastLetterFromVector(tempNames);
            possibleNames = this->collectValidNames(tempNames, firstLetter, lastLetter);
            int randIndex = rand() % possibleNames.size();
            name = possibleNames.at(randIndex);
    } else {
            if (isMale) {
                    firstLetter = this->pickFirstLetter("maleGiven");
                    std::vector<std::string> tempNames = this->getNamesStartingWith("maleGiven", firstLetter);
                    lastLetter = this->pickLastLetterFromVector(tempNames);
                    possibleNames = this->collectValidNames(tempNames, firstLetter, lastLetter);
                    int randIndex = rand() % possibleNames.size();
                    name = possibleNames.at(randIndex);
            } else {
                    firstLetter = this->pickFirstLetter("femaleGiven");
                    std::vector<std::string> tempNames = this->getNamesStartingWith("femaleGiven", firstLetter);
                    lastLetter = this->pickLastLetterFromVector(tempNames);
                    possibleNames = this->collectValidNames(tempNames, firstLetter, lastLetter);
                    int randIndex = rand() % possibleNames.size();
                    name = possibleNames.at(randIndex);	
            }
    }

    return name;
}

std::vector<std::string> nameByCountry::collectValidNames(std::vector<std::string> selected, char firstLetter, char lastLetter) 
{
    std::vector<std::string> chosen;

    for (int i = 0; i < selected.size(); ++i) {
            std::string tempName = selected.at(i);
            if ((tempName.at(0) == firstLetter) && (tempName.at(tempName.length() - 1) == lastLetter)) {
                    chosen.push_back(tempName);
            }
    }

    return chosen;
}

char nameByCountry::pickFirstLetter(std::string type) 
{
    int amount = 0;
    int randIndex;
    char randomChar = 'A';
    if (type.compare("maleGiven") == 0) {
            amount = m_mgTotalNames;
            randIndex = rand() % amount;
            std::map<char,int>::iterator it = m_mgFirstFreq.begin();
            while (it != m_mgFirstFreq.end()) {
                    if (randIndex < it->second) {
                            return it->first;
                    } else {
                            randIndex -= it->second;
                            ++it;
                    }
            }
    } else if (type.compare("femaleGiven") == 0) {
            amount = m_fgTotalNames;
            randIndex = rand() % amount;
            std::map<char,int>::iterator it = m_fgFirstFreq.begin();
            while (it != m_fgFirstFreq.end()) {
                    if (randIndex < it->second) {
                            return it->first;
                    } else {
                            randIndex -= it->second;
                            ++it;
                    }
            }

    } else if (type.compare("surname") == 0) {
            amount = m_sTotalNames;
            randIndex = rand() % amount;
            std::map<char,int>::iterator it = m_sFirstFreq.begin();
            while (it != m_sFirstFreq.end()) {
                    if (randIndex < it->second) {
                            return it->first;
                    } else {
                            randIndex -= it->second;
                            ++it;
                    }
            }
    } else {
            randomChar += rand() % 26;
    }
    return randomChar;
}

void nameByCountry::populateNames(std::string surnameList, std::string maleList, std::string femaleList)
{
    std::string line;
    std::ifstream surnames (surnameList.c_str());
    if (surnames.is_open())
    {
            while ( getline (surnames,line) )
            {
                    addName("surname", line);
            }
            surnames.close();
    }

    else std::cout << "Unable to open surnames file"; 

    std::ifstream male (maleList.c_str());
    if (male.is_open())
    {
            while ( getline (male,line) )
            {
                    addName("maleGiven", line);
            }
            male.close();
    }

    else std::cout << "Unable to open male given names file";

    std::ifstream female (femaleList.c_str());
    if (female.is_open())
    {
            while ( getline (female,line) )
            {
                    addName("femaleGiven", line);
            }
            female.close();
    }

    else std::cout << "Unable to open female given names file";
}

int nameByCountry::getTotalNames(std::string type)
{
    int result = 0;
    if (type.compare("maleGiven") == 0) {
            result = m_mgTotalNames;
    } else if (type.compare("femaleGiven") == 0) {
            result = m_fgTotalNames;
    } else if (type.compare("surname") == 0) {
            result = m_sTotalNames;
    }
    return result;
}

void nameByCountry::addName(std::string type, std::string name)
{
    char first = name.at(0);

    if (type.compare("maleGiven") == 0) {
            m_maleGivenNames[first].push_back(name);
            m_mgFirstFreq[first] += 1;
            m_mgTotalNames++;

    } else if (type.compare("femaleGiven") == 0) {
            m_femaleGivenNames[first].push_back(name);
            m_fgFirstFreq[first] += 1;
            m_fgTotalNames++;

    } else if (type.compare("surname") == 0) {
            m_surnames[first].push_back(name);
            m_sFirstFreq[first] += 1;
            m_sTotalNames++;
    }
}

void nameByCountry::printNames()
{
    std::map<char,std::vector<std::string> >::iterator it = m_maleGivenNames.begin();
    std::cout << "male first names: " << std::endl;
    while (it != m_maleGivenNames.end()) {
            std::vector<std::string> tempNames = this->getNamesStartingWith("maleGiven", it->first);
            for (int i = 0; i < tempNames.size(); i++)
            {
                    std::cout << tempNames.at(i) << " ";
            }
            ++it;
    }
    std::cout << std::endl;

    it = m_femaleGivenNames.begin();
    std::cout << "female first names: " << std::endl;
    while (it != m_femaleGivenNames.end()) {
            std::vector<std::string> tempNames = this->getNamesStartingWith("femaleGiven", it->first);
            for (int i = 0; i < tempNames.size(); i++)
            {
                    std::cout << tempNames.at(i) << " ";
            }
            ++it;
    }
    std::cout << std::endl;

    it = m_surnames.begin();
    std::cout << "last names: " << std::endl;
    while (it != m_surnames.end()) {
            std::vector<std::string> tempNames = this->getNamesStartingWith("surname", it->first);
            for (int i = 0; i < tempNames.size(); i++)
            {
                    std::cout << tempNames.at(i) << " ";
            }
            ++it;
    }
    std::cout << std::endl;

}
