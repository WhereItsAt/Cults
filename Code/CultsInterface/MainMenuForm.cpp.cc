/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MainMenuForm.cpp
 * Author: scott
 *
 * Created on 27 May 2017, 5:30 PM
 */

#include "MainMenuForm.h"
#include <QConicalGradient>
#include <QPalette>
#include <QColor>

MainMenuForm::MainMenuForm() {
    widget.setupUi(this);
    QPushButton *Exit = this->findChild<QPushButton*>("ExitButton");
    connect(Exit, SIGNAL(clicked()), this, SLOT(QuitApp()));
    
    QWidget *BGGradient = new QWidget(this->findChild<QWidget*>("BackgroundImage"));
    BGGradient->setFixedHeight(this->height());
    BGGradient->setFixedWidth(this->width());
    BGGradient->lower();
    QConicalGradient * grad = new QConicalGradient(QPointF((this->height()/2),(this->width()/2)),90);
    grad->setColorAt(0, QColor(7,16,61));
    grad->setColorAt(0.5, QColor(21,33,96));
    grad->setColorAt(1, QColor(54,71,155));
    QPalette pal = QApplication::palette();
    pal.setBrush(QPalette::Base, *grad);
    BGGradient->setPalette(pal);
    BGGradient->setEnabled(true);
    BGGradient->setVisible(true);
    BGGradient->setShown(true);
}

MainMenuForm::~MainMenuForm() {
}

void MainMenuForm::QuitApp() {
    QApplication::quit();
}
