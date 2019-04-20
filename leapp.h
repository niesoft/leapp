#pragma once
#ifndef LEAPP_H
#define LEAPP_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QtDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QWebEngineProfile>
#include "viewpage.h"
#include "tools.h"


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

	ViewPage *page;
	QSystemTrayIcon *tray;
	QMenu *menu;
	QPixmap icon;
	Tools tools;

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

private:
	Ui::Leapp *ui;
};

#endif // LEAPP_H
