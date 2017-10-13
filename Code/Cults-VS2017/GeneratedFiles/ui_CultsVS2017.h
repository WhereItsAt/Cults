/********************************************************************************
** Form generated from reading UI file 'CultsVS2017.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CULTSVS2017_H
#define UI_CULTSVS2017_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CultsVS2017Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CultsVS2017Class)
    {
        if (CultsVS2017Class->objectName().isEmpty())
            CultsVS2017Class->setObjectName(QStringLiteral("CultsVS2017Class"));
        CultsVS2017Class->resize(600, 400);
        menuBar = new QMenuBar(CultsVS2017Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CultsVS2017Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CultsVS2017Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CultsVS2017Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(CultsVS2017Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CultsVS2017Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CultsVS2017Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CultsVS2017Class->setStatusBar(statusBar);

        retranslateUi(CultsVS2017Class);

        QMetaObject::connectSlotsByName(CultsVS2017Class);
    } // setupUi

    void retranslateUi(QMainWindow *CultsVS2017Class)
    {
        CultsVS2017Class->setWindowTitle(QApplication::translate("CultsVS2017Class", "CultsVS2017", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CultsVS2017Class: public Ui_CultsVS2017Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CULTSVS2017_H
