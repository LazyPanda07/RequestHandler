#include "AddRequest.h"

#include "Database/SP_destination.h"
#include "Database/SP_reference.h"
#include "Database/Mode.h"
#include "Database/Constants.h"

using namespace std;

void AddRequest::init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings)
{

}

void AddRequest::doPost(framework::HTTPRequest&& request, framework::HTTPResponse& response)
{
	try
	{
		string id = request.getAttribute("id");
		const json::JSONParser& json = request.getJSON();

		auto& spDestinationModel = request.getDatabaseModelInstance<db::SP_destination>(db::databaseName, db::spDestinationTableName);
		auto& spReferenceModel = request.getDatabaseModelInstance<db::SP_reference>(db::databaseName, db::spReferenceTableName);
		auto& modeModel = request.getDatabaseModelInstance<db::Mode>(db::databaseName, db::modeTableName);

		const string& destination = json.get<string>("destination");
		const string& type = json.get<string>("type");

		spDestinationModel->insertQuery({ { "destination", destination } });
		spReferenceModel->insertQuery({ { "type", type } });

		string destinationId = spDestinationModel->selectByFieldQuery({ { "destination", destination } })[0].at("id");
		string referenceId = spReferenceModel->selectByFieldQuery({ { "type", type } })[0].at("id");

		modeModel->insertQuery({ { "id_reference", referenceId }, { "id_destination", destinationId }, { "id_user", id } });

		response.addBody
		(
			json::JSONBuilder(1251).push_back<bool>(make_pair("success", true))
		);
	}
	catch (const out_of_range&)
	{
		response.setResponseCode(web::ResponseCodes::unauthorized);
	}
	catch (const runtime_error& e)
	{
		response.addBody
		(
			json::JSONBuilder(1251).push_back<bool>(make_pair("success", false))
		);
	}
}

void AddRequest::destroy()
{

}
