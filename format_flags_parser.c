/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_flags_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:04:23 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 19:04:24 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	h_size_process(char **str, t_pfarg *arg, int *cur_size)
{
	if (**str == 'h' && *(*str + 1) == 'h')
	{
		*cur_size = (*cur_size > 1) ? *cur_size : 1;
		*str = *str + 1;
	}
	else if (**str == 'h' && arg->size_flag == 2)
	{
		*cur_size = 1;
		arg->size_flag = 1;
	}
	else if (**str == 'h')
		*cur_size = (*cur_size > 2) ? *cur_size : 2;
}

int			parse_size_flags(char **str, t_pfarg *arg)
{
	int		cur_size;

	cur_size = 0;
	while (**str != '\0' && ft_strchr("hljz", **str))
	{
		h_size_process(str, arg, &cur_size);
		if (**str == 'l')
			cur_size = (cur_size > 3) ? cur_size : 3;
		if (**str == 'l' && *(*str + 1) == 'l')
			cur_size = (cur_size > 4) ? cur_size : 4;
		if (**str == 'j')
			cur_size = (cur_size > 5) ? cur_size : 5;
		if (**str == 'z')
			cur_size = 6;
		*str = *str + 1;
	}
	if (arg->size_flag < cur_size)
		arg->size_flag = cur_size;
	return ((cur_size > 0) ? 1 : 0);
}

int			parse_prec(char **str, t_pfarg *arg, int prec)
{
	if (**str == '.')
	{
		prec = 0;
		*str = *str + 1;
		if (**str >= '0' && **str <= '9')
		{
			prec = 0;
			while (**str >= '0' && **str <= '9')
			{
				prec = prec * 10 + (**str - '0');
				*str = *str + 1;
			}
		}
		else if (**str == '*')
		{
			prec = va_arg(*(arg->argp), int);
			prec = (prec < 0) ? -1 : prec;
			*str = *str + 1;
		}
		arg->prec = prec;
		return (1);
	}
	return (0);
}

int			parse_width(char **str, t_pfarg *arg)
{
	int		width;

	width = 0;
	while ((**str != '\0' && **str > '0' && **str <= '9') ||
		(**str == '0' && width != 0))
	{
		width = width * 10 + (**str - '0');
		*str = *str + 1;
	}
	if (width > 0 && (arg->width = width))
		return (1);
	if (**str != '\0' && **str == '*')
	{
		arg->width = va_arg(*(arg->argp), int);
		if (arg->width < 0)
		{
			arg->width *= -1;
			arg->fmt_flags = arg->fmt_flags | 4;
		}
		*str = *str + 1;
		return (1);
	}
	return (0);
}

int			parse_fmt_flags(char **str, t_pfarg *arg)
{
	int		is_found;

	is_found = 0;
	while (**str != '\0' && ft_strchr("#0- +", **str))
	{
		is_found = 1;
		if (**str == '#')
			arg->fmt_flags = arg->fmt_flags | 16;
		else if (**str == '0')
			arg->fmt_flags = arg->fmt_flags | 8;
		else if (**str == '-')
			arg->fmt_flags = arg->fmt_flags | 4;
		else if (**str == ' ')
			arg->fmt_flags = arg->fmt_flags | 2;
		else if (**str == '+')
			arg->fmt_flags = arg->fmt_flags | 1;
		*str = *str + 1;
	}
	if ((arg->fmt_flags & 4) == arg->fmt_flags)
		arg->fmt_flags = arg->fmt_flags & 23;
	if ((arg->fmt_flags & 1) == arg->fmt_flags)
		arg->fmt_flags = arg->fmt_flags & 29;
	return (is_found);
}
