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
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenuForm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *TitleLabel;
    QLabel *BackgroundImage;
    QPushButton *NewButton;
    QPushButton *LoadButton;
    QPushButton *OptionsButton;
    QPushButton *ExitButton;
    QFrame *frame;

    void setupUi(QMainWindow *MainMenuForm)
    {
        if (MainMenuForm->objectName().isEmpty())
            MainMenuForm->setObjectName(QString::fromUtf8("MainMenuForm"));
        MainMenuForm->resize(806, 600);
        MainMenuForm->setMinimumSize(QSize(600, 400));
        MainMenuForm->setMaximumSize(QSize(1920, 1080));
        MainMenuForm->setContextMenuPolicy(Qt::NoContextMenu);
        MainMenuForm->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 85, 255, 255), stop:0.1 rgba(255, 255, 255, 255), stop:0.2 rgba(108, 224, 255, 167), stop:0.3 rgba(129, 190, 255, 92), stop:0.4 rgba(120, 215, 255, 51), stop:0.5 rgba(39, 89, 255, 205), stop:0.52 rgba(80, 74, 255, 205), stop:0.6 rgba(112, 131, 255, 84), stop:1 rgba(255, 255, 255, 0));"));
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
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        TitleLabel = new QLabel(centralwidget);
        TitleLabel->setObjectName(QString::fromUtf8("TitleLabel"));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        TitleLabel->setFont(font);
        TitleLabel->setAutoFillBackground(false);
        TitleLabel->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255, 255, 255);"));
        TitleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(TitleLabel);

        BackgroundImage = new QLabel(centralwidget);
        BackgroundImage->setObjectName(QString::fromUtf8("BackgroundImage"));
        sizePolicy.setHeightForWidth(BackgroundImage->sizePolicy().hasHeightForWidth());
        BackgroundImage->setSizePolicy(sizePolicy);
        BackgroundImage->setMinimumSize(QSize(300, 200));
        BackgroundImage->setMaximumSize(QSize(1920, 1080));
        BackgroundImage->setAutoFillBackground(false);
        BackgroundImage->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 0, 0, 0), stop:0.52 rgba(0, 0, 0, 0), stop:0.565 rgba(82, 121, 76, 33), stop:0.65 rgba(59, 122, 195, 64), stop:0.721925 rgba(85, 139, 223, 129), stop:0.77 rgba(94, 128, 196, 204), stop:0.89 rgba(99, 128, 255, 64), stop:1 rgba(0, 0, 0, 0));"));
        BackgroundImage->setPixmap(QPixmap(QString::fromUtf8("../../Documents/cults/robe.png")));
        BackgroundImage->setScaledContents(true);
        BackgroundImage->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(BackgroundImage);

        NewButton = new QPushButton(centralwidget);
        NewButton->setObjectName(QString::fromUtf8("NewButton"));
        NewButton->setMinimumSize(QSize(300, 40));
        NewButton->setMaximumSize(QSize(650, 150));
        NewButton->setCursor(QCursor(Qt::CrossCursor));
        NewButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
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
        NewButton->setAutoDefault(false);
        NewButton->setDefault(false);
        NewButton->setFlat(false);

        verticalLayout->addWidget(NewButton, 0, Qt::AlignHCenter);

        LoadButton = new QPushButton(centralwidget);
        LoadButton->setObjectName(QString::fromUtf8("LoadButton"));
        LoadButton->setMinimumSize(QSize(300, 40));
        LoadButton->setMaximumSize(QSize(600, 150));
        LoadButton->setCursor(QCursor(Qt::CrossCursor));
        LoadButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
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

        verticalLayout->addWidget(LoadButton, 0, Qt::AlignHCenter);

        OptionsButton = new QPushButton(centralwidget);
        OptionsButton->setObjectName(QString::fromUtf8("OptionsButton"));
        OptionsButton->setMinimumSize(QSize(300, 40));
        OptionsButton->setMaximumSize(QSize(600, 150));
        OptionsButton->setCursor(QCursor(Qt::CrossCursor));
        OptionsButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
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

        verticalLayout->addWidget(OptionsButton, 0, Qt::AlignHCenter);

        ExitButton = new QPushButton(centralwidget);
        ExitButton->setObjectName(QString::fromUtf8("ExitButton"));
        ExitButton->setMinimumSize(QSize(300, 40));
        ExitButton->setMaximumSize(QSize(600, 150));
        ExitButton->setCursor(QCursor(Qt::CrossCursor));
        ExitButton->setStyleSheet(QString::fromUtf8("QPushButton:hover:!pressed\n"
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

        verticalLayout->addWidget(ExitButton, 0, Qt::AlignHCenter);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainMenuForm->setCentralWidget(centralwidget);

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
