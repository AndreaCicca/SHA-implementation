/**
 * @file logging.hh
 * @author Andrea Ciccarello
 * @brief Definizione delle funzioni di logging
 * @version 1.0
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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