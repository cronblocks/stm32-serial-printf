/*
 * serial_print.h
 *
 *  Created on: Jun 10, 2022
 *      Author: usama
 */

#ifndef _SERIAL_PRINTF_H_
#define _SERIAL_PRINTF_H_

#include "stm32f7xx_hal.h"

#define SERIAL_TRANSMISSION_TIMEOUT_MS      20
#define SERIAL_STRING_BUFFER_SIZE           200

/**
 * Supported formats:
 * %b, %B   - Binary
 * %0b, %0B - Binary Filled with Leading Zeros up to Nearest Byte, e.g., %0b
 * %1b, %1B - Binary with 1 Byte Width - Filled with Leading Zeros, e.g., %1b
 * %2b, %2B - Binary with 2 Byte Width - Filled with Leading Zeros, e.g., %2b
 * %3b, %3B - Binary with 3 Byte Width - Filled with Leading Zeros, e.g., %3b
 * %4b, %4B - Binary with 4 Byte Width - Filled with Leading Zeros, e.g., %4b
 * %c, %C   - ASCII Character
 * %d, %D   - Decimal
 * %u, %U   - Unsigned Decimal
 * %x       - Hex of Unsigned Decimal with Lower-case Letters
 * %X       - Hex of Unsigned Decimal with Upper-case Letters
 *
 * e.g., serial_printf(&huart1, "Binary = %4b, Hex = 0x%X", value, value);
 */
void serial_printf(UART_HandleTypeDef* uart_handle_ptr, const char* format_str, ...);



#endif /* _SERIAL_PRINTF_H_ */
