/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:23:45 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:56:24 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char				*ft_strchr(const char *s, int c)
{
	char	*pointer;

	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	pointer = (char *)s;
	while (*pointer)
	{
		if (*pointer == c)
			return (pointer);
		pointer++;
	}
	return (NULL);
}

unsigned long int	ft_strlen(const char *str)
{
	unsigned long int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

static void			ft_fdputstr(char const *str, int fd)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_fdputchar(*str, fd);
		str++;
	}
}

void				ft_pfputstr(t_pfarg *arg, int fd)
{
	char	ch;

	ch = '\0';
	if (arg->is_zero_char == 1 && (arg->fmt_flags & 4) == 4)
		write(fd, &ch, 1);
	ft_fdputstr(arg->cnt, fd);
	if (arg->is_zero_char == 1 && (arg->fmt_flags | 4) != arg->fmt_flags)
		write(fd, &ch, 1);
}

void				ft_swap_chars(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
