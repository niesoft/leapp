#ifndef LEAPPTOOLS_H
#define LEAPPTOOLS_H

#include <QString>
#include <QVariant>
#include <QDebug>
#include <QTime>

class LEAppTools
{
public:
	LEAppTools();
	void debug(QString fname, const QVariant &v);
	QString getTime();
};

#endif // LEAPPTOOLS_H
