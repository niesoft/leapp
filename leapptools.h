#pragma once
#ifndef LEAPPTOOLS_H
#define LEAPPTOOLS_H

#include <QString>
#include <QVariant>
#include <QDebug>
#include <QTime>
#include <QProcess>

class LEAppTools
{
public:
	bool isdebug = true;
	QString path = "";

	LEAppTools();

	void debug(QString fname, const QVariant &v = "");

	bool isOnline();

	QString getTime();

private:
};

#endif // LEAPPTOOLS_H
