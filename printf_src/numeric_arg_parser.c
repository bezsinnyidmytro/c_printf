/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_arg_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:04:12 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 19:04:14 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	udef_size_parse(t_pfarg *arg)
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

size_t			u_size_parse(t_pfarg *arg)
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

static size_t	sdef_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->c_type == 'd' || arg->c_type == 'i')
		parsed_arg = va_arg(*(arg->argp), int);
	else if (arg->c_type == 'D')
		parsed_arg = va_arg(*(arg->argp), long int);
	return (parsed_arg);
}

size_t			s_size_parse(t_pfarg *arg)
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
