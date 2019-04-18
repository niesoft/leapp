#include "leapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	leapp leapp;
	leapp.show();
	return a.exec();
}
