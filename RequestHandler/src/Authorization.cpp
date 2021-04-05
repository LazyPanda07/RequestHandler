#include "Authorization.h"

#include "Utility/StringConversion.h"
#include "Database/SP_users.h"
#include "Database/Constants.h"

void Authorization::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void Authorization::doPost(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	const auto& login = request.getKeyValueParameters().at("login");

	if (login == "admin")
	{
		request.setAttribute("id", "admin");

		response.addBody
		(
			framework::utility::cp1251ToUTF8("����������� ������ �������")
		);

		response.setResponseCode(web::ResponseCodes::seeOther);

		response.addHeader("Location", "/");
	}
	else
	{
		auto& users = request.getDatabaseModelInstance<db::SP_users>(db::databaseName, db::spUsersTableName);

		framework::sqlite::utility::SQLiteResult result = users->selectByFieldQuery({ { "full_name", login } });

		if (result.size())
		{
			response.addBody
			(
				framework::utility::cp1251ToUTF8("����������� ������ �������")
			);

			request.setAttribute("id", result[0].at("id_user"));

			response.setResponseCode(web::ResponseCodes::seeOther);

			response.addHeader("Location", "/");
		}
		else
		{
			response.addBody
			(
				framework::utility::cp1251ToUTF8("�� ������� ����� ������������ � ������ �������")
			);
		}
	}

	response.addHeader("Content-Type", "text/html; charset=utf-8");
}

void Authorization::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	request.sendAssetFile("/Authorization.html", response);
}

void Authorization::destroy()
{

}
