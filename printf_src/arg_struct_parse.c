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

#include "../includes/ft_printf.h"

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
	else if (arg->c_type == 'b')
		arg->cnt = ft_uitoa_base(u_size_parse(arg), 2);
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

void		parse_conv(const char **str, t_pfarg *arg)
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

void		struct_parse(const char **str, va_list *ap, size_t *b_printed)
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
