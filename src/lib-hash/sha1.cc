#include "sha1.hh"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>

namespace cripto {

/**
 * @brief Funzione che ruota a sinistra un valore di 32 bit
 *
 * @param value valore da ruotare
 * @param count numero di posizioni di cui ruotare il ruotare il valore
 * @return uint32_t valore ruotato
 */
inline uint32_t leftRotate(uint32_t value, unsigned int count) {
  // shift a sinistra di count posizioni
  // shift a destra di 32 - count posizioni
  return (value << count) | (value >> (32 - count));
}

/**
 * @brief Costruttore
 *
 * Ci sono 5 registri di stato inizializzati con i valori iniziali
 * specificati dallo standard.
 *
 * A = 0x67452301, B = 0xEFCDAB89, C = 0x98BADCFE,
 * D = 0x10325476, E = 0xC3D2E1F0
 *
 * Il contatore di bit è inizializzato a 0 e la lunghezza del buffer a 0.
 *
 */
SHA1::SHA1()
    : state{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0},
      bitCount(0), bufferLength(0) {}

/**
 * @brief Funcione che ha il compito di dividere i dati in blocchi di 512 bit,
 * quando il buffer è pieno verranno processati tramite la funzione transform
 *
 * @param data
 * @param length
 */
void SHA1::update(const uint8_t *data, size_t length) {
  // tutti i dati devono essere processati
  while (length > 0) {
    // Quanti byte posso copiare nel buffer
    // minimo tra length e e lo spazio disponibile nel buffer
    size_t toCopy = std::min(length, SHA1_BLOCK_SIZE - bufferLength);
    // Copio i dati nel buffer
    // buffer è al massimo 512 bit
    std::memcpy(buffer + bufferLength, data, toCopy);
    bufferLength += toCopy;
    data += toCopy;
    length -= toCopy;

    // se il buffer è pieno allora lo si deve processare
    if (bufferLength == SHA1_BLOCK_SIZE) {

      // processamento del buffer
      transform(buffer);
      bitCount += 512;
      bufferLength = 0;
    }
  }
}

void SHA1::transform(const uint8_t block[SHA1_BLOCK_SIZE]) {
  uint32_t w[80];

  // Conversione dei messaggi in 16 parole da 32 bit
  // 512 bit = 16 parole da 32 bit
  for (int i = 0; i < 16; ++i) {
    w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
           (block[i * 4 + 2] << 8) | block[i * 4 + 3];
  }

  // Espanzione delle parole in 80 parole da 32 bit
  for (int i = 16; i < 80; ++i) {
    w[i] = leftRotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
  }

  // copio i 5 stati nelle variabili locali
  // andrò soltanto a modificare queste variabili,
  // in questo modo l'output della funzione di hash sarà sempre
  // 5 * 32 bit = 160 bit
  uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];

  // Le 80 iterazioni per il calcolo dell'hash
  // ^ = XOR -> OR esclusivo
  // & = AND
  // | = OR
  // ~ = NOT 1 -> 0, 0 -> 1

  for (int i = 0; i < 80; ++i) {
    uint32_t f, k;
    if (i < 20) {
      f = (b & c) | ((~b) & d);
      k = 0x5A827999;
    } else if (i < 40) {
      f = b ^ c ^ d;
      k = 0x6ED9EBA1;
    } else if (i < 60) {
      f = (b & c) | (b & d) | (c & d);
      k = 0x8F1BBCDC;
    } else {
      f = b ^ c ^ d;
      k = 0xCA62C1D6;
    }

    uint32_t temp = leftRotate(a, 5) + f + e + k + w[i];
    e = d;
    d = c;
    c = leftRotate(b, 30);
    b = a;
    a = temp;
  }

  // Aggiornamento dello stato generale.
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
}

/**
 * @brief Funzione di padding
 *
 */
void SHA1::pad() {
  bitCount += bufferLength * 8;
  // aggiunta di un bit a 1 alla fine del messaggio
  buffer[bufferLength++] = 0x80;
  // Se la lunghezza del buffer con il bit aggiunto è maggiore di 448 bit
  // allora non ci sarà abbastanza spazio per aggiungere la lunghezza
  // di 64 bit del messaggio.
  if (bufferLength > 56) {
    // Riepio il buffer con 0 fino a 512 bit
    std::memset(buffer + bufferLength, 0, SHA1_BLOCK_SIZE - bufferLength);
    // calcolo l'hash parziale del blocco
    transform(buffer);
    bufferLength = 0;
  }

  // padding con 0 fino a 56 byte (448 bit)
  std::memset(buffer + bufferLength, 0, 56 - bufferLength);

  // aggiunta della lunghezza del messaggio come un numero a 64 bit
  // alla fine del blocco
  // 448 + 64 = 512 bit
  for (int i = 0; i < 8; ++i) {
    buffer[56 + i] = (bitCount >> ((7 - i) * 8)) & 0xFF;
  }

  transform(buffer);
}

/**
 * @brief Conclusione dell'hash e restituzione del digest
 *
 * @param digest
 */
void SHA1::final(uint8_t digest[SHA1_DIGEST_SIZE]) {
  pad();

  for (int i = 0; i < 5; ++i) {
    digest[i * 4] = (state[i] >> 24) & 0xFF;
    digest[i * 4 + 1] = (state[i] >> 16) & 0xFF;
    digest[i * 4 + 2] = (state[i] >> 8) & 0xFF;
    digest[i * 4 + 3] = state[i] & 0xFF;
  }
}

std::string SHA1::toHexString(const uint8_t *digest, size_t length) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (size_t i = 0; i < length; ++i) {
    ss << std::setw(2) << static_cast<unsigned int>(digest[i]);
  }
  return ss.str();
}

} // namespace cripto