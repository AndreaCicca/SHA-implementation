#include "common_hash.hh"
#include "logging.hh"
#include <gtest/gtest.h>
#include <random>

namespace {

static const std::string caratteri =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

std::string
generaStringaCasuale(int lunghezza) {
    std::random_device rd; // Generatore di numeri casuali basato su hardware
    std::mt19937       gen(rd()); // Mersenne Twister PRNG, rd è il seed
    std::uniform_int_distribution<> distribuzione(0, caratteri.size() - 1);

    std::string stringaCasuale;
    for (int i = 0; i < lunghezza; ++i)
    {
        stringaCasuale += caratteri[distribuzione(gen)];
    }

    return stringaCasuale;
}
} // namespace

//! Test con stringa vuota
TEST(SHA1Test, EmptyString) {
    std::string message = "";
    EXPECT_EQ(cripto_test_sha1(message, false),
              openssl_test_sha1(message, false));
}

//! Test con una stringa breve
TEST(SHA1Test, ShortString) {
    std::string message = "Hello, World!";
    EXPECT_EQ(cripto_test_sha1(message, false),
              openssl_test_sha1(message, false));
}

//! Test con una stringa più lunga
TEST(SHA1Test, LongString) {
    std::string message =
      "This is a longer string to test SHA1 implementation. "
      "It should work with various lengths.";
    EXPECT_EQ(cripto_test_sha1(message, false),
              openssl_test_sha1(message, false));
}

//! Test con caratteri speciali
TEST(SHA1Test, SpecialCharacters) {
    std::string message = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./";
    EXPECT_EQ(cripto_test_sha1(message, false),
              openssl_test_sha1(message, false));
}

//! Test con una stringa contenente caratteri non ASCII
TEST(SHA1Test, NonASCIICharacters) {
    std::string message = "こんにちは世界 Здравствуй Κόσμε";
    EXPECT_EQ(cripto_test_sha1(message, false),
              openssl_test_sha1(message, false));
}

//! Test con una stringa molto lunga
TEST(SHA1Test, VeryLongString) {
    std::string message(1000000, 'a'); // Stringa di un milione di 'a'
    EXPECT_EQ(cripto_test_sha1(message, false),
              openssl_test_sha1(message, false));
}

//! Generazione causale di stringhe
TEST(SHA1Test, RandomString) {
    for (int k = 0; k < 100; ++k)
    {
        std::string random_message = "";
        for (int i = 0; i < 100; ++i)
        {
            random_message += generaStringaCasuale(100);
        }
        EXPECT_EQ(cripto_test_sha1(random_message, false),
                  openssl_test_sha1(random_message, false));
    }
}

//! Test determinismo con la stessa stringa
TEST(SHA1Test, Determinism) {
    std::string message = "Hello, World!";
    auto        digest  = cripto_test_sha1(message, false);

    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(digest, cripto_test_sha1(message, false));
        EXPECT_EQ(digest, openssl_test_sha1(message, false));
    }
}

//! Test effetto a valanga
TEST(SHA1Test, AvalancheEffect) {
    std::string message = "Hello, World!";
    auto        digest  = cripto_test_sha1(message, false);

    for (size_t i = 0; i < message.size(); ++i)
    {
        std::string modified_message = message;
        modified_message[i]          = 'a';
        EXPECT_NE(digest, cripto_test_sha1(modified_message, false));
        EXPECT_NE(digest, openssl_test_sha1(modified_message, false));
    }
}

//! Performance
TEST(SHA1Test, Performance) {
    std::string message(1000000, 'a'); // Stringa di un milione di 'a'

    auto start = std::chrono::high_resolution_clock::now();
    cripto_test_sha1(message, false);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        .count();
    cripto::log_trace("SHA1: Performance test completed in " +
                     std::to_string(duration) + " ms");

    EXPECT_LT(duration, 1000);
}

int
main(int argc, char **argv) {
    cripto::init_logging();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}