/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: scott
 *
 * Created on 27 May 2017, 4:28 PM
 */

#include <QApplication>
#include "MainMenuForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    MainMenuForm form;
    form.showFullScreen();
    
    return app.exec();
}
