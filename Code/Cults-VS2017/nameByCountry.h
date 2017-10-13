/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nameByCountry.h
 * Author: scott
 *
 * Created on 29 July 2017, 8:44 PM
 */

#ifndef NAMEBYCOUNTRY_H
#define NAMEBYCOUNTRY_H

#include <string>
#include <vector>
#include <map>

class nameByCountry {
public:
    nameByCountry();
    nameByCountry(std::string countryname);
    nameByCountry(const nameByCountry& orig);
    virtual ~nameByCountry();
    std::string getCountryName();
    void setCountryName(std::string name);
    void addName(std::string type, std::string name);
    void populateNames(std::string surnameList, std::string maleList, std::string femaleList);
    int getTotalNames(std::string type);
    char pickFirstLetter(std::string type);
    std::vector<std::string> getNamesStartingWith(std::string type, char first);
    char pickLastLetterFromVector(std::vector<std::string> valid);
    std::string generateName(bool isMale, bool isSurname);
    std::vector<std::string> collectValidNames(std::vector<std::string> selected, char firstLetter, char lastLetter);
    void printNames();
    
private:
    std::string m_countryName;
    int m_mgTotalNames;
    int m_fgTotalNames;
    int m_sTotalNames;
    std::map<char,std::vector<std::string> > m_maleGivenNames;
    std::map<char,std::vector<std::string> > m_femaleGivenNames;
    std::map<char,std::vector<std::string> > m_surnames;
    std::map<char,int> m_mgFirstFreq; //map = number of names starting with letter
    std::map<char,int> m_fgFirstFreq;
    std::map<char,int> m_sFirstFreq;
};

#endif /* NAMEBYCOUNTRY_H */

