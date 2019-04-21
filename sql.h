#ifndef SQL_H
#define SQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>

class Leapp;

class SQL
{
public:
	SQL(Leapp * l = nullptr);
	Leapp * leapp;
	QSqlDatabase db;
	QSqlQuery * query;
	QJsonArray send(QString str, bool res = false);

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
