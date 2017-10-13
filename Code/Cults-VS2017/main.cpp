#include "CultsVS2017.h"
#include "MainMenuForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//CultsVS2017 w;
	//w.show();
	MainMenuForm form;
	form.showFullScreen();

	return a.exec();
}
