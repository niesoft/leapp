#pragma once
#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QVariant>
#include <QDebug>
#include <QTime>
#include <QProcess>
#include <QFile>


class Tools
{
public:
	Tools();

	bool debugenable = true;
	QString path = "";

	void start();
	void debug(QString fname, const QVariant &v = "");
	bool isOnline();
	QString getPath();
	QString getTime();
	QString fileOpen(QString filename);
};

#endif // TOOLS_H
