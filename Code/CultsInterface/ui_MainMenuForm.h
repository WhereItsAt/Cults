/********************************************************************************
** Form generated from reading UI file 'MainMenuForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUFORM_H
#define UI_MAINMENUFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenuForm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QVBoxLayout *verticalLayout;
    QLabel *TitleLabel;
    QLabel *BackgroundImage;
    QPushButton *NewButton;
    QPushButton *LoadButton;
    QPushButton *OptionsButton;
    QPushButton *ExitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainMenuForm)
    {
        if (MainMenuForm->objectName().isEmpty())
            MainMenuForm->setObjectName(QString::fromUtf8("MainMenuForm"));
        MainMenuForm->resize(806, 600);
        MainMenuForm->setMinimumSize(QSize(600, 400));
        MainMenuForm->setMaximumSize(QSize(1920, 1080));
        MainMenuForm->setContextMenuPolicy(Qt::NoContextMenu);
        MainMenuForm->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainMenuForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(600, 400));
        centralwidget->setMaximumSize(QSize(1920, 1080));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout1 = new QGridLayout();
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        TitleLabel = new QLabel(centralwidget);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        TitleLabel->setFont(font);
        TitleLabel->setStyleSheet(QString::fromUtf8("color : rgb(255, 255, 255)"));
        TitleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(TitleLabel);

        BackgroundImage = new QLabel(centralwidget);
        BackgroundImage->setObjectName(QString::fromUtf8("BackgroundImage"));
        sizePolicy.setHeightForWidth(BackgroundImage->sizePolicy().hasHeightForWidth());
        BackgroundImage->setSizePolicy(sizePolicy);
        BackgroundImage->setMinimumSize(QSize(300, 200));
        BackgroundImage->setMaximumSize(QSize(1920, 1080));
        BackgroundImage->setAutoFillBackground(true);
        BackgroundImage->setPixmap(QPixmap(QString::fromUtf8("../../Documents/cults/robe.png")));
        BackgroundImage->setScaledContents(true);
        BackgroundImage->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(BackgroundImage);

        NewButton = new QPushButton(centralwidget);
        NewButton->setObjectName(QString::fromUtf8("NewButton"));
        NewButton->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(NewButton, 0, Qt::AlignHCenter);

        LoadButton = new QPushButton(centralwidget);
        LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
        LoadButton->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(LoadButton, 0, Qt::AlignHCenter);

        OptionsButton = new QPushButton(centralwidget);
        OptionsButton->setObjectName(QString::fromUtf8("OptionsButton"));
        OptionsButton->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(OptionsButton, 0, Qt::AlignHCenter);

        ExitButton = new QPushButton(centralwidget);
        ExitButton->setObjectName(QString::fromUtf8("ExitButton"));
        ExitButton->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(ExitButton, 0, Qt::AlignHCenter);


        gridLayout1->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);

        MainMenuForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainMenuForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 806, 25));
        MainMenuForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainMenuForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setEnabled(false);
        MainMenuForm->setStatusBar(statusbar);

        retranslateUi(MainMenuForm);

        QMetaObject::connectSlotsByName(MainMenuForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainMenuForm)
    {
        MainMenuForm->setWindowTitle(QApplication::translate("MainMenuForm", "MainMenuForm", 0, QApplication::UnicodeUTF8));
        TitleLabel->setText(QApplication::translate("MainMenuForm", "Cults", 0, QApplication::UnicodeUTF8));
        BackgroundImage->setText(QString());
        NewButton->setText(QApplication::translate("MainMenuForm", "New Game", 0, QApplication::UnicodeUTF8));
        LoadButton->setText(QApplication::translate("MainMenuForm", "Load Game", 0, QApplication::UnicodeUTF8));
        OptionsButton->setText(QApplication::translate("MainMenuForm", "Options", 0, QApplication::UnicodeUTF8));
        ExitButton->setText(QApplication::translate("MainMenuForm", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainMenuForm: public Ui_MainMenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUFORM_H
