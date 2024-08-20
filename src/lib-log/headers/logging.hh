/**
 * @file logging.hh
 * @author Andrea Ciccarello
 * @brief Definizione delle funzioni di logging
 * @version 1.0
 * @date 2024-08-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

namespace cripto {

/**
 * @brief Inizializzazione del logging tramite la libreria boost
 * 
 * @param trace 
 */
void
init_logging(bool trace = false);

/**
 * @brief Stampa del messaggio con la priorità trace
 * 
 * @param message 
 */
void
log_trace(const std::string &message);

/**
 * @brief Stampa del messaggio con la priorità @a trace
 * 
 * @param message 
 */
void
log_info(const std::string &message);

/**
 * @brief Stampa del messaggio con la priorità @a info
 * 
 * @param message 
 */
void
log_error(const std::string &message);

/**
 * @brief Stampa del messaggio con la priorità @a warning
 * 
 * @param message 
 */
void
log_warning(const std::string &message);

/**
 * @brief Stampa del messaggio con la priorità @a  debug
 * 
 * @param message 
 */
void
log_debug(const std::string &message);

/**
 * @brief Stampa del messaggio con la priorità @a fatal
 * 
 * @param message 
 */
void
log_fatal(const std::string &message);

} // namespace cripto