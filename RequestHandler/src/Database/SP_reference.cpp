#include "SP_reference.h"

#include "Constants.h"

using namespace std;

namespace db
{
	SP_reference::SP_reference() :
		SQLiteDatabaseModel
		(
			spReferenceTableName,
			framework::sqlite::SQLiteDatabase
			(
				databaseName
			)
		)
	{
		this->rawQuery
		(
			"CREATE TABLE IF NOT EXISTS " + this->getTableName() + " (id INTEGER PRIMARY KEY AUTOINCREMENT, type VARCHAR(60) NOT NULL)",
			framework::sqlite::SQLiteDatabaseModel::queryType::write
		);
	}
}
