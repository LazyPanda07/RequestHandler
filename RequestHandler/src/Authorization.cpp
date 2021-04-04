#include "Authorization.h"

#include "Utility/StringConversion.h"

void Authorization::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void Authorization::doPost(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	if (request.getBody() == "admin")
	{
		request.setAttribute("login", "admin");

		response.addBody
		(
			framework::utility::cp1251ToUTF8("Авторизация прошла успешно")
		);
	}
	else
	{
		// TODO: авторизация
	}

	response.addHeader("Content-Type", "text/html; charset=utf-8");
}

void Authorization::doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	response.addBody
	(
		framework::utility::cp1251ToUTF8("Страница авторизации")
	);

	response.addHeader("Content-Type", "text/html; charset=utf-8");
}

void Authorization::destroy()
{

}
