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

#include "logging.hh"
#include "sha1.hh"
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <vector> // Aggiunto questo include

void cripto_test_sha1(const std::string &message) {
  uint8_t digest[cripto::SHA1_DIGEST_SIZE];

  cripto::SHA1 sha1;

  // Eseguo la prima parte dell'hash e converto la stringa in un array di byte
  sha1.update(reinterpret_cast<const uint8_t *>(message.data()),
              message.length());

  // Eseguo la seconda parte dell'hash ed estraggo il digest a 160 bit
  sha1.final(digest);

  // Converto il digest in una stringa esadecimale
  std::string result =
      cripto::SHA1::toHexString(digest, cripto::SHA1_DIGEST_SIZE);
  std::cout << "Cripto  SHA1: " << result << std::endl;
  cripto::log_trace("Cripto  SHA1: " + result);
}

void openssl_test_sha1(const std::string &message) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(reinterpret_cast<const unsigned char *>(message.data()),
       message.length(), hash);

  std::string hash_string = cripto::SHA1::toHexString(hash, SHA_DIGEST_LENGTH);
  std::cout << "OpenSSL SHA1: " << hash_string << std::endl;
  cripto::log_trace("OpenSSL SHA1: " + hash_string);
}

int main() {

  cripto::init_logging(true);

  std::vector<std::string> test_cases = {
      "",
      "a",
      "abc",
      "message digest",
      "abcdefghijklmnopqrstuvwxyz",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
      "123456789012345678901234567890123456789012345678901234567890123456789012"
      "34567890",
      "Nel mezzo del cammin di nostra vita mi ritrovai per una selva oscura",
      "ché la diritta via era smarrita."};

  for (const auto &test : test_cases) {
    std::cout << "Testing message: \"" << test << "\"" << std::endl;
    cripto::log_trace("Testing message: \"" + test + "\"");
    cripto_test_sha1(test);
    openssl_test_sha1(test);
    std::cout << std::endl;
  }

  return 0;
}