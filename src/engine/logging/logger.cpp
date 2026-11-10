#include "logger.h"


void Logger::Log(std::string log) {
	Logger::logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
}