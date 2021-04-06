#include "SP_users.h"

#include "Constants.h"

namespace db
{
	SP_users::SP_users() : 
		SQLiteDatabaseModel
		(
			spUsersTableName,
			framework::sqlite::SQLiteDatabase
			(
				databaseName
			)
		)
	{
		this->rawQuery
		(
			"CREATE TABLE IF NOT EXISTS " + this->getTableName() + " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, full_name VARCHAR(100) NOT NULL UNIQUE)",
			framework::sqlite::SQLiteDatabaseModel::queryType::write
		);
	}
}
