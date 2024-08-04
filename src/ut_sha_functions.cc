#include "common_hash.hh"
#include <gtest/gtest.h>
#include "logging.hh"


//! Test con stringa vuota
TEST(SHA1Test, EmptyString) {
    std::string message = "";
    EXPECT_EQ(cripto_test_sha1(message), openssl_test_sha1(message));
}

//! Test con una stringa breve
TEST(SHA1Test, ShortString) {
    std::string message = "Hello, World!";
    EXPECT_EQ(cripto_test_sha1(message), openssl_test_sha1(message));
}

//! Test con una stringa più lunga
TEST(SHA1Test, LongString) {
    std::string message = "This is a longer string to test SHA1 implementation. It should work with various lengths.";
    EXPECT_EQ(cripto_test_sha1(message), openssl_test_sha1(message));
}

//! Test con caratteri speciali
TEST(SHA1Test, SpecialCharacters) {
    std::string message = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./";
    EXPECT_EQ(cripto_test_sha1(message), openssl_test_sha1(message));
}

//! Test con una stringa contenente caratteri non ASCII
TEST(SHA1Test, NonASCIICharacters) {
    std::string message = "こんにちは世界 - Здравствуй, мир - Γειά σου Κόσμε";
    EXPECT_EQ(cripto_test_sha1(message), openssl_test_sha1(message));
}

//! Test con una stringa molto lunga
TEST(SHA1Test, VeryLongString) {
    std::string message(1000000, 'a'); // Stringa di un milione di 'a'
    EXPECT_EQ(cripto_test_sha1(message), openssl_test_sha1(message));
}

int main(int argc, char **argv) {
  cripto::init_logging(false);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}