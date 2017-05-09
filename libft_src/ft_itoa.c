/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 14:54:25 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:58:14 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		ft_itoa_pos(ssize_t n, int size, char **str)
{
	while (--size >= 0)
	{
		(*str)[size] = (char)(n % 10 + '0');
		n = n / 10;
	}
}

static void		ft_itoa_neg(ssize_t n, int size, char **str)
{
	(*str)[0] = '-';
	while (--size >= 1)
	{
		(*str)[size] = (char)(-(n % 10) + '0');
		n = n / 10;
	}
}

static int		ft_nbrlen(ssize_t n)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	len++;
	return (len);
}

char			*ft_itoa(ssize_t n)
{
	int		size;
	char	*str;

	size = ft_nbrlen(n);
	str = ft_strnew(size);
	if (!str)
		return (char *)(NULL);
	if (n < 0)
		ft_itoa_neg(n, size, &str);
	else
		ft_itoa_pos(n, size, &str);
	return (str);
}
