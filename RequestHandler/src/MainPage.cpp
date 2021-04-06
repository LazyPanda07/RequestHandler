#include "MainPage.h"

#include "Utility/StringConversion.h"
#include "Database/Mode.h"
#include "Database/SP_destination.h"
#include "Database/SP_reference.h"
#include "Database/SP_users.h"
#include "Database/Constants.h"

using namespace std;

void MainPage::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void MainPage::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	try
	{
		auto& modeModel = request.getDatabaseModelInstance<db::Mode>(db::databaseName, db::modeTableName);
		auto& spDestinationModel = request.getDatabaseModelInstance<db::SP_destination>(db::databaseName, db::spDestinationTableName);
		auto& spReferenceModel = request.getDatabaseModelInstance<db::SP_reference>(db::databaseName, db::spReferenceTableName);
		auto& spUsersModel = request.getDatabaseModelInstance<db::SP_users>(db::databaseName, db::spUsersTableName);

		if (request.getAttribute("id") == "admin")
		{
			framework::sqlite::utility::SQLiteResult data = modeModel->rawQuery
			(
				"SELECT Mode.id as id, SP_users.full_name, SP_destination.destination, SP_reference.type "
				"FROM SP_users INNER JOIN(SP_reference INNER JOIN(SP_destination INNER JOIN Mode ON SP_destination.id = Mode.id_destination) ON SP_reference.id = Mode.id_reference) ON SP_users.id = Mode.id_user",
				framework::sqlite::SQLiteDatabaseModel::queryType::read
			);

			if (data.size())
			{
				string result = R"(<table style="margin-left: auto; margin-right: auto; border-collapse: collapse;">)";
				smartPointer<unordered_map<string_view, string>> variables = make_unique<unordered_map<string_view, string>>();

				variables->insert(make_pair("title", framework::utility::cp1251ToUTF8("Главная страница")));

				variables->insert(make_pair("pathToScript", "/script.js"));

				variables->insert(make_pair("error", framework::utility::cp1251ToUTF8("Не удалось удалить заявку")));

				request.sendAssetFile("/script.wfdp", response, variables);

				for (const auto& i : data)
				{
					result += R"(<tr style="border: 2px solid black;">)";

					result += R"(<td style="visibility: hidden">)" + i.at("id") + "</td>";

					result += R"(<td style="border: 2px solid black;">)" + i.at("full_name") + "</td>";

					result += R"(<td style="border: 2px solid black;">)" + i.at("destination") + "</td>";

					result += R"(<td style="border: 2px solid black;">)" + i.at("type") + "</td>";

					result += R"X(<td><button onclick="sendRequest(this.id)" id=")X" + i.at("id") + R"(">)" + framework::utility::cp1251ToUTF8("Удалить") + "</button></td>";

					result += "</tr>";
				}

				result += "</table></body></html>";

				response.appendBody
				(
					result
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
			request.sendAssetFile("/StudentMainPage.html", response);
		}

		response.addHeader("Content-Type", "text/html; charset=utf-8");
	}
	catch (const out_of_range&)
	{
		response.setResponseCode(web::ResponseCodes::seeOther);

		response.addHeader("Location", "/authorization");
	}
}

void MainPage::doDelete(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	auto& spDestinationModel = request.getDatabaseModelInstance<db::SP_destination>(db::databaseName, db::spDestinationTableName);
	auto& spReferenceModel = request.getDatabaseModelInstance<db::SP_reference>(db::databaseName, db::spReferenceTableName);
	auto& modeModel = request.getDatabaseModelInstance<db::Mode>(db::databaseName, db::modeTableName);

	try
	{
		framework::sqlite::utility::SQLiteResult result = modeModel->selectByFieldQuery({ { "id", request.getJSON().get<string>("id") } });

		modeModel->deleteQuery("id", result[0].at("id"));
		spDestinationModel->deleteQuery("id", result[0].at("id"));
		spReferenceModel->deleteQuery("id", result[0].at("id"));

		response.addBody
		(
			json::JSONBuilder(1251).push_back<bool>(make_pair("success", true))
		);
	}
	catch (const runtime_error&)
	{
		response.addBody
		(
			json::JSONBuilder(1251).push_back<bool>(make_pair("success", false))
		);
	}
}

void MainPage::destroy()
{

}
