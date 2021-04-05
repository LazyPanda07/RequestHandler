#pragma once

#include "SQLite3/SQLiteDatabaseModel.h"

namespace db
{
	class SP_destination : public framework::sqlite::SQLiteDatabaseModel
	{
	public:
		SP_destination();

		~SP_destination() = default;
	};
}
