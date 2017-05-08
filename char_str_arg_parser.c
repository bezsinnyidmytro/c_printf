/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_str_arg_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:03:59 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 19:04:03 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*char_parse(t_pfarg *arg, int udef_flag)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * 2);
	res[1] = 0;
	if (!udef_flag)
		res[0] = (unsigned char)va_arg(*(arg->argp), int);
	else
		res[0] = arg->c_type;
	return (res);
}

static char	*wc_to_str(int ch)
{
	char	*res;

	res = ft_strnew(2);
	res[1] = '\0';
	res[0] = ch;
	return (res);
}

static void	insert_wchar(char **res, int width, size_t ch)
{
	char	*tmp;

	tmp = ft_strnew(0);
	if (width == 1)
		tmp = ft_strjoin(tmp, wc_to_str(ch));
	else
	{
		if (width == 2)
			tmp = ft_strjoin(tmp, wc_to_str((ch >> 6) + 192));
		else if (width == 3)
		{
			tmp = ft_strjoin(tmp, wc_to_str((ch >> 12) + 224));
			tmp = ft_strjoin(tmp, wc_to_str(((ch >> 6) & 63) + 128));
		}
		else if (width == 4)
		{
			tmp = ft_strjoin(tmp, wc_to_str((ch >> 18) + 240));
			tmp = ft_strjoin(tmp, wc_to_str(((ch >> 12) & 63) + 192));
			tmp = ft_strjoin(tmp, wc_to_str(((ch >> 6) & 63) + 128));
		}
		tmp = ft_strjoin(tmp, wc_to_str((ch & 63) + 128));
	}
	*res = ft_strjoin(*res, tmp);
	free(tmp);
}

static int	get_wchar_width(wchar_t *s)
{
	int		width;

	width = 0;
	if (*s <= 0x7F)
		width = 1;
	else if (*s <= 0x7FF)
		width = 2;
	else if (*s <= 0xFFFF)
		width = 3;
	else if (*s <= 0x1FFFFF)
		width = 4;
	return (width);
}

char		*string_parse(t_pfarg *arg)
{
	char	*res;
	wchar_t	*s;
	int		c_width;
	int		sum_width;
	int		is_first;

	if (arg->size_flag != 3)
		return (ft_strdup(va_arg(*(arg->argp), char *)));
	sum_width = 0;
	is_first = 1;
	res = ft_strnew(0);
	s = va_arg(*(arg->argp), wchar_t *);
	if (!s)
		return (ft_strdup("(null)"));
	while (*s != '\0' && (arg->prec == -1 || (arg->prec != -1 &&
		sum_width < arg->prec)))
	{
		sum_width += (c_width = get_wchar_width(s));
		if (is_first || (arg->prec != -1 && sum_width <= arg->prec) ||
			arg->prec == -1)
			insert_wchar(&res, c_width, *s);
		is_first = 0;
		s++;
	}
	return (res);
}
