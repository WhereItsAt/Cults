/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bureaucrat.h
 * Author: scott
 *
 * Created on 3 June 2017, 10:33 PM
 */

#ifndef BUREAUCRAT_H
#define BUREAUCRAT_H

#include "Specialist.h"

class Bureaucrat: public Specialist {
public:
    Bureaucrat();
    Bureaucrat(const Bureaucrat& orig);
    virtual ~Bureaucrat();
private:

};

#endif /* BUREAUCRAT_H */

