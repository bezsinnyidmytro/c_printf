/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_struct_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:57:03 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:57:07 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		udef_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->c_type == 'o' || arg->c_type == 'O')
		parsed_arg = va_arg(*(arg->argp), unsigned int);
	else if (arg->c_type == 'x' || arg->c_type == 'X')
		parsed_arg = va_arg(*(arg->argp), unsigned int);
	else if (arg->c_type == 'u')
		parsed_arg = va_arg(*(arg->argp), unsigned int);
	else if (arg->c_type == 'U')
		parsed_arg = va_arg(*(arg->argp), unsigned long int);
	return (parsed_arg);
}

size_t		u_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->size_flag == 1)
		parsed_arg = (unsigned char)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 2)
		parsed_arg = (unsigned short)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 3)
		parsed_arg = va_arg(*(arg->argp), unsigned long int);
	else if (arg->size_flag == 4)
		parsed_arg = va_arg(*(arg->argp), unsigned long long int);
	else if (arg->size_flag == 5)
		parsed_arg = va_arg(*(arg->argp), uintmax_t);
	else if (arg->size_flag == 6)
		parsed_arg = va_arg(*(arg->argp), size_t);
	else
		parsed_arg = udef_size_parse(arg);
	return (parsed_arg);
}

size_t		sdef_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->c_type == 'd' || arg->c_type == 'i')
		parsed_arg = va_arg(*(arg->argp), int);
	else if (arg->c_type == 'D')
		parsed_arg = va_arg(*(arg->argp), long int);
	return (parsed_arg);
}

size_t		s_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->size_flag == 1)
		parsed_arg = (char)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 2)
		parsed_arg = (short)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 3)
		parsed_arg = va_arg(*(arg->argp), long int);
	else if (arg->size_flag == 4)
		parsed_arg = va_arg(*(arg->argp), long long int);
	else if (arg->size_flag == 5)
		parsed_arg = va_arg(*(arg->argp), intmax_t);
	else if (arg->size_flag == 6)
		parsed_arg = va_arg(*(arg->argp), ssize_t);
	else
		parsed_arg = sdef_size_parse(arg);
	return (parsed_arg);
}

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

char		*wc_to_str(int ch)
{
	char	*res;

	res = ft_strnew(2);
	res[1] = '\0';
	res[0] = ch;
	return (res);
}

void		insert_wchar(char **res, int width, size_t ch)
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

int			get_wchar_width(wchar_t *s)
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

void		parse_arg(t_pfarg *arg)
{
	if (arg->c_type == 'i' || arg->c_type == 'd' || arg->c_type == 'D')
		arg->cnt = ft_itoa(s_size_parse(arg));
	else if (arg->c_type == 'o' || arg->c_type == 'O')
		arg->cnt = ft_uitoa_base(u_size_parse(arg), 8);
	else if (arg->c_type == 'x' || arg->c_type == 'X')
		arg->cnt = ft_uitoa_base(u_size_parse(arg), 16);
	else if (arg->c_type == 'u' || arg->c_type == 'U')
		arg->cnt = ft_uitoa_base(u_size_parse(arg), 10);
	else if (arg->c_type == 'c' || arg->c_type == 'C')
		arg->cnt = char_parse(arg, 0);
	else if (arg->c_type == 's' || arg->c_type == 'S')
	{
		arg->cnt = string_parse(arg);
		arg->cnt = (arg->cnt == NULL) ? ft_strdup("(null)") : arg->cnt;
	}
	else if (arg->c_type == '%')
		arg->cnt = ft_strdup("%");
	else if (arg->c_type == 'p')
		arg->cnt = ft_uitoa_base((uintmax_t)va_arg(*(arg->argp), void *), 16);
	else if (arg->c_type != -1)
		arg->cnt = char_parse(arg, 1);
}

void		h_size_process(char **str, t_pfarg *arg, int *cur_size)
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

void		parse_conv(char **str, t_pfarg *arg)
{
	if (**str != '\0')
	{
		arg->c_type = **str;
		if (arg->c_type == 'U' || arg->c_type == 'D' || arg->c_type == 'O')
			arg->size_flag = (arg->size_flag > 3) ? arg->size_flag : 3;
		if (arg->c_type == 'C' || arg->c_type == 'S')
			arg->size_flag = 3;
		*str = *str + 1;
	}
}

void		free_structure(t_pfarg *arg)
{
	free(arg->cnt);
	arg->cnt = NULL;
	arg->argp = NULL;
	free(arg);
	arg = NULL;
}

void		struct_init(t_pfarg *arg, va_list *ap)
{
	arg->cnt = NULL;
	arg->fmt_flags = 0;
	arg->width = 0;
	arg->prec = -1;
	arg->size_flag = 0;
	arg->c_type = -1;
	arg->is_zero_char = 0;
	arg->cnt_len = 0;
	arg->argp = ap;
}

void		struct_parse(char **str, va_list *ap, int *b_printed)
{
	t_pfarg		*arg;

	arg = (t_pfarg*)malloc(sizeof(t_pfarg));
	*str = *str + 1;
	if (arg)
	{
		struct_init(arg, ap);
		while (**str && (parse_fmt_flags(str, arg) ||
			parse_width(str, arg) || parse_prec(str, arg, -1) ||
			parse_size_flags(str, arg)))
		{
		}
		parse_conv(str, arg);
		parse_arg(arg);
		if (arg->cnt)
		{
			common_format(arg);
			ft_pfputstr(arg);
			*b_printed += ft_strlen(arg->cnt) + arg->cnt_len;
		}
		free_structure(arg);
	}
}
