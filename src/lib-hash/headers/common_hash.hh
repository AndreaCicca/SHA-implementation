/**
 * @file common_hash.hh
 * @author Andrea Ciccarello
 * @brief Common header file for hash functions
 * @version 1.0
 * @date 2024-08-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "logging.hh"
#include "sha0.hh"
#include "sha1.hh"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string
cripto_test_sha1(const std::string &message, const bool isPrintable = true) {
    uint8_t digest[cripto::SHA1_DIGEST_SIZE];

    cripto::SHA1 sha1;

    // Eseguo la prima parte dell'hash e converto la stringa in un array di
    // byte
    sha1.initialization(reinterpret_cast<const uint8_t *>(message.data()),
                        message.length());

    // Eseguo la seconda parte dell'hash ed estraggo il digest a 160 bit
    sha1.final(digest);

    // Converto il digest in una stringa esadecimale
    std::string result =
      cripto::SHA1::toHexString(digest, cripto::SHA1_DIGEST_SIZE);
    if (isPrintable)
    {
        std::cout << "Cripto  SHA1: " << result << std::endl;
        cripto::log_trace("Cripto  SHA1: " + result);
    }

    return result;
}

std::string
cripto_test_sha0(const std::string &message, const bool isPrintable = true) {
    uint8_t digest[cripto::SHA0_DIGEST_SIZE];

    cripto::SHA0 sha0;

    // Eseguo la prima parte dell'hash e converto la stringa in un array di
    // byte
    sha0.initialization(reinterpret_cast<const uint8_t *>(message.data()),
                        message.length());

    // Eseguo la seconda parte dell'hash ed estraggo il digest a 160 bit
    sha0.final(digest);

    // Converto il digest in una stringa esadecimale
    std::string result =
      cripto::SHA0::toHexString(digest, cripto::SHA0_DIGEST_SIZE);
    if (isPrintable)
    {
        std::cout << "Cripto  SHA0: " << result << std::endl;
        cripto::log_trace("Cripto  SHA0: " + result);
    }
    return result;
}

std::string
openssl_test_sha1(const std::string &message, const bool isPrintable = true) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char *>(message.data()),
         message.length(), hash);

    std::string hash_string =
      cripto::SHA1::toHexString(hash, SHA_DIGEST_LENGTH);
    if (isPrintable)
    {
        std::cout << "OpenSSL SHA1: " << hash_string << std::endl;
        cripto::log_trace("OpenSSL SHA1: " + hash_string);
    }
    return hash_string;
}

std::string
read_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Impossibile aprire il file: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}