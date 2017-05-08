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

#include "ft_printf.h"

int				ft_printf(char *str, ...)
{
	va_list		argp;
	int			b_printed;

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
	return (b_printed);
}
