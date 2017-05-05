#include "ft_printf.h"

int				ft_printf(char *str, ...)
{
	va_list		argp;
	int			b_printed;

	b_printed = 0;
	va_start(argp, str);
	while (*str)
	{
		if (*str != '%')		// % should be used as the conversion type
		{
			b_printed++;
			write(1, str, 1);
			str++;
		}
		else
		{
			struct_parse(&str, &argp, &b_printed);
		}
	}
	va_end(argp);

	return (b_printed);
}