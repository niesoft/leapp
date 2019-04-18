#include "leapp.h"

leapp::leapp(QWidget *parent) :
	QWebEnginePage(parent) {
	view = new QWebEngineView();
	view->setPage(this);
	qDebug() << "start Leapp";
}

void leapp::show()
{
//	view->setMinimumSize(640, 480);
	view->setHtml("<script>function test(){ alert('test function'); return 'test return'; }</script><h1>test</h1>"
				  "<button onclick='alert(\"test\")'>проверка</button>"
				  "<button onclick='test();'>fun</button>");
	view->show();
	view->setMinimumSize(220, 140);
	view->resize(640, 480);
}

// Событие на alert();
void leapp::javaScriptAlert(const QUrl &securityOrigin, const QString &msg)
{
	qDebug() << msg;
	if (msg == "test") view->page()->runJavaScript("test()", [](const QVariant &v) { qDebug() << v.toString(); });
}
// Событие на сообщение в console.log();

