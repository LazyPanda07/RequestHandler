#pragma once

#include "Executors/BaseStatefulExecutor.h"

class AddRequest : public framework::BaseStatefulExecutor
{
public:
	AddRequest() = default;

	void init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings) override;

	void doPost(framework::HTTPRequest&& request, framework::HTTPResponse& response) override;

	void destroy() override;

	~AddRequest() = default;
};

CREATE_BASE_EXECUTOR_SUBCLASS_INSTANCE(AddRequest)
