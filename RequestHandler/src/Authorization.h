#pragma once

#include "Executors/BaseStatefulExecutor.h"

class Authorization : public framework::BaseStatefulExecutor
{
public:
	Authorization() = default;

	void init(const framework::utility::JSONSettingsParser::ExecutorSettings & settings) override;

	void doPost(framework::HTTPRequest&& request, framework::HTTPResponse& response) override;

	void doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response) override;

	void destroy() override;

	~Authorization() = default;
};

CREATE_BASE_EXECUTOR_SUBCLASS_INSTANCE(Authorization)
