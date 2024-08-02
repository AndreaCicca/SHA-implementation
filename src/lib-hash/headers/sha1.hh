#pragma once
#include <cstdint>
#include <string>

namespace cripto {

constexpr unsigned int SHA1_BLOCK_SIZE = 64;  // 512 bits
constexpr unsigned int SHA1_DIGEST_SIZE = 20; // 160 bits

class SHA1 {
public:
  SHA1();
  void update(const uint8_t *data, size_t length);
  void final(uint8_t digest[SHA1_DIGEST_SIZE]);
  static std::string toHexString(const uint8_t *digest, size_t length);

private:
  void transform(const uint8_t block[SHA1_BLOCK_SIZE]);
  void pad();

  uint32_t state[5];
  uint64_t bitCount;
  uint8_t buffer[SHA1_BLOCK_SIZE];
  size_t bufferLength;
};

} // namespace cripto