/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:56:48 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:56:52 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_signed_conv(char ch)
{
	if (ft_strchr("diD", ch))
		return (1);
	return (0);
}

void	common_format(t_pfarg *arg)
{
	char	*end_content;

	end_content = pre_format(arg);
	if (ft_strchr("pdiDoOuUxXsS", arg->c_type))
		prec_format(arg, &end_content);
	if (is_signed_conv(arg->c_type))
		signed_sign_format(arg, &end_content);
	hash_format(arg, &end_content);
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	if (arg->c_type == 'X')
		ft_strcap(end_content);
	arg->cnt = end_content;
}
