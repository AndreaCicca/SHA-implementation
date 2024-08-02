#pragma once
#include <string>

namespace cripto {

void init_logging(bool trace);

void log_trace(const std::string &message);

void log_info(const std::string &message);

void log_error(const std::string &message);

void log_warning(const std::string &message);

void log_debug(const std::string &message);

void log_fatal(const std::string &message);

} // namespace cripto