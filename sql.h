#ifndef SQL_H
#define SQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>

class Leapp;

class SQL
{
public:
	SQL(Leapp * l = nullptr);
	Leapp * leapp;
	QSqlDatabase db;
	QSqlQuery * query;
	QJsonObject send(QString str);

};

#endif // SQL_H


//	QJsonArray temp;
//	temp = sql->send("CREATE TABLE UserNew (id INTEGER PRIMARY KEY NOT NULL, login VARCHAR( 200 ) NOT NULL, loginold VARCHAR( 200 ) NOT NULL)");
//	temp = sql->send("SELECT * FROM UserNew");
//	temp = sql.send("select * from sqlite_master where type = 'table'");
//	QString sqltemp = "INSERT INTO UserNew (login, loginold) VALUES";
//	for (int i = 0; i < 2000000; i++) {
//		sqltemp += ("('test" + QString::number(i) +  "', 'nowtest " + QString::number(i) +  "'),");
//	}
//	temp = sql->send(sqltemp.remove(sqltemp.size()-1, 1));
//	temp = sql.send("DELETE FROM UserNew WHERE id in (SELECT id FROM UserNew LIMIT 4)");
//	qDebug() << temp;
//QStringList abc = QString("q w e r t y u i o p a s d f g h j k l z x c v b n m").split(" ");
//QString tempname = "";
//for (int a = 4; a < rand() % 15 + 1; a++) {
//	tempname += abc[rand() % (abc.size()-1)];
//}
//QString sqltemp = "INSERT INTO users (name, email) VALUES";
//for (int i = 0; i < 20000; i++) {
//	QString tempname = "";
//	for (int a = 0; a < rand() % 15 + 5; a++) {
//		tempname += abc[rand() % (abc.size()-1)];
//	}
//	QString tempmail = "";
//	for (int a = 0; a < rand() % 10 + 5; a++) {
//		tempmail += abc[rand() % (abc.size()-1)];
//	}

//	qDebug() << tempname + " => " + tempmail + "@mail.ru";

//	sqltemp += ("('" + tempname +  "', '" + tempmail +  "'),");
//}
//QJsonObject temp = sql->send(sqltemp.remove(sqltemp.size()-1, 1));
