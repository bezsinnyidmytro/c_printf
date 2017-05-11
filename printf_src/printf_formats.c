/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_formats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:57:55 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:57:57 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*pre_format(t_pfarg *arg)
{
	if (arg->cnt[0] == '0' && arg->prec == 0 &&
		ft_strchr("pdiDoOuUxX", arg->c_type))
		arg->cnt[0] = '\0';
	else if (arg->cnt[0] == '0' && (arg->c_type == 'x' || arg->c_type == 'X'))
		arg->fmt_flags = (arg->fmt_flags & 15);
	else if (arg->cnt[0] == '\0' && (arg->c_type == 'c' || arg->c_type == 'C'))
	{
		arg->width--;
		arg->cnt_len += 1;
		arg->is_zero_char = 1;
	}
	return (ft_strdup(arg->cnt));
}

static void	prec_format_str(t_pfarg *arg, int c_len, char **end_content)
{
	char	*tmp;

	if (arg->prec < c_len && arg->prec != -1 && (arg->c_type == 's' ||
		arg->c_type == 'S'))
	{
		tmp = ft_strndup((*end_content), arg->prec);
		free(*end_content);
		(*end_content) = tmp;
	}
}

void		prec_format(t_pfarg *arg, char **end_content)
{
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;

	c_len = ft_strlen(arg->cnt);
	prec_format_str(arg, c_len, end_content);
	c_len = (arg->cnt[0] == '-') ? c_len - 1 : c_len;
	p_len = 0;
	if (arg->prec > c_len && arg->c_type != 's' && arg->c_type != 'S')
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		i = -1;
		if ((*end_content)[0] == '-')
		{
			tmp[0] = '-';
			*end_content[0] = '0';
			i++;
		}
		while (++i < p_len)
			tmp[i] = '0';
		*end_content = ft_dstrjoin(tmp, *end_content, 0, 1);
		free(tmp);
	}
}

void		signed_sign_format(t_pfarg *arg, char **end_content)
{
	if ((arg->fmt_flags & 1) == 1 && (*end_content)[0] != '-')
		*end_content = ft_dstrjoin("+", *end_content, 0, 1);
	else if ((arg->fmt_flags & 2) == 2 && (*end_content)[0] != '-')
		*end_content = ft_dstrjoin(" ", *end_content, 0, 1);
}

void		hash_format(t_pfarg *arg, char **end_content)
{
	if (arg->c_type == 'p')
		*end_content = ft_dstrjoin("0x", *end_content, 0, 1);
	else if ((arg->c_type == 'o' || arg->c_type == 'O') &&
		(*end_content)[0] != '0' && (arg->fmt_flags & 16) == 16)
		*end_content = ft_dstrjoin("0", *end_content, 0, 1);
	else if ((arg->c_type == 'x' || arg->c_type == 'X') &&
		(arg->fmt_flags & 16) == 16 && (arg->prec != 0 || arg->cnt[0] != '\0'))
		*end_content = ft_dstrjoin("0x", *end_content, 0, 1);
}
