#pragma once

#include <string>

namespace db
{
	inline const std::string databaseName = "request_handler.sqlite3";

	inline const std::string spUsersTableName = "SP_users";
	inline const std::string spReferenceTableName = "SP_reference";
	inline const std::string spDestinationTableName = "SP_destination";
	inline const std::string modeTableName = "Mode";
}
