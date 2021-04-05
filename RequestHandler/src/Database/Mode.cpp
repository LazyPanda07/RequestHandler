#include "Mode.h"

#include "Constants.h"

namespace db
{
	Mode::Mode() :
		SQLiteDatabaseModel
		(
			modeTableName,
			framework::sqlite::SQLiteDatabase
			(
				databaseName
			)
		)
	{
		this->rawQuery
		(
			"CREATE TABLE IF NOT EXISTS " + this->getTableName() + " (id_mode INTEGER PRIMARY KEY AUTOINCREMENT, id_reference INTEGER NOT NULL, id_destination INTEGER NOT NULL, id_user INTEGER NOT NULL, "
			"FOREIGN KEY(id_reference) REFERENCES " + spReferenceTableName + "(id_reference), "
			"FOREIGN KEY(id_destination) REFERENCES " + spDestinationTableName + "(id_destination), "
			"FOREIGN KEY(id_user) REFERENCES " + spUsersTableName + "(id_user))",
			framework::sqlite::SQLiteDatabaseModel::queryType::write
		);
	}
}
