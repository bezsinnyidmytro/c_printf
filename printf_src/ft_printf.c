/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:57:16 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:57:18 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_printf(const char *str, ...)
{
	va_list		argp;
	size_t		b_printed;

	b_printed = 0;
	va_start(argp, str);
	while (*str)
	{
		if (*str != '%')
		{
			b_printed++;
			write(1, str, 1);
			str++;
		}
		else
			struct_parse(&str, &argp, &b_printed);
	}
	va_end(argp);
	if (b_printed > 2147483647)
		return (-1);
	return (b_printed);
}
