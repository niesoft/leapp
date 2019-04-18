#ifndef LEAAP_H
#define LEAAP_H


#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QMenu>
#include <QDebug>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>
#include "leapptools.h"

class leapp : public QWebEnginePage {

public:
	explicit leapp(QWidget *parent = nullptr);
	QWebEngineView *view;
	LEAppTools tools;
	QSystemTrayIcon *tray;
	QMenu *menu;

	void show();
	void setTray();
	void setTrayIcon(QIcon icon);
	void setWindowIcon(QIcon icon);
	void setWindowTitle(QString title);
	void showTrayMessage(QString title, QString msg, int type = 0, int msec = 10000);

	void javaScriptAlert(const QUrl &securityOrigin, const QString &message);
	void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
public slots:
	void trayClick(QSystemTrayIcon::ActivationReason reason);
	void trayMenuClick(QAction *action);
};

#endif // LEAAP_H
