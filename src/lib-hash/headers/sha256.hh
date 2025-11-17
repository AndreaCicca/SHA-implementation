/**
 * @file sha256.hh
 * @author Andrea Ciccarello
 * @brief Definizione classe SHA256
 * @version 1.0
 * @date 2024-11-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <cstdint>
#include <string>

namespace cripto {

constexpr unsigned int SHA256_BLOCK_SIZE  = 64; // 512 bits
constexpr unsigned int SHA256_DIGEST_SIZE = 32; // 256 bits

class SHA256 {
  public:
    SHA256();
    void               initialization(const uint8_t *data, size_t length);
    void               final(uint8_t digest[SHA256_DIGEST_SIZE]);
    static std::string toHexString(const uint8_t *digest, size_t length);

  private:
    void transform(const uint8_t block[SHA256_BLOCK_SIZE]);
    void padding();

    //! I 8 registri di stato inizializzati con i valori iniziali
    //! specificati dallo standard SHA-256.
    uint32_t state[8];

    //! Tiene traccia del numero di bit processati fino a questo momento.
    uint64_t bitCount;

    /**
     * @brief Lunghezza corrente del buffer interno per accumulare i dati
     * prima di processarlo. Quando si raggiungono i 64 byte (512 bit) il
     * buffer viene processato e il bufferLength azzerato.
     *
     * @note Il buffer è di 64 byte (512 bit) come specificato dallo
     * standard.
     */
    size_t bufferLength;

    /**
     * @brief Numero del blocco da elaborare che ha come scopo quello di
     * migliorare l'output del logging a livello trace.
     */
    uint64_t block_number;

    uint8_t buffer[SHA256_BLOCK_SIZE];
};

} // namespace cripto

// Pseudocodice SHA-256
//
// Initialize hash values:
// (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
// h0 := 0x6a09e667
// h1 := 0xbb67ae85
// h2 := 0x3c6ef372
// h3 := 0xa54ff53a
// h4 := 0x510e527f
// h5 := 0x9b05688c
// h6 := 0x1f83d9ab
// h7 := 0x5be0cd19
//
// Initialize array of round constants:
// (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
// k[0..63] := 
//   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
//   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
//   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
//   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
//   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
//   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
//   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
//   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
//
// Pre-processing (Padding):
// append the bit '1' to the message e.g. by adding 0x80 if message length is a multiple of 8 bits.
// append 0 ≤ k < 512 bits '0', such that the resulting message length in bits
//    is congruent to −64 ≡ 448 (mod 512)
// append ml, the original message length, as a 64-bit big-endian integer.
//    Thus, the total length is a multiple of 512 bits.
//
// Process the message in successive 512-bit chunks:
// break message into 512-bit chunks
// for each chunk
//     create a 64-entry message schedule array w[0..63] of 32-bit words
//     copy chunk into first 16 words w[0..15] of the message schedule array
//
//     Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array:
//     for i from 16 to 63
//         s0 := (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
//         s1 := (w[i-2] rightrotate 17) xor (w[i-2] rightrotate 19) xor (w[i-2] rightshift 10)
//         w[i] := w[i-16] + s0 + w[i-7] + s1
//
//     Initialize working variables to current hash value:
//     a := h0
//     b := h1
//     c := h2
//     d := h3
//     e := h4
//     f := h5
//     g := h6
//     h := h7
//
//     Compression function main loop:
//     for i from 0 to 63
//         S1 := (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
//         ch := (e and f) xor ((not e) and g)
//         temp1 := h + S1 + ch + k[i] + w[i]
//         S0 := (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
//         maj := (a and b) xor (a and c) xor (b and c)
//         temp2 := S0 + maj
// 
//         h := g
//         g := f
//         f := e
//         e := d + temp1
//         d := c
//         c := b
//         b := a
//         a := temp1 + temp2
//
//     Add the compressed chunk to the current hash value:
//     h0 := h0 + a
//     h1 := h1 + b
//     h2 := h2 + c
//     h3 := h3 + d
//     h4 := h4 + e
//     h5 := h5 + f
//     h6 := h6 + g
//     h7 := h7 + h
//
// Produce the final hash value (big-endian):
// digest := h0 append h1 append h2 append h3 append h4 append h5 append h6 append h7
