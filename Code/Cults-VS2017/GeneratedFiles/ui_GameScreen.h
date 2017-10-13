/********************************************************************************
** Form generated from reading UI file 'GameScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESCREEN_H
#define UI_GAMESCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameScreen
{
public:
    QAction *actionNew_Game;
    QAction *actionLoad_Game;
    QAction *actionMain_Menu;
    QAction *actionExit;
    QAction *actionList_Cults;
    QAction *actionShow_Game_Info;
    QAction *actionShow_Map_Info;
    QAction *actionShow_Cult_Info;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuGame;
    QMenu *menuCults;
    QMenu *menuMap;
    QMenu *menuInfo;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameScreen)
    {
        if (GameScreen->objectName().isEmpty())
            GameScreen->setObjectName(QStringLiteral("GameScreen"));
        GameScreen->resize(800, 600);
        actionNew_Game = new QAction(GameScreen);
        actionNew_Game->setObjectName(QStringLiteral("actionNew_Game"));
        actionLoad_Game = new QAction(GameScreen);
        actionLoad_Game->setObjectName(QStringLiteral("actionLoad_Game"));
        actionMain_Menu = new QAction(GameScreen);
        actionMain_Menu->setObjectName(QStringLiteral("actionMain_Menu"));
        actionExit = new QAction(GameScreen);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionList_Cults = new QAction(GameScreen);
        actionList_Cults->setObjectName(QStringLiteral("actionList_Cults"));
        actionShow_Game_Info = new QAction(GameScreen);
        actionShow_Game_Info->setObjectName(QStringLiteral("actionShow_Game_Info"));
        actionShow_Map_Info = new QAction(GameScreen);
        actionShow_Map_Info->setObjectName(QStringLiteral("actionShow_Map_Info"));
        actionShow_Cult_Info = new QAction(GameScreen);
        actionShow_Cult_Info->setObjectName(QStringLiteral("actionShow_Cult_Info"));
        centralwidget = new QWidget(GameScreen);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        GameScreen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameScreen);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuGame = new QMenu(menubar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        menuCults = new QMenu(menubar);
        menuCults->setObjectName(QStringLiteral("menuCults"));
        menuMap = new QMenu(menubar);
        menuMap->setObjectName(QStringLiteral("menuMap"));
        menuInfo = new QMenu(menubar);
        menuInfo->setObjectName(QStringLiteral("menuInfo"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        GameScreen->setMenuBar(menubar);
        statusbar = new QStatusBar(GameScreen);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GameScreen->setStatusBar(statusbar);

        menubar->addAction(menuGame->menuAction());
        menubar->addAction(menuCults->menuAction());
        menubar->addAction(menuMap->menuAction());
        menubar->addAction(menuInfo->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuGame->addAction(actionNew_Game);
        menuGame->addAction(actionLoad_Game);
        menuGame->addAction(actionMain_Menu);
        menuGame->addAction(actionExit);
        menuCults->addAction(actionList_Cults);
        menuInfo->addAction(actionShow_Game_Info);
        menuInfo->addAction(actionShow_Map_Info);
        menuInfo->addAction(actionShow_Cult_Info);

        retranslateUi(GameScreen);

        QMetaObject::connectSlotsByName(GameScreen);
    } // setupUi

    void retranslateUi(QMainWindow *GameScreen)
    {
        GameScreen->setWindowTitle(QApplication::translate("GameScreen", "GameScreen", Q_NULLPTR));
        actionNew_Game->setText(QApplication::translate("GameScreen", "New Game", Q_NULLPTR));
        actionLoad_Game->setText(QApplication::translate("GameScreen", "Load Game", Q_NULLPTR));
        actionMain_Menu->setText(QApplication::translate("GameScreen", "Main Menu", Q_NULLPTR));
        actionExit->setText(QApplication::translate("GameScreen", "Exit", Q_NULLPTR));
        actionList_Cults->setText(QApplication::translate("GameScreen", "List Cults", Q_NULLPTR));
        actionShow_Game_Info->setText(QApplication::translate("GameScreen", "Show Game Info", Q_NULLPTR));
        actionShow_Map_Info->setText(QApplication::translate("GameScreen", "Show Map Info", Q_NULLPTR));
        actionShow_Cult_Info->setText(QApplication::translate("GameScreen", "Show Cult Info", Q_NULLPTR));
        menuGame->setTitle(QApplication::translate("GameScreen", "Game", Q_NULLPTR));
        menuCults->setTitle(QApplication::translate("GameScreen", "Cults", Q_NULLPTR));
        menuMap->setTitle(QApplication::translate("GameScreen", "Map", Q_NULLPTR));
        menuInfo->setTitle(QApplication::translate("GameScreen", "Info", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("GameScreen", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameScreen: public Ui_GameScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCREEN_H
