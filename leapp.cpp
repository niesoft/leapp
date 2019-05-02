#include "leapp.h"
#include "ui_leapp.h"

Leapp::Leapp(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Leapp)
{
    initMyResource();
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
	connect(ui->view, &QWebEngineView::loadFinished, this, &Leapp::loadFinished);
	connect(ui->view, &QWebEngineView::loadProgress, this, &Leapp::loadProgress);
	connect(ui->view, &QWebEngineView::loadStarted, this, &Leapp::loadStarted);

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


	channel->registerObject(QString("leapp"), transport);
	ui->view->page()->setWebChannel(channel);
}
void Leapp::loadStarted()
{
	tools.debug(__FUNCTION__);
    QString line = this->fileOpen(":/jslibs/qwebchannel.txt");
    line += this->fileOpen(":/jslibs/leapp.txt");
	line += this->setProperties();

	QWebEngineScript script_qwebchannel;
    script_qwebchannel.setInjectionPoint(QWebEngineScript::DocumentCreation);
	script_qwebchannel.setWorldId(QWebEngineScript::MainWorld);
	script_qwebchannel.setName("qwebchannel.js");
	script_qwebchannel.setRunsOnSubFrames(true);
	script_qwebchannel.setSourceCode(line);
	ui->view->page()->scripts().insert(script_qwebchannel);
}
void Leapp::loadProgress()
{
	tools.debug(__FUNCTION__);
}
void Leapp::loadFinished()
{
	tools.debug(__FUNCTION__);
    this->page->runJavaScript("document.documentElement.outerHTML;", [this](const QVariant &v) {
        this->tools.debug(__FUNCTION__, v);
    });
}

QString Leapp::setProperties(){
	QString properties = "";
	int state = 0;
	if (this->windowState() == Qt::WindowNoState) state = 0;
	if (this->windowState() == Qt::WindowActive) state = 1;
	if (this->windowState() == Qt::WindowFullScreen) state = 2;
	if (this->windowState() == Qt::WindowMaximized) state = 3;
	if (this->windowState() == Qt::WindowMinimized) state = 4;
	properties += "leapp.window.width = \"" + QString::number(this->width()) + "\";";
	properties += "leapp.window.height = \"" + QString::number(this->height()) + "\";";
	properties += "leapp.window.minWidth = \"" + QString::number(this->minimumWidth()) + "\";";
	properties += "leapp.window.minHeight = \"" + QString::number(this->minimumHeight()) + "\";";
	properties += "leapp.window.maxWidth = \"" + QString::number(this->maximumWidth()) + "\";";
	properties += "leapp.window.maxHeight = \"" + QString::number(this->maximumHeight()) + "\";";
	properties += "leapp.window.left = \"" + QString::number(this->x()) + "\";";
	properties += "leapp.window.top = \"" + QString::number(this->y()) + "\";";
	properties += "leapp.window.title = \"" + this->windowTitle() + "\";";
	properties += "leapp.window.state = \"" + QString::number(state) + "\";";
	properties += "leapp.window.path = \"" + qApp->applicationDirPath() + "\";";
	return properties;
}

QString Leapp::fileOpen(QString filename)
{
	QFile file(filename);
    if(!file.open(QFile::ReadOnly)) {
        qDebug() << "error: " << file.errorString();
        qApp->exit(1);
    }
    qDebug() << filename;
    qDebug() << file.size();
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString line = in.readAll();
	file.close();
    if (line.length() < 1) qApp->exit(1);
	return line;
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
	this->page->runJavaScript("if (typeof leapp == 'object'){ leapp.window.left = " + QString::number(event->pos().x()) + "; "
							  "leapp.window.top = " + QString::number(event->pos().y()) + "; "
							  "leapp.onMove(" + QString::number(event->pos().x()) + ", " + QString::number(event->pos().y()) + "); }");
}
// Действия при закрытии окна
void Leapp::closeEvent(QCloseEvent *event)
{
	event->ignore();
	this->page->runJavaScript("leapp.onClose()", [this](const QVariant &v) {
		this->tools.debug(__FUNCTION__, v);
		if (v.type() == QVariant::Bool && v.toInt() == true) qApp->exit(0);
	});
}
// Ресайз главной формы
void Leapp::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	tools.debug(__FUNCTION__, event->size());
	this->page->runJavaScript("if (typeof leapp == 'object'){ leapp.window.width = " + QString::number(this->width()) + "; "
							  "leapp.window.height = " + QString::number(this->height()) + "; "
							  "leapp.onResize(" + QString::number(this->width()) + ", " + QString::number(this->height()) + "); }");
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
	tools.debug(__FUNCTION__, message);
}

QJsonObject SQL::send(QString str)
{
	QJsonObject result;
	if( !query->exec(str) ) {
		result.insert("error", query->lastError().text());
	}else{
		QJsonArray array;
		QSqlRecord rec = query->record();
		while( query->next() ) {
			QJsonObject row;
			for (int i = 0; i < rec.count(); i++) {
				row.insert(rec.fieldName(i), query->value(i).toString());
			}
			array.append(row);
		}
		result.insert("rows", array);
		result.insert("lastInsertId", query->lastInsertId().toInt());
		result.insert("numRowsAffected", query->numRowsAffected());
		result.insert("query", str);
	}
	return result;
}


QJsonObject Transport::resize(int w, int h)
{
	int width = (w >= 0) ? w : leapp->width();
	int height = (h >= 0) ? h : leapp->height();
	leapp->resize(width, height);
	QJsonObject result{{"width", leapp->width()}, {"height", leapp->height()}};
	return result;
}
QJsonObject Transport::minSize(int w, int h)
{
	int width = (w >= 0) ? w : leapp->minimumWidth();
	int height = (h >= 0) ? h : leapp->minimumHeight();
	leapp->setMinimumSize(width, height);
	QJsonObject result{{"minWidth", leapp->minimumWidth()}, {"minHeight", leapp->minimumHeight()}};
	return result;
}
QJsonObject Transport::maxSize(int w, int h)
{
	int width = (w >= 0) ? w : leapp->maximumWidth();
	int height = (h >= 0) ? h : leapp->maximumHeight();
	leapp->setMaximumSize(width, height);
	QJsonObject result{{"maxWidth", leapp->maximumWidth()}, {"maxHeight", leapp->maximumHeight()}};
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
void Transport::state(int s)
{
	if (s < 0 || s > 4) s = 0;
	if (s == 0) leapp->setWindowState(Qt::WindowNoState);
	if (s == 1) leapp->setWindowState(Qt::WindowActive);
	if (s == 2) leapp->setWindowState(Qt::WindowFullScreen);
	if (s == 3) leapp->setWindowState(Qt::WindowMaximized);
	if (s == 4) leapp->setWindowState(Qt::WindowMinimized);
	leapp->page->runJavaScript("if (typeof leapp == 'object'){ leapp.window.state = " + QString::number(s) + "; }");
}
void Transport::style(int style)
{
	if (style < 0 || style > 7) style = 0;
	if (style == 0) leapp->setWindowFlags(Qt::Window);
	if (style == 1) leapp->setWindowFlags(Qt::Dialog);
	if (style == 2) leapp->setWindowFlags(Qt::Sheet);
	if (style == 3) leapp->setWindowFlags(Qt::Drawer);
	if (style == 4) leapp->setWindowFlags(Qt::Popup);
	if (style == 5) leapp->setWindowFlags(Qt::Tool);
	if (style == 6) leapp->setWindowFlags(Qt::ToolTip);
	if (style == 7) leapp->setWindowFlags(Qt::SplashScreen);
	leapp->page->runJavaScript("if (typeof leapp == 'object'){ leapp.window.style = " + QString::number(style) + "; }");
	leapp->show();
	leapp->setWindowState(Qt::WindowActive);
}
void Transport::reload(QString url)
{
	if (url != "") {
		leapp->loadHtml(QUrl(url));
	}else {
		leapp->loadHtml();
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
QJsonObject Transport::sql(QString query)
{
	QJsonObject result = leapp->sql->send(query);;
	return result;
}
