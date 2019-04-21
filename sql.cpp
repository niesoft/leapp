#include "sql.h"
#include <QDebug>

SQL::SQL(Leapp *l)
{
	leapp = l;
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( "storage" );
	query = new QSqlQuery( db );
	if( !db.open() ) {
		qDebug() << db.lastError().text();
	}
}

