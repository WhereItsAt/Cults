/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OptionsForm.h
 * Author: scott
 *
 * Created on 9 September 2017, 9:31 PM
 */

#ifndef _OPTIONSFORM_H
#define _OPTIONSFORM_H

#include "ui_OptionsForm.h"

class OptionsForm : public QMainWindow {
    Q_OBJECT
public:
    OptionsForm();
    virtual ~OptionsForm();
private:
    Ui::OptionsForm widget;
    
        public slots:
            void CloseOptions();
        
};

#endif /* _OPTIONSFORM_H */
