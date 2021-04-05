#include "MainPage.h"

#include "Utility/StringConversion.h"
#include "Database/Mode.h"
#include "Database/Constants.h"

using namespace std;

void MainPage::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void MainPage::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	try
	{
		smartPointer<unordered_map<string_view, string>> variables = make_unique<unordered_map<string_view, string>>();

		auto& modeModel = request.getDatabaseModelInstance<db::Mode>(db::databaseName, db::modeTableName);

		if (request.getAttribute("id") == "admin")
		{
			framework::sqlite::utility::SQLiteResult data = modeModel->rawQuery
			(
				"SELECT Mode.id_mode, SP_users.full_name, SP_destination.destination, SP_reference.type "
				"FROM SP_users INNER JOIN(SP_reference INNER JOIN(SP_destination INNER JOIN Mode ON SP_destination.id_destination = Mode.id_destination) ON SP_reference.id_reference = Mode.id_reference) ON SP_users.id_user = Mode.id_user",
				framework::sqlite::SQLiteDatabaseModel::queryType::read
			);

			if (data.size())
			{
				string result = R"(<table style="margin-left: auto; margin-right: auto;">)";

				for (const auto& i : data)
				{
					result += "<tr>";

					result += "<td>" + i.at("full_name") + "</td>";

					result += "<td>" + i.at("destination") + "</td>";

					result += "<td>" + i.at("type") + "</td>";

					result += "</tr>";
				}

				result += "</table>";

				response.addBody
				(
					move(result)
				);
			}
			else
			{
				response.addBody
				(
					framework::utility::cp1251ToUTF8("В данный момент нет заявок")
				);
			}
		}
		else
		{

		}

		response.addHeader("Content-Type", "text/html; charset=utf-8");
	}
	catch (const out_of_range&)
	{
		response.setResponseCode(web::ResponseCodes::seeOther);

		response.addHeader("Location", "/authorization");
	}
}

void MainPage::destroy()
{

}
