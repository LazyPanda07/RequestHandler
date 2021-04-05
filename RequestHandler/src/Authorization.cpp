#include "Authorization.h"

#include "Utility/StringConversion.h"
#include "Database/SP_users.h"
#include "Database/Constants.h"

using namespace std;

void Authorization::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void Authorization::doPost(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	string login = request.getJSON().get<string>("login");

	if (login == "admin")
	{
		request.setAttribute("id", "admin");

		response.addBody
		(
			json::JSONBuilder(1251).push_back<bool>(make_pair("success", true))
		);
	}
	else
	{
		auto& users = request.getDatabaseModelInstance<db::SP_users>(db::databaseName, db::spUsersTableName);

		framework::sqlite::utility::SQLiteResult result = users->selectByFieldQuery({ { "full_name", login } });

		if (result.size())
		{
			response.addBody
			(
				json::JSONBuilder(1251).push_back<bool>(make_pair("success", true))
			);

			request.setAttribute("id", result[0].at("id_user"));
		}
		else
		{
			response.addBody
			(
				json::JSONBuilder(1251).push_back<bool>(make_pair("success", false))
			);
		}
	}
}

void Authorization::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	request.sendAssetFile("/Authorization.html", response);
}

void Authorization::destroy()
{

}
