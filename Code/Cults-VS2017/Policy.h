/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Policy.h
 * Author: scott
 *
 * Created on 3 June 2017, 8:32 PM
 */

#ifndef POLICY_H
#define POLICY_H

class Policy {
public:
    Policy();
    Policy(const Policy& orig);
    virtual ~Policy();
    bool operator==(const Policy &pol) const;
    std::string getName() const;
    void setName(std::string name);
private:
    std::string m_name;
};

#endif /* POLICY_H */

