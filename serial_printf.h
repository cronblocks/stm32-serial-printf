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

void serial_printf(UART_HandleTypeDef* uart_handle_ptr, const char* format_str, ...);



#endif /* _SERIAL_PRINTF_H_ */
