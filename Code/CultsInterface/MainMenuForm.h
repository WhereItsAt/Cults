/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainMenuForm.h
 * Author: scott
 *
 * Created on 27 May 2017, 5:30 PM
 */

#ifndef _MAINMENUFORM_H
#define _MAINMENUFORM_H

#include "ui_MainMenuForm.h"

class MainMenuForm : public QMainWindow {
    Q_OBJECT
public:
    MainMenuForm();
    virtual ~MainMenuForm();
private:
    Ui::MainMenuForm widget;
    public slots:
        void QuitApp();
};

#endif /* _MAINMENUFORM_H */
