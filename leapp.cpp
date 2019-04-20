#include "leapp.h"
#include "ui_leapp.h"

Leapp::Leapp(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Leapp)
{
	page = new ViewPage(this, this);
	tray = new QSystemTrayIcon();
	menu = new QMenu("leappMenu");
	icon = QPixmap(":/icons/icon64.png");

	ui->setupUi(this);
	ui->view->setPage(page);
	this->setCentralWidget(ui->view);

	connect(tray, &QSystemTrayIcon::activated, this, &Leapp::trayClick);
	connect(menu, &QMenu::triggered, this, &Leapp::trayMenuClick);

}

Leapp::~Leapp()
{
	delete ui;
}

void Leapp::start()
{
	qDebug() << __FUNCTION__;
	this->setWindowIcon(icon);
	ui->view->setContextMenuPolicy(Qt::NoContextMenu);
	this->setMinimumSize(320, 240);
	this->loadHtml();
	this->trayIconSet(icon);
	if (trayenable) tray->show();
	if (traymenuenable) this->trayMenuSet(QString("О программе\nНастройки\nВыход").split("\n"));
	this->show();
}

void Leapp::loadHtml(QUrl url)
{
	ui->view->page()->profile()->clearHttpCache();
	ui->view->load(url);
}

// Изменяем состояние окна
void Leapp::windowStateSet(QString state)
{
	if (state == "0" || state == "nostate") this->setWindowState(Qt::WindowNoState);
	if (state == "1" || state == "active") this->setWindowState(Qt::WindowActive);
	if (state == "2" || state == "fullscreen") this->setWindowState(Qt::WindowFullScreen);
	if (state == "3" || state == "maximized") this->setWindowState(Qt::WindowMaximized);
	if (state == "4" || state == "minimized") this->setWindowState(Qt::WindowMinimized);
}
// Изменяем стиль окна
void Leapp::windowStyleSet(QString style)
{
	if (style == "0" || style == "window") this->setWindowFlags(Qt::Window);
	if (style == "1" || style == "dialog") this->setWindowFlags(Qt::Dialog);
	if (style == "2" || style == "sheet") this->setWindowFlags(Qt::Sheet);
	if (style == "3" || style == "drawer") this->setWindowFlags(Qt::Drawer);
	if (style == "4" || style == "popup") this->setWindowFlags(Qt::Popup);
	if (style == "5" || style == "tool") this->setWindowFlags(Qt::Tool);
	if (style == "6" || style == "toolTip") this->setWindowFlags(Qt::ToolTip);
	if (style == "7" || style == "splashScreen") this->setWindowFlags(Qt::SplashScreen);
}
// Смена иконки в трее
void Leapp::trayIconSet(QPixmap icon)
{
	tray->setIcon(QIcon(icon));
}
// Установка меню в трее
void Leapp::trayMenuSet(QStringList list)
{
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == "-" || list[i] == ""){
			menu->addSeparator();
		}else{
			menu->addAction(new QAction(list[i], this));
		}
	}
	tray->setContextMenu(menu);
}
// Сообщение в трее
void Leapp::trayMessageShow(QString title, QString msg, QString type, int msec)
{
	if (type == "0" || type == "noicon") tray->showMessage(title, msg, QSystemTrayIcon::NoIcon, msec);
	if (type == "1" || type == "information") tray->showMessage(title, msg, QSystemTrayIcon::Information, msec);
	if (type == "2" || type == "warning") tray->showMessage(title, msg, QSystemTrayIcon::Warning, msec);
	if (type == "3" || type == "critical") tray->showMessage(title, msg, QSystemTrayIcon::Critical, msec);
}
// Событие при клике на иконку трея
void Leapp::trayClick(QSystemTrayIcon::ActivationReason reason)
{
	tools.debug(__FUNCTION__, reason);
	if (reason == 3 && menu->actions().size() > 0) {
		this->setVisible(!this->isVisible());
		this->setWindowState(Qt::WindowActive);
	}
}
// Событие при клике меню в трее
void Leapp::trayMenuClick(QAction * action)
{
	tools.debug(__FUNCTION__, action->text());
	this->page->runJavaScript("leapp.trayMenuClick(\"" + action->text() + "\")");
}
// Действия при закрытии окна
void Leapp::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event);
	qDebug() << __FUNCTION__;
	if (tray->isVisible()) event->ignore();
	this->page->runJavaScript("leapp.windowClose()");
}
// Ресайз главной формы
void Leapp::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	qDebug() << __FUNCTION__;
	this->page->runJavaScript("leapp.sizeChanged(" + QString::number(this->width()) + ", " + QString::number(this->height()) + ")");
}
// Отправить сообщение в трей.
void ViewPage::javaScriptAlert(const QUrl &securityOrigin, const QString &message)
{
	Q_UNUSED(securityOrigin);
	tools.debug(__FUNCTION__, message);
	leapp->trayMessageShow(leapp->windowTitle(), message);
}

void ViewPage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
	Q_UNUSED(level); Q_UNUSED(lineNumber); Q_UNUSED(sourceID);
	leapp->command(message);
	tools.debug(__FUNCTION__, message);
}

void Leapp::command(QString command)
{
	QString result;
	if (command == "Leapp.windowTitle") {
		this->page->runJavaScript("leapp.windowtitle", [this](const QVariant &v) {
			this->setWindowTitle(v.toString());
		});
	}else if (command == "Leapp.windowState"){
		this->page->runJavaScript("leapp.windowstate", [this](const QVariant &v) {
			this->windowStateSet(v.toString().toLower());
		});
	}else if (command == "Leapp.windowStyle"){
		this->page->runJavaScript("leapp.windowstyle", [this](const QVariant &v) {
			this->windowStyleSet(v.toString().toLower());
		});
	}else if (command == "Leapp.width"){
		this->page->runJavaScript("leapp.windowwidth", [this](const QVariant &v) {
			this->resize(v.toString().toInt(), this->height());
		});
	}else if (command == "Leapp.height"){
		this->page->runJavaScript("leapp.windowheight", [this](const QVariant &v) {
			this->resize(this->width(), v.toString().toInt());
		});
	}else if (command == "Leapp.exit"){
		qApp->exit(0);
	}else if (command == "Leapp.reload"){
		this->loadHtml();
	}
}
