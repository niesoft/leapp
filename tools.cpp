#include "tools.h"

Tools::Tools(){}

// Вывод сообщений в консоль
void Tools::debug(QString fname, const QVariant &v)
{
	if (debugenable) {
		qDebug() << "[" + getTime() + "] " + fname + "():";
		qDebug() << v;
	}
}
// Текущее время
QString Tools::getTime()
{
	return QString::fromStdString(QTime::currentTime().toString("HH:mm:ss").toStdString());
}
// Пингуем корневой сервер что бы проверить подключение к глобальной паутине.
bool Tools::isOnline()
{
	#if defined(WIN32)
	   QString parameter = "-n 1";
	#else
	   QString parameter = "-c 1";
	#endif
	int exitCode = QProcess::execute("ping", QStringList() << parameter << "198.41.0.4");
	return (exitCode == 0) ? true : false;
}
QString Tools::getPath()
{
	return "";
}
QString Tools::fileOpen(QString filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	in.setCodec("UTF-8");
	QString line = in.readAll();
	file.close();
	return line;
}
