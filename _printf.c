#include "holberton.h"
#include <stdarg.h>
#include <stdio.h>

/**
 *_printf - own printf function
 *@format: format
 *Return: numbers of bytes
 */
int _printf(const char *format, ...)
{
	int bytes = 0;
	va_list arglist;
	opt op_func[] = {{"s", print_string}, {"c", print_char},
			 {"d", print_int}, {"i", print_int}, {"b", print_binary},
			 {"o", print_octal}, {"x", print_hexadecimal},
			 {"X", print_hexadecimal_X}, {"u", print_decimal},
			 {"R", print_rot13}, {"r", print_rev},
			 {"S", print_to_hexa}, {"p", print_address}, {NULL, NULL}};

	if (format == NULL)
		return (-1);
	va_start(arglist, format);
	bytes = _print_aux(format, arglist, op_func);
	va_end(arglist);
	return (bytes);
}
/**
 *_print_aux - own printf function
 *@format: format
 *@arglist: argument list
 *@op_func: structure of options
 *Return: numbers of bytes
 */
int _print_aux(const char *format, va_list arglist, opt *op_func)
{
	int i = 0, j = 0, bytes = 0;

	while (format[i] != '\0' && format != NULL)
	{
		if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		j = 0;
		if (format[i] == '%' && (format[i + 1] == ' ' || format[i + 1] != '%'))
		{
			if (format[i + 1] == ' ')
			{
				while (format[i + 1] == ' ')
					i++;
			}
			while (j < 13)
			{
				if (op_func[j].reference[0] == format[i + 1])
				{
					bytes += op_func[j].function(arglist);
					i++;
					break;
				}
				j++;
			}
			if (j == 13)
				bytes += _putchar(format[i]);
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			bytes += _putchar('%');
			i++;
		}
		else
			bytes += _putchar(format[i]);
		i++;
	}
	return (bytes);
}
