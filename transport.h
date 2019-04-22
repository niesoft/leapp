#pragma once
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QObject>
#include <QJsonObject>

class Leapp;

class Transport : public QObject
{
	Q_OBJECT
public:
	explicit Transport(Leapp *parent = nullptr);
	Leapp * leapp;

public slots:
	QJsonObject resize(int w = -1, int h = -1);
	QJsonObject move(int x = -1, int y = -1);
	void title(QString title = " ");
	void show();
	void hide();
	void exit();
	void reload(QString url = "");
	void state(int s = 0);
	void style(int style = 0);
	QJsonObject sql(QString query);

};

#endif // TRANSPORT_H
