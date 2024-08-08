/**
 * @file main.cc
 * @author Andrea Ciccarello
 * @brief Funzione Main con il test delle di SHA1 tramite openssl
 * @version 1.0
 * @date 2024-08-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "common_hash.hh"
#include "logging.hh"

int
main() {

	cripto::init_logging(true);

	std::vector<std::string> test_cases = {
	  "",
	  "a",
	  "abc",
	  "message digest",
	  "abcdefghijklmnopqrstuvwxyz",
	  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
	  "1234567890123456789012345678901234567890123456789012345678901234",
	  "Nel mezzo del cammin di nostra vita mi ritrovai per una selva "
	  "oscura"};

	for (const auto &test : test_cases) {
		std::cout << "Testing message: \"" << test << "\"" << std::endl;
		cripto::log_trace("Testing message: \"" + test + "\"");
		(void)cripto_test_sha1(test);
		(void)openssl_test_sha1(test);
		std::cout << std::endl;
	}

	// commedia.txt
	try {
		std::string commedia_content = read_file("commedia.txt");
		std::cout << "Calcolo hash di commedia.txt" << std::endl;
		cripto::log_trace("Calcolo hash di commedia.txt");
		(void)cripto_test_sha1(commedia_content);
		(void)openssl_test_sha1(commedia_content);
	} catch (const std::exception &e) {
		std::cerr << "Errore: " << e.what() << std::endl;
		cripto::log_error(
		  "Errore durante la lettura di commedia.txt: " +
		  std::string(e.what()));
	}

	return 0;
}