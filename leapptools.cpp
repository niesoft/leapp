#include "leapptools.h"

LEAppTools::LEAppTools()
{

}

// Вывод сообщений в консоль
void LEAppTools::debug(QString fname, const QVariant &v)
{
	if (isdebug) {
		qDebug() << "[" + getTime() + "] " + fname + "():";
		qDebug() << v;
	}
}
// Текущее время
QString LEAppTools::getTime()
{
	return QString::fromStdString(QTime::currentTime().toString("HH:mm:ss").toStdString());
}
// Пингуем корневой сервер что бы проверить подключение к глобальной паутине.
bool LEAppTools::isOnline()
{
	#if defined(WIN32)
	   QString parameter = "-n 1";
	#else
	   QString parameter = "-c 1";
	#endif
	int exitCode = QProcess::execute("ping", QStringList() << parameter << "198.41.0.4");
	return (exitCode == 0) ? true : false;
}
