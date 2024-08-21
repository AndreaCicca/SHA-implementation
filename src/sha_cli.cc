/**
 * @file sha_cli.cc
 * @author Andrea Ciccarello
 * @brief Funzione Main per l'eseguibile che permette di leggere un input da
 * terminale
 * @version 1.0
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "common_hash.hh"

int
main() {
    cripto::init_logging(false);
    std::string input_string;
    std::cout << "Inserisci una stringa: ";
    std::getline(std::cin, input_string);

    std::cout << "Calcolo hash della stringa: \"" << input_string << "\""
              << std::endl;
    cripto::log_trace("Calcolo hash della stringa: \"" + input_string + "\"");

    (void)cripto_test_sha1(input_string);
    (void)openssl_test_sha1(input_string);

    return 0;
}