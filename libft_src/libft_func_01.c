/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 15:23:34 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:58:55 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar(char ch)
{
	write(1, &ch, 1);
}

char	*ft_dstrjoin(char *s1, char *s2, int ff1, int ff2)
{
	size_t	len;
	char	*str_new;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str_new = ft_strnew(len);
	if (!str_new)
		return (NULL);
	str_new = ft_strcat(str_new, s1);
	str_new = ft_strcat(str_new, s2);
	if (ff1)
		free(s1);
	if (ff2)
		free(s2);
	return (str_new);
}

char	*ft_strcat(char *s1, const char *s2)
{
	unsigned long int	i;
	unsigned long int	j;

	j = ft_strlen(s1);
	i = 0;
	while (s2[i] != '\0')
	{
		s1[j + i] = s2[i];
		i++;
	}
	s1[j + i] = '\0';
	return (s1);
}

void	ft_strcap(char *str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 32;
		str++;
	}
}

char	*ft_strdup(const char *s1)
{
	unsigned long int	size;
	char				*str_new;
	int					i;

	if (!s1)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	str_new = ft_strnew(size);
	if (!str_new)
		return (NULL);
	while (s1[i])
	{
		str_new[i] = s1[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
