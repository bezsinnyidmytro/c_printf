/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 15:18:20 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/13 15:18:21 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ABS(val) (val > 0 ? val : -val)

#include "../includes/ft_printf.h"

static void		set_start_expo(int *expo, long double val)
{
	*expo = 0;
	if ((val > 0 && val < 1.0) || (val < 0 && val > -1.0))
		*expo = -1;
	else if ((val > 0 && val >= 10.0) || (val > 0 && val <= -10.0))
		*expo = 1;
}

static void		get_expo(int *expo, long double *val)
{
	set_start_expo(expo, *val);
	if (*val > 0 && *val < 1.0)
	{
		while ((*val = *val * 10) < 1.0)
			(*expo)--;
	}
	else if (*val > 0 && *val > 1.0)
	{
		while ((*val = *val / 10) > 10)
			(*expo)++;
	}
	else if (*val < 0 && *val > -1.0)
	{
		while ((*val = *val * 10) > -1.0)
			(*expo)--;
	}
	else if (*val < 0 && *val < -1.0)
	{
		while ((*val = *val / 10) < -10)
			(*expo)++;
	}
}

char			*expo_to_str(int expo)
{
	char		*res;

	res = ft_uitoa_base(ABS(expo), 10);
	if ((expo >= 0 && expo < 10) || (expo <= 0 && expo > -10))
		res = ft_dstrjoin("0", res, 0, 1);
	if (expo >= 0)
		res = ft_dstrjoin("+", res, 0, 1);
	else
		res = ft_dstrjoin("-", res, 0, 1);
	res = ft_dstrjoin("e", res, 0, 1);
	return (res);
}

char			*ft_etoa(long double val, int prec)
{
	int			expo;
	char		*res;
	char		*str_expo;
	int			mult_flag;

	mult_flag = 0;
	if ((val > 0 && val < 10) || (val < 0 && val > -10))
		mult_flag = 1;
	if (prec == -1)
		prec = 6;
	get_expo(&expo, &val);
	val = mult_flag ? val * 10 : val;
	res = ft_ftoa(val, prec);
	str_expo = expo_to_str(expo);
	res = ft_dstrjoin(res, str_expo, 1, 1);
	return (res);
}
