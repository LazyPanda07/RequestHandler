#include "MainPage.h"

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
			
		}
		else
		{
			
		}
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
