/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 12:39:30 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/13 12:39:31 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		float_res_fill(int *sizes, char **tmp, char **res)
{
	int			i;
	int			j;

	j = -1;
	while (++j < sizes[0] - sizes[1] && sizes[2] > sizes[1])
	{
		if (j == sizes[0] - sizes[2] - 1)
		{
			(*res)[j] = '.';
			j++;
		}
		(*res)[j] = '0';
	}
	i = -1;
	j--;
	while (++i < sizes[1] && (++j) >= 0)
	{
		if (j == sizes[0] - sizes[2] - 1 && sizes[2] < sizes[1])
		{
			(*res)[j] = '.';
			j++;
		}
		(*res)[j] = (*tmp)[i];
	}
}

int				*parse_values(int a, int b, int c)
{
	int			*res;

	res = (int *)malloc(sizeof(int) * 3);
	res[0] = a;
	res[1] = b;
	res[2] = c;
	return (res);
}

static void		float_put_dot(char **no_dot, int prec)
{
	char		*res;
	int			no_dot_len;
	int			res_len;
	char		*tmp;

	tmp = *no_dot;
	if (tmp[0] == '-')
		tmp++;
	no_dot_len = ft_strlen(tmp);
	res_len = (prec >= no_dot_len) ? prec + 2 : ft_strlen(tmp) + 1;
	res = ft_strnew(res_len + 1);
	float_res_fill(parse_values(res_len, no_dot_len, prec), &tmp, &res);
	if (prec == no_dot_len && (*no_dot)[0] == '-')
		res = ft_dstrjoin("-0.", res, 0, 1);
	else if ((*no_dot)[0] == '-')
		res = ft_dstrjoin("-", res, 0, 1);
	else if (prec == no_dot_len)
		res = ft_dstrjoin("0.", res, 0, 1);
	free(*no_dot);
	*no_dot = res;
}

char			*ft_ftoa(long double val, int prec)
{
	long int	int_val;
	char		*res;
	int			i;

	if (prec == -1)
		prec = 6;
	i = prec + 1;
	while (--i)
		val = val * 10;
	val = ft_round_fraction(val);
	int_val = val;
	res = ft_itoa(int_val);
	float_put_dot(&res, prec);
	return (res);
}

char			*fe_dispatcher(t_pfarg *arg)
{
	if (arg->c_type == 'f' || arg->c_type == 'F')
		return (ft_ftoa(va_arg(*(arg->argp), double), arg->prec));
	else if (arg->c_type == 'e' || arg->c_type == 'E')
		return (ft_etoa(va_arg(*(arg->argp), double), arg->prec));
	return (NULL);
}
