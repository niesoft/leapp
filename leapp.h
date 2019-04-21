#pragma once
#ifndef LEAPP_H
#define LEAPP_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QtDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QWebEngineProfile>
#include <QWebChannel>
#include <QJsonObject>
#include "viewpage.h"
#include "tools.h"
#include "sql.h"
#include "transport.h"


namespace Ui {
class Leapp;
}

#include <QWebEnginePage>

class Leapp : public QMainWindow
{
	Q_OBJECT

public:
	explicit Leapp(QWidget *parent = nullptr);
	~Leapp();

	QSize startsize = QSize(640,480);
	QSize minimalsize = QSize(140,220);
	QSize maximalsize = QSize(9999,9999);
	int windowstatedefault = 0;
	bool trayenable = true;
	bool traymenuenable = true;
	int temp;

	ViewPage * page;
	QSystemTrayIcon * tray;
	QMenu * menu;
	SQL * sql;
	QPixmap icon;
	Tools tools;
	QWebChannel * channel;
	Transport * transport;

	void start();
	void loadHtml(QUrl url = QUrl("qrc:/html/index.html"));
	void command(QString command = "");
	void windowStateSet(QString state);
	void windowStyleSet(QString style);
	void trayClick(QSystemTrayIcon::ActivationReason reason);
	void trayMenuClick(QAction * action);
	void trayIconSet(QPixmap icon);
	void trayMenuSet(QStringList list);
	void trayMessageShow(QString title, QString msg, QString type = "0", int msec = 10000);

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent * event);
	void moveEvent(QMoveEvent *event);

private:
	Ui::Leapp *ui;
public slots:
	QString onKeysExtracted(QStringList keys);
};

#endif // LEAPP_H
