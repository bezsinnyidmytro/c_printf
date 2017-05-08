/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_minus_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 18:31:56 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 18:31:57 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_zpad_c(char ch)
{
	if (ft_strchr("diDoOuUxXp", ch))
		return (0);
	return (1);
}

static void	left_side(int width, int c_len, char **end_content)
{
	char	*tmp;
	int		i;

	tmp = ft_strnew(width - c_len);
	i = -1;
	while (++i < width - c_len)
		tmp[i] = ' ';
	*end_content = ft_strjoin(*end_content, tmp);
	free(tmp);
}

static void	right_side(t_pfarg *arg, char **end_content, int c_len)
{
	char	*tmp;
	int		z_flag;
	int		i;

	z_flag = ((arg->fmt_flags & 8) == 8 && (arg->prec == -1 ||
		is_zpad_c(arg->c_type))) ? 1 : 0;
	tmp = ft_strnew(arg->width - c_len);
	i = -1;
	if (z_flag && (arg->c_type == 'p' || ((arg->c_type == 'x' ||
		arg->c_type == 'X') && (arg->fmt_flags & 16) == 16)))
		(*end_content)[1] = '0';
	while (++i < arg->width - c_len)
		tmp[i] = z_flag ? '0' : ' ';
	if (z_flag && ft_strchr(" -+", (*end_content)[0]) &&
		ft_strchr("diD", arg->c_type))
	{
		tmp[0] = (*end_content)[0];
		(*end_content)[0] = '0';
	}
	*end_content = ft_strjoin(tmp, *end_content);
	if (z_flag && (arg->c_type == 'p' || ((arg->c_type == 'x' ||
		arg->c_type == 'X') && (arg->fmt_flags & 16) == 16)))
		(*end_content)[1] = 'x';
	free(tmp);
}

void		zero_minus_format(t_pfarg *arg, char **end_content)
{
	int		c_len;

	c_len = ft_strlen(*end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
		left_side(arg->width, c_len, end_content);
	else if (arg->width > c_len)
		right_side(arg, end_content, c_len);
}
