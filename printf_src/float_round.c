/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_round.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 12:36:45 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/13 12:36:46 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static long double	ft_round_up(long double t)
{
	long double d;

	d = (intmax_t)t;
	if (t <= d)
		return (d);
	return (d + 1);
}

static long double	ft_round_down(long double t)
{
	long double d;

	d = (intmax_t)t;
	if (t >= d)
		return (d);
	return (d - 1);
}

long double			ft_round_fraction(long double t)
{
	long double up;
	long double down;

	up = ft_round_up(t);
	down = ft_round_down(t);
	if (t - down == 0.5 && !((intmax_t)down ^ 1))
		return (down);
	else if (up - t == 0.5)
		return (up);
	if (t - down >= 0.5)
		return (up);
	else
		return (down);
}
