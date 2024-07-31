#include "logging.hh"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

void init_logging() {
  logging::register_simple_formatter_factory<logging::trivial::severity_level,
                                             char>("Severity");

  logging::add_file_log(
      keywords::file_name = "log_%N.log",
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::time_based_rotation =
          logging::sinks::file::rotation_at_time_point(0, 0, 0),
      keywords::format = "[%TimeStamp%] [%Severity%] %Message%");

  logging::core::get()->set_filter(logging::trivial::severity >=
                                   logging::trivial::info);

  logging::add_common_attributes();
}

// Funzione per logare facilmente a livello info
void log_info(const std::string &message) {
  BOOST_LOG_TRIVIAL(info) << message;
}

void log_error(const std::string &message) {
  BOOST_LOG_TRIVIAL(error) << message;
}

void log_warning(const std::string &message) {
  BOOST_LOG_TRIVIAL(warning) << message;
}

void log_debug(const std::string &message) {
  BOOST_LOG_TRIVIAL(debug) << message;
}

void log_fatal(const std::string &message) {
  BOOST_LOG_TRIVIAL(fatal) << message;
}