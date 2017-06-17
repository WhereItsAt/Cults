/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoryEvent.h
 * Author: scott
 *
 * Created on 11 June 2017, 11:26 PM
 */

#ifndef STORYEVENT_H
#define STORYEVENT_H

class StoryEvent {
public:
    StoryEvent();
    StoryEvent(const StoryEvent& orig);
    virtual ~StoryEvent();
    bool operator==(const StoryEvent &ev) const;
    int getId() const;
    void setId(int id);
private:
    int m_id;
};

#endif /* STORYEVENT_H */

