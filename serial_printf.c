/*
 * serial_print.c
 *
 *  Created on: Jun 10, 2022
 *      Author: usama
 */
#include "../serial_printf/serial_printf.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

static inline void send_string_to_serial(const char* str, UART_HandleTypeDef* uart_ptr) {
	HAL_UART_Transmit(
			uart_ptr,
			(const uint8_t *)str,
			(uint16_t)strlen(str),
			TRANSMISSION_TIMEOUT_MS
			);
}

void serial_printf(UART_HandleTypeDef* uart_ptr, const char* format_str, ...) {
	char temp[TEMP_BUFFER_SIZE];

	for (int _i = 0; _i < TEMP_BUFFER_SIZE; _i++) {
		temp[_i] = 0;
	}

	va_list va_args;
	va_start(va_args, format_str);

	int temp_index = 0;
	char next_char;

	for (int format_str_index = 0; format_str_index < strlen(format_str); format_str_index++) {

		next_char = format_str[format_str_index + 1];

		if (format_str[format_str_index] != '%') {
			temp[temp_index++] = format_str[format_str_index];
		} else {
			switch (next_char) {

			case 'd':
			case 'D':
				sprintf(&temp[temp_index], "%d", va_arg(va_args, int));
				temp_index = strlen(temp);
				format_str_index++;
				break;

			case 'u':
			case 'U':
				sprintf(&temp[temp_index], "%u", va_arg(va_args, unsigned int));
				temp_index = strlen(temp);
				format_str_index++;
				break;

			case 'x':
				sprintf(&temp[temp_index], "0x%x", va_arg(va_args, unsigned int));
				temp_index = strlen(temp);
				format_str_index++;
				break;

			case 'X':
				sprintf(&temp[temp_index], "0x%X", va_arg(va_args, unsigned int));
				temp_index = strlen(temp);
				format_str_index++;
				break;

			default:
				temp[temp_index++] = format_str[format_str_index];
				break;
			}
		}
	}

	va_end(va_args);

	send_string_to_serial(temp, uart_ptr);
}

