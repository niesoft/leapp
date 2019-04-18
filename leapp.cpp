#include "leapp.h"

leapp::leapp(QWidget *parent) :
	QWebEnginePage(parent) {
	view = new QWebEngineView();
	view->setPage(this);
	qDebug() << "start Leapp";
}

void leapp::show()
{
	view->setHtml("<script>function test(){ alert('test function'); return 'test return'; }</script><h1>test</h1>"
				  "<button onclick='alert(\"test\")'>проверка</button>"
				  "<button onclick='test();'>fun</button>");
	view->show();
	view->setMinimumSize(220, 140);
	view->resize(640, 480);
	tools.debug(__FUNCTION__, "test");
}

// Событие на alert();
void leapp::javaScriptAlert(const QUrl &securityOrigin, const QString &message)
{
//	debug(__FUNCTION__, message);
	Q_UNUSED(securityOrigin);
	qDebug() << message;
	if (message == "test") view->page()->runJavaScript("test()", [](const QVariant &v) { qDebug() << v.toString(); });
}
// Событие на сообщение в console.log();
void leapp::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID) {
	Q_UNUSED(level); Q_UNUSED(lineNumber); Q_UNUSED(sourceID);
	qDebug() << message;
}
