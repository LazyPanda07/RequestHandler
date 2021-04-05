#pragma once

#include "SQLite3/SQLiteDatabaseModel.h"

namespace db
{
	class Mode : public framework::sqlite::SQLiteDatabaseModel
	{
	public:
		Mode();

		~Mode() = default;
	};
}
