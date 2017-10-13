/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameScreen.h
 * Author: scott
 *
 * Created on 10 September 2017, 1:05 AM
 */

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include "ui_GameScreen.h"

class GameScreen : public QMainWindow {
    //Q_OBJECT
public:
    GameScreen();
    virtual ~GameScreen();
private:
    Ui::GameScreen widget;
};

#endif /* _GAMESCREEN_H */
