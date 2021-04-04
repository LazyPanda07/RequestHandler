#include "MainPage.h"

void MainPage::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void MainPage::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	try
	{
		if (request.getAttribute("login") == "admin")
		{

		}
		else
		{

		}
	}
	catch (const std::exception&)
	{
		response.setResponseCode(web::ResponseCodes::seeOther);

		response.addHeader("Location", "/authorization");
	}
}

void MainPage::destroy()
{

}
