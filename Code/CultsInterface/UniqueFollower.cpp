/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UniqueFollower.cpp
 * Author: scott
 * 
 * Created on 3 June 2017, 10:27 PM
 */

#include "UniqueFollower.h"
#include "GoverningBody.h"
#include "FollowerManager.h"
#include "CEO.h"

UniqueFollower::UniqueFollower() {
}

UniqueFollower::UniqueFollower(const UniqueFollower& orig) {
}

UniqueFollower::~UniqueFollower() {
}

void UniqueFollower::contribute() {
    //same as contribute function for specialaists
    //akin to operate function for buildings/improvements
    //how much is contributed depends on their happiness/fear/etc
}

Leader* UniqueFollower::convertToLeader() {
    //leader has insanity/respect
    //need a way to convert unique follower traits in to leader traits
    //thus create an equivelant leader
    //delete unique follower and then call coup on government/cult replacing current leader with this one
    //choose type of leader based on cult type
    //DO NOT change cult type to suit unique follower
    
    //placeholder code added just so project would compile
    CEO* headHoncho = new CEO();
    return headHoncho;
}

void UniqueFollower::jumpShip() {
    m_cult->getFollowerManager()->removeUniqueFollower(this);
    m_preferredGBody->getFollowerManager()->addUniqueFollower(this);
    //recalculate stats eg fear, opinion, preferred GBody, etc
}
