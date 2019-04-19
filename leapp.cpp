#include "leapp.h"

leapp::leapp(QWidget *parent) :
	QWebEnginePage(parent)
	{
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
	view->load(QUrl("qrc:/gui/index.html"));
	view->show();
	view->setMinimumSize(220, 140);
	view->resize(640, 480);
	view->setContextMenuPolicy(Qt::NoContextMenu);


	QPixmap pix(":/icons/icon64.png");
	setTrayIcon(pix);
	setWindowIcon(pix);
	setWindowTitle("Leapp v0.0");
	setTray();
}

void leapp::resizeEvent(QResizeEvent * event)
{
	tools.debug(__FUNCTION__, event->type());
}

void leapp::setPath(QString path)
{
	tools.path = path;
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
void leapp::setWindowStyle(int style)
{
	if (style == 1) {
		view->setWindowFlags(Qt::Dialog);
	} else if (style == 2) {
		view->setWindowFlags(Qt::Sheet);
	} else if (style == 3) {
		view->setWindowFlags(Qt::Drawer);
	} else if (style == 4) {
		view->setWindowFlags(Qt::Popup);
	} else if (style == 5) {
		view->setWindowFlags(Qt::Tool);
	} else if (style == 6) {
		view->setWindowFlags(Qt::ToolTip);
	} else if (style == 7) {
		view->setWindowFlags(Qt::SplashScreen);
	} else {
		view->setWindowFlags(Qt::Window);
	}
}
// Событие на alert();
void leapp::javaScriptAlert(const QUrl &securityOrigin, const QString &message)
{
	tools.debug(__FUNCTION__, message);
	Q_UNUSED(securityOrigin);
	showTrayMessage("", message);
//	if (message == "test") view->page()->runJavaScript("test()", [](const QVariant &v) { qDebug() << v.toString(); });
}
// Событие на сообщение в console.log();
void leapp::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
	tools.debug(__FUNCTION__, message);
	Q_UNUSED(level); Q_UNUSED(lineNumber); Q_UNUSED(sourceID);
	command(message);
}
// Событие при клике на иконку трея
void leapp::trayClick(QSystemTrayIcon::ActivationReason reason)
{
	tools.debug(__FUNCTION__, reason);
	if (reason == 3 && menu->actions().size() > 0) {
		view->setVisible(!view->isVisible());
		view->setWindowState(Qt::WindowActive);
	}
}
// Событие при клике меню в трее
void leapp::trayMenuClick(QAction * action)
{
	tools.debug(__FUNCTION__, action->text());
}
// Показать сообщение в трее
void leapp::showTrayMessage(QString title, QString msg, int type, int msec)
{
	switch (type) {
	case 1:
		tray->showMessage(title, msg, QSystemTrayIcon::Information, msec);
		break;
	case 2:
		tray->showMessage(title, msg, QSystemTrayIcon::Warning, msec);
		break;
	case 3:
		tray->showMessage(title, msg, QSystemTrayIcon::Critical, msec);
		break;
	default:
		tray->showMessage(title, msg, QSystemTrayIcon::NoIcon, msec);
		break;
	}
}
void leapp::command(QString command)
{
	QString result;
	if (command == "Leapp.setWindowTitle") {
		view->page()->runJavaScript("leapp.getWindowTitle()", [this](const QVariant &v) {
			this->setWindowTitle(v.toString());
		});
	}else{
		this->runJavaScript(command);
	}
}
