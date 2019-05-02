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
#include <QThread>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebChannel>
#include <QJsonObject>
#include <QResource>
#include "viewpage.h"
#include "tools.h"
#include "sql.h"
#include "transport.h"

inline void initMyResource() {
    Q_INIT_RESOURCE(res);
}

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
	void trayClick(QSystemTrayIcon::ActivationReason reason);
	void trayMenuClick(QAction * action);
	void trayIconSet(QPixmap icon);
	void trayMenuSet(QStringList list);
	void trayMessageShow(QString title, QString msg, QString type = "0", int msec = 10000);
	QString setProperties();

	QString fileOpen(QString filename);

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent * event);
	void moveEvent(QMoveEvent *event);

private:
	Ui::Leapp *ui;
public slots:
	void loadFinished();
	void loadProgress();
	void loadStarted();
};

#endif // LEAPP_H
