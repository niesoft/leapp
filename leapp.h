#ifndef LEAAP_H
#define LEAAP_H

#include "tools.h"

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QMenu>
#include <QDebug>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>

class leapp : public QWebEnginePage {

public:
	explicit leapp(QWidget *parent = nullptr);
	void show();
	QWebEngineView *view;
	QSystemTrayIcon *tray;
	Tools *tools;

	void javaScriptAlert(const QUrl &securityOrigin, const QString &message);
	void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
};

#endif // LEAAP_H
