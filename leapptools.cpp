#include "leapptools.h"

LEAppTools::LEAppTools()
{

}

void LEAppTools::debug(QString fname, const QVariant &v)
{
	qInfo() << "[" + getTime() + "] " + fname + "():";
	qDebug() << v;
	qDebug() << "";
}
// Текущее время
QString LEAppTools::getTime()
{
	return QString::fromStdString(QTime::currentTime().toString("HH:mm:ss").toStdString());
}
