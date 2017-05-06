/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:22:49 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/06 15:23:05 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = s;
	while (n--)
	{
		*str = (char)0;
		str++;
	}
}

static void	*ft_memalloc(size_t size)
{
	void	*point;

	point = malloc(size);
	if (!point)
		return (NULL);
	ft_bzero(point, size);
	return (point);
}

char		*ft_strnew(size_t size)
{
	return (char *)ft_memalloc(size + 1);
}
