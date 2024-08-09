#include "common_hash.hh"
#include "logging.hh"
#include <gtest/gtest.h>
#include <random>

namespace {
std::string
generaStringaCasuale(int lunghezza) {
    // Definisco i caratteri possibili
    const std::string caratteri =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::random_device rd; // Generatore di numeri casuali basato su hardware
    std::mt19937       gen(rd()); // Mersenne Twister PRNG
    std::uniform_int_distribution<> distribuzione(0, caratteri.size() - 1);

    std::string stringaCasuale;
    for (int i = 0; i < lunghezza; ++i) {
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
    for (int i = 0; i < 1000; ++i) {
        auto random_message = generaStringaCasuale(i);
        EXPECT_EQ(cripto_test_sha1(random_message, false),
                  openssl_test_sha1(random_message, false));
    }
}

int
main(int argc, char **argv) {
    cripto::init_logging(false);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}