/**
 * @file sha256.cc
 * @author Andrea Ciccarello
 * @brief Implementazione della classe SHA256
 * @version 1.0
 * @date 2024-11-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "sha256.hh"
#include "logging.hh"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>

namespace cripto {

/**
 * @brief Funzione che ruota a destra un valore di 32 bit
 *
 * @param value valore da ruotare
 * @param count numero di posizioni di cui ruotare il valore
 * @return uint32_t valore ruotato
 */
inline uint32_t
rightRotate(uint32_t value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}

/**
 * @brief Funzione che shifta a destra un valore di 32 bit
 *
 * @param value valore da shiftare
 * @param count numero di posizioni di cui shiftare il valore
 * @return uint32_t valore shiftato
 */
inline uint32_t
rightShift(uint32_t value, unsigned int count) {
    return value >> count;
}

/**
 * @brief Costruttore della classe SHA256
 *
 * Ci sono 8 registri di stato inizializzati con i valori iniziali
 * specificati dallo standard SHA-256.
 *
 * Questi valori sono i primi 32 bit delle parti frazionarie delle
 * radici quadrate dei primi 8 numeri primi (2, 3, 5, 7, 11, 13, 17, 19).
 *
 * Il contatore di bit è inizializzato a 0 e la lunghezza del buffer a 0.
 */
SHA256::SHA256()
  : state{0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
          0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19},
    bitCount(0), bufferLength(0), block_number(0), buffer{} {
}

/**
 * @brief Funzione che ha il compito di dividere i dati in blocchi di 512 bit,
 * quando il buffer è pieno verranno processati tramite la funzione transform
 *
 * @param data puntatore ai dati da processare
 * @param length lunghezza dei dati in byte
 */
void
SHA256::initialization(const uint8_t *data, size_t length) {
    // tutti i dati devono essere processati
    while (length > 0)
    {
        // Quanti byte posso copiare nel buffer
        // minimo tra length e lo spazio disponibile nel buffer.
        size_t toCopy = std::min(length, SHA256_BLOCK_SIZE - bufferLength);
        // Copio i dati nel buffer
        std::memcpy(buffer + bufferLength, data, toCopy);
        bufferLength = bufferLength + toCopy;

        // data puntatore alla posizione successiva
        data   = data + toCopy;
        length = length - toCopy;

        // se il buffer è pieno allora lo si deve processare
        if (bufferLength == SHA256_BLOCK_SIZE)
        {
            // processamento del buffer
            transform(buffer);

            bitCount += 512;
            bufferLength = 0;
        }
    }
}

/**
 * @brief Funzione di trasformazione che permette di processare un blocco
 *
 * @param block blocco di 512 bit da processare
 */
void
SHA256::transform(const uint8_t block[SHA256_BLOCK_SIZE]) {
    // Array delle costanti K per SHA-256
    // Primi 32 bit delle parti frazionarie delle radici cubiche
    // dei primi 64 numeri primi (2..311)
    static const uint32_t k[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
      0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
      0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
      0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
      0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
      0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
      0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
      0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
      0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
      0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    uint32_t w[64];

    // Incremento block number
    ++block_number;

    // Conversione dei blocchi in 16 parole da 32 bit
    // 512 bit = 16 parole da 32 bit
    for (int i = 0; i < 16; ++i)
    {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
               (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    // Espansione delle parole da 16 parole a 64 parole
    for (int i = 16; i < 64; ++i)
    {
        uint32_t s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^
                      rightShift(w[i - 15], 3);
        uint32_t s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^
                      rightShift(w[i - 2], 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    std::string block_number_string = std::to_string(block_number);
    cripto::log_trace("SHA256: Processing block N°: " + block_number_string);

    // copio gli 8 stati nelle variabili locali
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3],
             e = state[4], f = state[5], g = state[6], h = state[7];

    // Le 64 iterazioni per il calcolo dell'hash
    for (int i = 0; i < 64; ++i)
    {
        uint32_t S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
        uint32_t ch = (e & f) ^ ((~e) & g);
        uint32_t temp1 = h + S1 + ch + k[i] + w[i];
        uint32_t S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // Aggiornamento dello stato generale
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;

    for (int i = 0; i < 8; ++i)
    {
        cripto::log_trace("SHA256: State " + std::to_string(i) + " = " +
                          std::to_string(state[i]));
    }
}

/**
 * @brief Funzione di padding
 */
void
SHA256::padding() {
    bitCount += bufferLength * 8;
    // aggiunta di un bit a 1 alla fine del messaggio
    buffer[bufferLength++] = 0x80;
    
    // Se la lunghezza del buffer con il bit aggiunto è maggiore di 448 bit
    // allora non ci sarà abbastanza spazio per aggiungere la lunghezza
    // di 64 bit del messaggio.
    if (bufferLength > 56)
    {
        cripto::log_trace("SHA256: Ultimo blocco non rispetta 448 mod 512");
        // Riempio il buffer con 0 fino a 512 bit
        std::memset(buffer + bufferLength, 0, SHA256_BLOCK_SIZE - bufferLength);
        // calcolo l'hash parziale del blocco
        transform(buffer);
        bufferLength = 0;
    }

    // padding con 0 fino a 56 byte (448 bit)
    std::memset(buffer + bufferLength, 0, 56 - bufferLength);

    // aggiunta della lunghezza del messaggio come un numero a 64 bit
    // alla fine del blocco
    // 448 + 64 = 512 bit
    for (int i = 0; i < 8; ++i)
    {
        buffer[56 + i] = (bitCount >> ((7 - i) * 8)) & 0xFF;
    }

    cripto::log_trace(
      "SHA256: Elaborazione blocco finale con padding e lunghezza del messaggio");
    transform(buffer);
}

/**
 * @brief Conclusione dell'hash e restituzione del digest
 *
 * @param digest array di 32 byte dove verrà scritto il digest
 */
void
SHA256::final(uint8_t digest[SHA256_DIGEST_SIZE]) {
    padding();

    for (int i = 0; i < 8; ++i)
    {
        digest[i * 4]     = (state[i] >> 24) & 0xFF;
        digest[i * 4 + 1] = (state[i] >> 16) & 0xFF;
        digest[i * 4 + 2] = (state[i] >> 8) & 0xFF;
        digest[i * 4 + 3] = state[i] & 0xFF;
    }
}

/**
 * @brief Funzione che converte un digest in una stringa esadecimale
 *
 * @param digest array di byte del digest
 * @param length lunghezza del digest in byte
 * @return std::string rappresentazione esadecimale del digest
 */
std::string
SHA256::toHexString(const uint8_t *digest, size_t length) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
    {
        ss << std::setw(2) << static_cast<unsigned int>(digest[i]);
    }
    return ss.str();
}

} // namespace cripto
