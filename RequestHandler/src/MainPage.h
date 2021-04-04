#pragma once

#include "Executors/BaseStatefulExecutor.h"

class MainPage : public framework::BaseStatefulExecutor
{
public:
	MainPage() = default;

	void init(const framework::utility::JSONSettingsParser::ExecutorSettings& settings) override;

	void doGet(framework::HTTPRequest&& request, framework::HTTPResponse& response) override;

	void destroy() override;

	~MainPage() = default;
};

CREATE_BASE_EXECUTOR_SUBCLASS_INSTANCE(MainPage)
