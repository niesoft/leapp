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

class leapp : public QWebEnginePage {

public:
	explicit leapp(QWidget *parent = nullptr);
	void show();
	QWebEngineView *view;

	void javaScriptAlert(const QUrl &securityOrigin, const QString &msg);
};

#endif // LEAAP_H
