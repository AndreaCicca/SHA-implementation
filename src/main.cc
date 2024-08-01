#include "hash.hh"
#include "logging.hh"

int main() {
  cripto::init_logging();
  cripto::log_info("Questo è un messaggio di log a livello info");
  cripto::test_hash();
  return 0;
}