#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CultsVS2017.h"

class CultsVS2017 : public QMainWindow
{
	Q_OBJECT

public:
	CultsVS2017(QWidget *parent = Q_NULLPTR);

private:
	Ui::CultsVS2017Class ui;
};
