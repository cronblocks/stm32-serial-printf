/*
 * serial_print.h
 *
 *  Created on: Jun 10, 2022
 *      Author: usama
 */

#ifndef _SERIAL_PRINTF_H_
#define _SERIAL_PRINTF_H_

#include "main.h"

#define TRANSMISSION_TIMEOUT_MS      20
#define STRING_BUFFER_SIZE           100

/**
 * Supported formats:
 * %b, %B - Binary
 * %1/2/3/4b, %1/2/3/4B - Binary with 1/2/3/4 Bytes, e.g., %2b
 * %d, %D - Decimal
 * %u, %U - Unsigned Decimal
 * %x     - Hex of Unsigned Decimal with Lower-case Letters
 * %X     - Hex of Unsigned Decimal with Upper-case Letters
 *
 */
void serial_printf(UART_HandleTypeDef* uart_handle_ptr, const char* format_str, ...);



#endif /* _SERIAL_PRINTF_H_ */
