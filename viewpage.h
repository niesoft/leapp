#pragma once
#ifndef VIEWPAGE_H
#define VIEWPAGE_H

#include <QWebEnginePage>
#include "tools.h"

class Leapp;

class ViewPage : public QWebEnginePage{
	Q_OBJECT
public:
	explicit ViewPage(QObject *parent = nullptr, Leapp * leapp = nullptr);
	Leapp * leapp;
	Tools tools;
protected:
	void javaScriptAlert(const QUrl &securityOrigin, const QString &message);
	void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
};

#endif
