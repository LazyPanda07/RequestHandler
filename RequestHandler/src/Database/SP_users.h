#pragma once

#include "SQLite3/SQLiteDatabaseModel.h"

namespace db
{
	class SP_users : public framework::sqlite::SQLiteDatabaseModel
	{
	public:
		SP_users();

		~SP_users() = default;
	};
}
