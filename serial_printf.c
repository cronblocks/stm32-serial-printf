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

static inline void send_string_to_serial(const char* str, UART_HandleTypeDef* uart_handle_ptr) {
	HAL_UART_Transmit(
			uart_handle_ptr,
			(const uint8_t *) str,
			(uint16_t) strlen(str),
			TRANSMISSION_TIMEOUT_MS
			);
}

void serial_printf(UART_HandleTypeDef* uart_handle_ptr, const char* format_str, ...) {
	char final_str[STRING_BUFFER_SIZE];

	for (int _i = 0; _i < STRING_BUFFER_SIZE; _i++) { final_str[_i] = 0; }

	va_list va_args;
	va_start(va_args, format_str);

	int final_str_index = 0;
	char next_char;

	int __temp_index;
	char __temp_char;
	unsigned int __temp_uint;

	for (int format_str_index = 0; format_str_index < strlen(format_str); format_str_index++) {

		next_char = format_str[format_str_index + 1];

		if (format_str[format_str_index] != '%') {

			final_str[final_str_index++] = format_str[format_str_index];

		} else {

			switch (next_char) {

			case 'b':
			case 'B':
				__temp_uint = va_arg(va_args, unsigned int);
				__temp_index = final_str_index;

				while(__temp_uint) {
					final_str[__temp_index++] = 48 + (__temp_uint % 2);
					final_str[__temp_index] = 0;
					__temp_uint /= 2;
				}

				if (__temp_index == final_str_index) {

					// Value is zero
					sprintf(&final_str[final_str_index], "%d", 0);

				} else {

					// Reverse the order
					__temp_index--;
					while (__temp_index > final_str_index) {
						__temp_char = final_str[final_str_index];
						final_str[final_str_index] = final_str[__temp_index];
						final_str[__temp_index] = __temp_char;

						final_str_index++;
						__temp_index--;
					}
				}

				final_str_index = strlen(final_str);
				format_str_index++;
				break;

			case 'd':
			case 'D':
				sprintf(&final_str[final_str_index], "%d", va_arg(va_args, int));
				final_str_index = strlen(final_str);
				format_str_index++;
				break;

			case 'u':
			case 'U':
				sprintf(&final_str[final_str_index], "%u", va_arg(va_args, unsigned int));
				final_str_index = strlen(final_str);
				format_str_index++;
				break;

			case 'x':
				sprintf(&final_str[final_str_index], "%x", va_arg(va_args, unsigned int));
				final_str_index = strlen(final_str);
				format_str_index++;
				break;

			case 'X':
				sprintf(&final_str[final_str_index], "%X", va_arg(va_args, unsigned int));
				final_str_index = strlen(final_str);
				format_str_index++;
				break;

			default:
				final_str[final_str_index++] = format_str[format_str_index];
				break;
			}
		}
	}

	va_end(va_args);

	send_string_to_serial(final_str, uart_handle_ptr);
}

