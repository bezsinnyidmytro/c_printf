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

static int		ft_strstr_s(const char *big, const char *little)
{
	int i;
	int l_len;

	l_len = ft_strlen(little);
	i = 0;
	while (big[i] != '\0' && i < l_len && big[i] == little[i])
		i++;
	if (i == l_len)
		return (1);
	return (0);
}

static void		check_for_fd(int *fd, const char **str, va_list *ap)
{
	if (ft_strstr_s((*str), "{fileoutput}"))
	{
		*fd = va_arg(*ap, int);
		(*str) += 12;
	}
}

int				ft_printf(const char *str, ...)
{
	va_list		argp;
	size_t		b_printed;
	int			fd;

	va_start(argp, str);
	fd = 1;
	check_for_fd(&fd, &str, &argp);
	b_printed = 0;
	while (*str)
	{
		if (*str != '%')
		{
			b_printed++;
			write(fd, str, 1);
			str++;
		}
		else
			struct_parse(&str, &argp, &b_printed, fd);
	}
	va_end(argp);
	if (b_printed > 2147483647)
		return (-1);
	return (b_printed);
}
