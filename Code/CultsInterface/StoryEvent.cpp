/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoryEvent.cpp
 * Author: scott
 * 
 * Created on 11 June 2017, 11:26 PM
 */

#include "StoryEvent.h"

StoryEvent::StoryEvent() {
}

StoryEvent::StoryEvent(const StoryEvent& orig) {
}

StoryEvent::~StoryEvent() {
}

bool StoryEvent::operator==(const StoryEvent& ev) const {
    if (m_id == ev.getId()) {
        return true;
    }
    return false;
}

int StoryEvent::getId() const {
    return m_id;
}

void StoryEvent::setId(int id) {
    m_id = id;
}
