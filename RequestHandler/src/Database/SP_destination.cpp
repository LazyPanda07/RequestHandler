#include "SP_destination.h"

#include "Constants.h"

namespace db
{
	SP_destination::SP_destination() :
		SQLiteDatabaseModel
		(
			spDestinationTableName,
			framework::sqlite::SQLiteDatabase
			(
				databaseName
			)
		)
	{
		this->rawQuery
		(
			"CREATE TABLE IF NOT EXISTS " + this->getTableName() + " (id_destination INTEGER PRIMARY KEY AUTOINCREMENT, destination VARCHAR(60) NOT NULL)",
			framework::sqlite::SQLiteDatabaseModel::queryType::write
		);
	}
}
