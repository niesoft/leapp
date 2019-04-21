#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QObject>

class Leapp;

class Transport : public QObject
{
	Q_OBJECT
public:
	explicit Transport(Leapp *parent = nullptr);
	Leapp * leapp;
signals:

public slots:
	QString onKeysExtracted(QStringList keys);
};

#endif // TRANSPORT_H
