#include "viewpage.h"
#include <QDebug>

ViewPage::ViewPage(QObject * parent, Leapp * leapp)
	: QWebEnginePage(parent){
	this->leapp = leapp;
}


