/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:22:49 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:55:37 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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

char		*ft_strndup(const char *s1, unsigned int n)
{
	char				*str_new;
	unsigned int		i;

	if (!s1)
		return (NULL);
	i = 0;
	str_new = ft_strnew(n);
	if (!str_new)
		return (NULL);
	while (s1[i] && i < n)
	{
		str_new[i] = s1[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
