#include "leapp.h"

leapp::leapp(QWidget *parent) :
	QWebEnginePage(parent) {
	tools.debug(__FUNCTION__, "Starting Leapp...");
	view = new QWebEngineView();
	tray = new QSystemTrayIcon();
	menu = new QMenu("leappMenu");
	view->setPage(this);
	connect(tray, &QSystemTrayIcon::activated, this, &leapp::trayClick);
	connect(menu, &QMenu::triggered, this, &leapp::trayMenuClick);
}

void leapp::show()
{
	tools.debug(__FUNCTION__);
	view->setHtml("<script>function test(){ alert('test function'); return 'test return'; }</script><h1>test</h1>"
				  "<button onclick='alert(\"test\")'>проверка</button>"
				  "<button onclick='test();'>fun</button>");
	view->show();
	view->setMinimumSize(220, 140);
	view->resize(640, 480);

	QPixmap pix(":/icons/icon64.png");
	setTrayIcon(pix);
	setWindowIcon(pix);
	setWindowTitle("Leapp v0.0");
	setTray();
}

void leapp::setTray()
{
	QString menustr = "О программе\nНастройки\nВыход";
	QStringList menulist = menustr.split("\n");
	for	(int i = 0; i < menulist.size(); i++) {
		if (menulist[i] == "-"){
			menu->addSeparator();
		}else{
			menu->addAction(new QAction(menulist[i], this));
		}
	}
//	new QAction("Настройка", this);
//	menu->addAction(setupAction);
//	menu->addSeparator();
//	menu->addAction(quitAction);
	tray->setContextMenu(menu);
	tray->show();
}

// Меняем иконку трея
void leapp::setTrayIcon(QIcon icon)
{
	tray->setIcon(QIcon(icon));
}
// Меняем иконку окна программы
void leapp::setWindowIcon(QIcon icon)
{
	view->setWindowIcon(icon);
}
// Меняем заголовок окна
void leapp::setWindowTitle(QString title)
{
	view->setWindowTitle(title);
}

// Событие на alert();
void leapp::javaScriptAlert(const QUrl &securityOrigin, const QString &message)
{
	tools.debug(__FUNCTION__, message);
	tools.debug(__FUNCTION__, tools.isOnline());
	Q_UNUSED(securityOrigin);
	if (message == "test") view->page()->runJavaScript("test()", [](const QVariant &v) { qDebug() << v.toString(); });
}
// Событие на сообщение в console.log();
void leapp::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
	tools.debug(__FUNCTION__, message);
	Q_UNUSED(level); Q_UNUSED(lineNumber); Q_UNUSED(sourceID);
}
// Событие при клике на иконку трея
void leapp::trayClick(QSystemTrayIcon::ActivationReason reason)
{
	tools.debug(__FUNCTION__, reason);
}
// Событие при клике меню в трее
void leapp::trayMenuClick(QAction *action)
{
	tools.debug(__FUNCTION__, action->text());
}
