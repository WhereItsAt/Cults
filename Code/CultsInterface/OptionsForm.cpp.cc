/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   OptionsForm.cpp
 * Author: scott
 *
 * Created on 9 September 2017, 9:31 PM
 */

#include "OptionsForm.h"

OptionsForm::OptionsForm() {
    widget.setupUi(this);
    
    QPushButton *Exit = this->findChild<QPushButton*>("mainMenuButton");
    connect(Exit, SIGNAL(clicked()), this, SLOT(CloseOptions()));
}

OptionsForm::~OptionsForm() {
}

void OptionsForm::CloseOptions() {
    this->close();
}
