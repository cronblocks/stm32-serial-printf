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
	char identifier_char;
	char identifier_modifier;

	int __temp_index;
	int __temp_count;
	char __temp_char;
	unsigned int __temp_uint;

	for (int format_str_index = 0; format_str_index < strlen(format_str); format_str_index++) {

		identifier_char = format_str[format_str_index + 1];
		identifier_modifier = -1;

		if ( (identifier_char == '0' ||
			  identifier_char == '1' ||
			  identifier_char == '2' ||
			  identifier_char == '3' ||
			  identifier_char == '4') && (format_str_index + 1 < strlen(format_str)) ) {

			identifier_modifier = format_str[format_str_index + 2];

			if (identifier_modifier == 'b' || identifier_modifier == 'B') {
				__temp_char = identifier_modifier;
				identifier_modifier = identifier_char - 48;
				identifier_char = __temp_char;
			} else {
				identifier_modifier = -1;
			}
		}

		if (format_str[format_str_index] != '%') {

			final_str[final_str_index++] = format_str[format_str_index];

		} else {

			switch (identifier_char) {

			case 'b':
			case 'B':
				__temp_uint = va_arg(va_args, unsigned int);
				__temp_index = final_str_index;
				__temp_count = 0;

				while(__temp_uint) {
					final_str[__temp_index++] = 48 + (__temp_uint % 2);
					final_str[__temp_index] = 0;

					__temp_uint /= 2;
					__temp_count++;
				}

				if (__temp_index == final_str_index) {

					// Value is zero
					switch (identifier_modifier) {
					case 0:
					case 1:  sprintf(&final_str[final_str_index], "00000000");                         break;
					case 2:  sprintf(&final_str[final_str_index], "0000000000000000");                 break;
					case 3:	 sprintf(&final_str[final_str_index], "000000000000000000000000");         break;
					case 4:  sprintf(&final_str[final_str_index], "00000000000000000000000000000000"); break;
					default: sprintf(&final_str[final_str_index], "0"); break;
					}

				} else {

					// Fill zeros if required
					if (identifier_modifier >= 0 && identifier_modifier <= 4) {
						if (identifier_modifier == 0) {
							while (identifier_modifier * 8 < __temp_count) identifier_modifier++;
						}

						while (__temp_count < identifier_modifier * 8) {
							final_str[__temp_index++] = 48;
							final_str[__temp_index] = 0;

							__temp_count++;
						}
					}

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

				if (identifier_modifier >= 0 && identifier_modifier <= 4) {
					format_str_index++; // Extra addition
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

