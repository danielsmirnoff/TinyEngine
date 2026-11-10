#pragma once

#include <string>
#include <memory>

#include "spdlog/sinks/basic_file_sink.h"

class Logger {
public:
	inline static std::shared_ptr<spdlog::logger> logger = nullptr;
	void Log(std::string log);
private:
};