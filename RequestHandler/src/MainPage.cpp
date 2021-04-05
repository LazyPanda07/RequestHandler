#include "MainPage.h"

using namespace std;

void MainPage::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void MainPage::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	try
	{
		smartPointer<unordered_map<string_view, string>> variables = make_unique<unordered_map<string_view, string>>();

		if (request.getAttribute("id") == "admin")
		{
			variables->insert(make_pair("userName", "admin"));
		}
		else
		{
			variables->insert(make_pair("userName", request.getAttribute("id")));
		}

		request.sendAssetFile("/MainPage.wfdp", response, variables);
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
