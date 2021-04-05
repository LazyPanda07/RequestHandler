#pragma once

#include "SQLite3/SQLiteDatabaseModel.h"

namespace db
{
	class SP_reference: public framework::sqlite::SQLiteDatabaseModel
	{
	public:
		SP_reference();

		~SP_reference() = default;
	};
}