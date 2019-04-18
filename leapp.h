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
	void show();
	QWebEngineView *view;
	LEAppTools tools;
	QSystemTrayIcon *tray;
	void setTrayIcon(QIcon icon);
	void setTray();
	void setWindowIcon(QIcon icon);
	void setWindowTitle(QString title);

	void javaScriptAlert(const QUrl &securityOrigin, const QString &message);
	void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
public slots:
	void trayClick(QSystemTrayIcon::ActivationReason reason);
};

#endif // LEAAP_H
