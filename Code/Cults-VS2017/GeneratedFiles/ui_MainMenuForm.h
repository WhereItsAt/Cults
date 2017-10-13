/********************************************************************************
** Form generated from reading UI file 'MainMenuForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUFORM_H
#define UI_MAINMENUFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            MainMenuForm->setObjectName(QStringLiteral("MainMenuForm"));
        MainMenuForm->resize(806, 600);
        MainMenuForm->setMinimumSize(QSize(600, 400));
        MainMenuForm->setMaximumSize(QSize(1920, 1080));
        MainMenuForm->setContextMenuPolicy(Qt::NoContextMenu);
        MainMenuForm->setStyleSheet(QStringLiteral("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 85, 255, 255), stop:0.1 rgba(255, 255, 255, 255), stop:0.2 rgba(108, 224, 255, 167), stop:0.3 rgba(129, 190, 255, 92), stop:0.4 rgba(120, 215, 255, 51), stop:0.5 rgba(39, 89, 255, 205), stop:0.52 rgba(80, 74, 255, 205), stop:0.6 rgba(112, 131, 255, 84), stop:1 rgba(255, 255, 255, 0));"));
        centralwidget = new QWidget(MainMenuForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(600, 400));
        centralwidget->setMaximumSize(QSize(1920, 1080));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        TitleLabel = new QLabel(centralwidget);
        TitleLabel->setObjectName(QStringLiteral("TitleLabel"));
        QFont font;
        font.setPointSize(35);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        TitleLabel->setFont(font);
        TitleLabel->setAutoFillBackground(false);
        TitleLabel->setStyleSheet(QLatin1String("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255, 255, 255);"));
        TitleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(TitleLabel);

        BackgroundImage = new QLabel(centralwidget);
        BackgroundImage->setObjectName(QStringLiteral("BackgroundImage"));
        sizePolicy.setHeightForWidth(BackgroundImage->sizePolicy().hasHeightForWidth());
        BackgroundImage->setSizePolicy(sizePolicy);
        BackgroundImage->setMinimumSize(QSize(300, 200));
        BackgroundImage->setMaximumSize(QSize(1920, 1080));
        BackgroundImage->setAutoFillBackground(false);
        BackgroundImage->setStyleSheet(QStringLiteral("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 0, 0, 0), stop:0.52 rgba(0, 0, 0, 0), stop:0.565 rgba(82, 121, 76, 33), stop:0.65 rgba(59, 122, 195, 64), stop:0.721925 rgba(85, 139, 223, 129), stop:0.77 rgba(94, 128, 196, 204), stop:0.89 rgba(99, 128, 255, 64), stop:1 rgba(0, 0, 0, 0));"));
        BackgroundImage->setPixmap(QPixmap(QString::fromUtf8("../../Documents/cults/robe.png")));
        BackgroundImage->setScaledContents(true);
        BackgroundImage->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(BackgroundImage);

        NewButton = new QPushButton(centralwidget);
        NewButton->setObjectName(QStringLiteral("NewButton"));
        NewButton->setMinimumSize(QSize(300, 40));
        NewButton->setMaximumSize(QSize(650, 150));
        NewButton->setCursor(QCursor(Qt::CrossCursor));
        NewButton->setStyleSheet(QLatin1String("QPushButton:hover:!pressed\n"
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
        NewButton->setFlat(false);

        verticalLayout->addWidget(NewButton, 0, Qt::AlignHCenter);

        LoadButton = new QPushButton(centralwidget);
        LoadButton->setObjectName(QStringLiteral("LoadButton"));
        LoadButton->setMinimumSize(QSize(300, 40));
        LoadButton->setMaximumSize(QSize(600, 150));
        LoadButton->setCursor(QCursor(Qt::CrossCursor));
        LoadButton->setStyleSheet(QLatin1String("QPushButton:hover:!pressed\n"
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
        OptionsButton->setObjectName(QStringLiteral("OptionsButton"));
        OptionsButton->setMinimumSize(QSize(300, 40));
        OptionsButton->setMaximumSize(QSize(600, 150));
        OptionsButton->setCursor(QCursor(Qt::CrossCursor));
        OptionsButton->setStyleSheet(QLatin1String("QPushButton:hover:!pressed\n"
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
        ExitButton->setObjectName(QStringLiteral("ExitButton"));
        ExitButton->setMinimumSize(QSize(300, 40));
        ExitButton->setMaximumSize(QSize(600, 150));
        ExitButton->setCursor(QCursor(Qt::CrossCursor));
        ExitButton->setStyleSheet(QLatin1String("QPushButton:hover:!pressed\n"
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
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainMenuForm->setCentralWidget(centralwidget);

        retranslateUi(MainMenuForm);

        NewButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainMenuForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainMenuForm)
    {
        MainMenuForm->setWindowTitle(QApplication::translate("MainMenuForm", "MainMenuForm", Q_NULLPTR));
        TitleLabel->setText(QApplication::translate("MainMenuForm", "Cults", Q_NULLPTR));
        BackgroundImage->setText(QString());
        NewButton->setText(QApplication::translate("MainMenuForm", "New Game", Q_NULLPTR));
        LoadButton->setText(QApplication::translate("MainMenuForm", "Load Game", Q_NULLPTR));
        OptionsButton->setText(QApplication::translate("MainMenuForm", "Options", Q_NULLPTR));
        ExitButton->setText(QApplication::translate("MainMenuForm", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainMenuForm: public Ui_MainMenuForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUFORM_H
