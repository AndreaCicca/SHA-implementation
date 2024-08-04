/**
 * @file logging.cc
 * @author Andrea Ciccarello
 * @brief Implementazione delle funzioni di logging
 * @version 1.0
 * @date 2024-08-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "logging.hh"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging  = boost::log;
namespace keywords = boost::log::keywords;

namespace cripto {

void
set_log_level(logging::trivial::severity_level level) {
  logging::core::get()->set_filter(logging::trivial::severity >= level);
}

void
init_logging(bool trace) {
  logging::register_simple_formatter_factory<logging::trivial::severity_level,
                                             char>("Severity");

  logging::add_file_log(keywords::file_name     = "logging_%N.log",
                        keywords::rotation_size = 10 * 1024 * 1024,
                        keywords::time_based_rotation =
                          logging::sinks::file::rotation_at_time_point(0, 0, 0),
                        keywords::format =
                          "[%TimeStamp%] [%Severity%] %Message%");

  if (trace) {
    set_log_level(logging::trivial::trace);
  } else {
    set_log_level(logging::trivial::info);
  }

  logging::add_common_attributes();
}

// Funzione per logare facilmente

void
log_trace(const std::string &message) {
  BOOST_LOG_TRIVIAL(trace) << message << std::flush;
}

void
log_info(const std::string &message) {
  BOOST_LOG_TRIVIAL(info) << message << std::flush;
}

void
log_error(const std::string &message) {
  BOOST_LOG_TRIVIAL(error) << message << std::flush;
}

void
log_warning(const std::string &message) {
  BOOST_LOG_TRIVIAL(warning) << message << std::flush;
}

void
log_debug(const std::string &message) {
  BOOST_LOG_TRIVIAL(debug) << message << std::flush;
}

void
log_fatal(const std::string &message) {
  BOOST_LOG_TRIVIAL(fatal) << message << std::flush;
}

} // namespace cripto