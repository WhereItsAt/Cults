/********************************************************************************
** Form generated from reading UI file 'OptionsForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSFORM_H
#define UI_OPTIONSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsForm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *TitleLabel;
    QLabel *Picture;
    QPushButton *mainMenuButton;
    QSpacerItem *verticalSpacer;
    QPushButton *DisplayButton;
    QPushButton *soundButton;
    QPushButton *gameplayButton;
    QPushButton *GraphicsButton;

    void setupUi(QMainWindow *OptionsForm)
    {
        if (OptionsForm->objectName().isEmpty())
            OptionsForm->setObjectName(QString::fromUtf8("OptionsForm"));
        OptionsForm->resize(800, 809);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OptionsForm->sizePolicy().hasHeightForWidth());
        OptionsForm->setSizePolicy(sizePolicy);
        OptionsForm->setMinimumSize(QSize(600, 400));
        OptionsForm->setMaximumSize(QSize(1920, 1080));
        OptionsForm->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 85, 255, 255), stop:0.1 rgba(255, 255, 255, 255), stop:0.2 rgba(108, 224, 255, 167), stop:0.3 rgba(129, 190, 255, 92), stop:0.4 rgba(120, 215, 255, 51), stop:0.5 rgba(39, 89, 255, 205), stop:0.52 rgba(80, 74, 255, 205), stop:0.6 rgba(112, 131, 255, 84), stop:1 rgba(255, 255, 255, 0));"));
        centralwidget = new QWidget(OptionsForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TitleLabel = new QLabel(centralwidget);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        TitleLabel->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        TitleLabel->setFont(font);
        TitleLabel->setAutoFillBackground(false);
        TitleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255,255,255);"));
        TitleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(TitleLabel, 1, 0, 1, 1);

        Picture = new QLabel(centralwidget);
        Picture->setObjectName(QString::fromUtf8("Picture"));
        Picture->setMinimumSize(QSize(300, 200));
        Picture->setMaximumSize(QSize(1920, 1080));
        Picture->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 0, 0, 0), stop:0.52 rgba(0, 0, 0, 0), stop:0.565 rgba(82, 121, 76, 33), stop:0.65 rgba(59, 122, 195, 64), stop:0.721925 rgba(85, 139, 223, 129), stop:0.77 rgba(94, 128, 196, 204), stop:0.89 rgba(99, 128, 255, 64), stop:1 rgba(0, 0, 0, 0));"));
        Picture->setPixmap(QPixmap(QString::fromUtf8("../../Documents/cults/robe.png")));
        Picture->setScaledContents(true);

        gridLayout->addWidget(Picture, 2, 0, 1, 1);

        mainMenuButton = new QPushButton(centralwidget);
        mainMenuButton->setObjectName(QString::fromUtf8("mainMenuButton"));
        mainMenuButton->setMinimumSize(QSize(300, 40));
        mainMenuButton->setMaximumSize(QSize(300, 40));
        mainMenuButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	background-color: rgba(255, 255, 255, 25);\n"
"	color: rgb(0,0,0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgba(0,0,0,255);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	background-color: rgba(255,255,255,25);\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));

        gridLayout->addWidget(mainMenuButton, 9, 0, 1, 1, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 8, 0, 1, 1);

        DisplayButton = new QPushButton(centralwidget);
        DisplayButton->setObjectName(QString::fromUtf8("DisplayButton"));
        DisplayButton->setMinimumSize(QSize(300, 40));
        DisplayButton->setMaximumSize(QSize(300, 40));
        DisplayButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	background-color: rgba(255, 255, 255, 25);\n"
"	color: rgb(0,0,0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgba(0,0,0,255);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	background-color: rgba(255,255,255,25);\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));

        gridLayout->addWidget(DisplayButton, 7, 0, 1, 1, Qt::AlignHCenter);

        soundButton = new QPushButton(centralwidget);
        soundButton->setObjectName(QString::fromUtf8("soundButton"));
        soundButton->setMinimumSize(QSize(300, 40));
        soundButton->setMaximumSize(QSize(300, 40));
        soundButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	background-color: rgba(255, 255, 255, 25);\n"
"	color: rgb(0,0,0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgba(0,0,0,255);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	background-color: rgba(255,255,255,25);\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));

        gridLayout->addWidget(soundButton, 4, 0, 1, 1, Qt::AlignHCenter);

        gameplayButton = new QPushButton(centralwidget);
        gameplayButton->setObjectName(QString::fromUtf8("gameplayButton"));
        gameplayButton->setMinimumSize(QSize(300, 40));
        gameplayButton->setMaximumSize(QSize(300, 40));
        gameplayButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	background-color: rgba(255, 255, 255, 25);\n"
"	color: rgb(0,0,0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgba(0,0,0,255);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	background-color: rgba(255,255,255,25);\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));

        gridLayout->addWidget(gameplayButton, 6, 0, 1, 1, Qt::AlignHCenter);

        GraphicsButton = new QPushButton(centralwidget);
        GraphicsButton->setObjectName(QString::fromUtf8("GraphicsButton"));
        GraphicsButton->setMinimumSize(QSize(300, 40));
        GraphicsButton->setMaximumSize(QSize(300, 40));
        GraphicsButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	background-color: rgba(255, 255, 255, 25);\n"
"	color: rgb(0,0,0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgba(0,0,0,255);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	background-color: rgba(255,255,255,25);\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
""));

        gridLayout->addWidget(GraphicsButton, 3, 0, 1, 1, Qt::AlignHCenter);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        OptionsForm->setCentralWidget(centralwidget);

        retranslateUi(OptionsForm);

        QMetaObject::connectSlotsByName(OptionsForm);
    } // setupUi

    void retranslateUi(QMainWindow *OptionsForm)
    {
        OptionsForm->setWindowTitle(QApplication::translate("OptionsForm", "OptionsForm", 0, QApplication::UnicodeUTF8));
        TitleLabel->setText(QApplication::translate("OptionsForm", "Options", 0, QApplication::UnicodeUTF8));
        Picture->setText(QString());
        mainMenuButton->setText(QApplication::translate("OptionsForm", "Back to Main Menu", 0, QApplication::UnicodeUTF8));
        DisplayButton->setText(QApplication::translate("OptionsForm", "Display", 0, QApplication::UnicodeUTF8));
        soundButton->setText(QApplication::translate("OptionsForm", "Sound", 0, QApplication::UnicodeUTF8));
        gameplayButton->setText(QApplication::translate("OptionsForm", "Gameplay", 0, QApplication::UnicodeUTF8));
        GraphicsButton->setText(QApplication::translate("OptionsForm", "Graphics", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsForm: public Ui_OptionsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSFORM_H
