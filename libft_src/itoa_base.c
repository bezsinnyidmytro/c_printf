/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:56:00 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:56:08 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	parse(size_t n, int b, char *res, int *i)
{
	char	*base;

	base = "0123456789abcdef";
	if ((unsigned int)b <= n)
		parse(n / b, b, res, i);
	res[(*i)++] = *(base + n % b);
}

char		*ft_uitoa_base(size_t val, int base)
{
	int		i;
	char	*res;

	if (base < 2 || 16 < base || !(res = ft_strnew(65)))
		return (NULL);
	i = 0;
	parse(val, base, res, &i);
	return (res);
}
