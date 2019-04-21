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
	sql = new SQL(this);
	transport = new Transport(this);

	channel = new QWebChannel;

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

//	QFile file("/media/niesoft/hard/Projects/leapp/leapp/html/index.html");
//	file.open(QIODevice::ReadOnly);
//	QTextStream in(&file);
//	in.setCodec("UTF-8");
//	QString line = in.readAll();
//	file.close();
//	ui->view->setHtml(line);

	channel->registerObject(QString("leapp"), transport);
	ui->view->page()->setWebChannel(channel);

}

QString Leapp::onKeysExtracted(QStringList keys)
{
	qDebug() << "Вызов функции:";
	qDebug() << keys;
	this->resize(300,300);
	return "work done! you best programmer!!";
}

// Изменяем состояние окна
void Leapp::windowStateSet(QString state)
{
	this->show();
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
// Действия при перемещении окна
void Leapp::moveEvent(QMoveEvent *event)
{
	tools.debug(__FUNCTION__, event->pos());
	this->page->runJavaScript("leapp.window.left = " + QString::number(event->pos().x()) + "; "
							  "leapp.window.top = " + QString::number(event->pos().y()) + ";");
	this->page->runJavaScript("leapp.onMove(" + QString::number(event->pos().x()) + ", " + QString::number(event->pos().y()) + ")");
}
// Действия при закрытии окна
void Leapp::closeEvent(QCloseEvent *event)
{
	event->ignore();
	this->page->runJavaScript("leapp.onClose()", [this](const QVariant &v) {
		this->tools.debug(__FUNCTION__, v);
		if (v.type() == QVariant::Bool) qApp->exit(0);
	});
}
// Ресайз главной формы
void Leapp::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	tools.debug(__FUNCTION__, event->size());
	this->page->runJavaScript("leapp.window.width = " + QString::number(this->width()) + "; "
							  "leapp.window.height = " + QString::number(this->height()) + ";");
	this->page->runJavaScript("leapp.onResize(" + QString::number(this->width()) + ", " + QString::number(this->height()) + ")");
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
	if (command == "Leapp.windowState"){
		this->page->runJavaScript("leapp.windowstate", [this](const QVariant &v) {
			this->windowStateSet(v.toString().toLower());
		});
	}else if (command == "Leapp.windowStyle"){
		this->page->runJavaScript("leapp.windowstyle", [this](const QVariant &v) {
			this->windowStyleSet(v.toString().toLower());
		});
	}
}


QJsonArray SQL::send(QString str, bool res)
{
	QJsonArray array;
	if( !query->exec(str) ) {
		QJsonObject row;
		row.insert("error", query->lastError().text());
		row.insert("query", str);
		array.push_front(row);
	}else{
		QSqlRecord rec = query->record();
		while( query->next() ) {
			QJsonObject row;
			for (int i = 0; i < rec.count(); i++) {
				row.insert(rec.fieldName(i), query->value(i).toString());
			}
			array.append(row);
		}
		if (array.count() == 0 && query->lastInsertId().toInt() > 0) {
			QJsonObject row;
			row.insert("lastInsertId", query->lastInsertId().toInt());
			row.insert("numRowsAffected", query->numRowsAffected());
			array.push_front(row);
		}
		if (array.count() == 0) {
			QJsonObject row;
			row.insert("numRowsAffected", query->numRowsAffected());
			array.push_front(row);
		}
	}
	return array;
}


QJsonObject Transport::resize(int w, int h)
{
	int width = (w >= 0) ? w : leapp->width();
	int height = (h >= 0) ? h : leapp->height();
	leapp->resize(width, height);
	QJsonObject result{{"width", leapp->width()}, {"height", leapp->height()}};
	return result;
}
QJsonObject Transport::move(int x, int y)
{
	int left = (x >= 0) ? x : leapp->x();
	int top = (y >= 0) ? y : leapp->y();
	leapp->move(left, top);
	QJsonObject result{{"left", leapp->x()}, {"top", leapp->y()}};
	return result;
}
void Transport::title(QString title)
{
	leapp->setWindowTitle(title);
}
void Transport::reload(QString url)
{
	if (url != "") {
		leapp->loadHtml(QUrl(url));
	}else {
		leapp->loadHtml(QUrl(url));
	}
}
void Transport::show()
{
	leapp->show();
}
void Transport::hide()
{
	leapp->hide();
}
void Transport::exit()
{
	qApp->exit(0);
}
