#include <iostream>

#include "WebFramework.h"

using namespace std;

int main(int argc, char** argv)
{
	try
	{
		framework::WebFramework requestHandler("request_handler_settings.ini");
		string blank;

		requestHandler.startServer();

		while (cin >> blank)
		{

		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
