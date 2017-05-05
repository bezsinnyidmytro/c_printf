/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 14:54:25 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/04/30 14:54:26 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// FT_STRNEW
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

char	*ft_strnew(size_t size)
{
	return (char *)ft_memalloc(size + 1);
}

// FT_ITOA
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

// // FT_UITOA
// static void		ft_uitoa_pos(size_t n, int size, char **str)
// {
// 	while (--size >= 0)
// 	{
// 		(*str)[size] = (char)(n % 10 + '0');
// 		n = n / 10;
// 	}
// }

// static int		ft_unbrlen(size_t n)
// {
// 	int		len;

// 	len = 0;
// 	while (n / 10 != 0)
// 	{
// 		len++;
// 		n = n / 10;
// 	}
// 	len++;
// 	return (len);
// }

// char			*ft_uitoa(size_t n)
// {
// 	int		size;
// 	char	*str;

// 	size = ft_unbrlen(n);
// 	str = ft_strnew(size);
// 	if (!str)
// 		return (char *)(NULL);
// 	ft_uitoa_pos(n, size, &str);
// 	return (str);
// }

// FT_STRCHR
char	*ft_strchr(const char *s, int c)
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

// FT_STRLEN
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

// FT_STRDUP
char	*ft_strdup(const char *s1)
{
	unsigned long int	size;
	char				*str_new;
	int					i;

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

// FT_PUTSTR
void	ft_putstr(char const *str)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

// FT_PUTCHAR
void	ft_putchar(char ch)
{
	write(1, &ch, 1);
}

// FT_STRJOIN
char	*ft_strjoin(char const *s1, char const *s2)
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
	return (str_new);
}

// FT_STRCAT
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

// FT_STRCAPITALIZER
void	ft_strcap(char *str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 32;
		str++;
	}
}
