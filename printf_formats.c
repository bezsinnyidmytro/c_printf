#include "ft_printf.h"

void	prec_format(t_pfarg *arg, char **end_content)
{
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;

	c_len = ft_strlen(arg->cnt);

	// sS
	if (arg->prec < c_len && arg->prec != -1 && (arg->c_type == 's' || arg->c_type == 'S'))
		(*end_content)[arg->prec] = '\0';

	// diD oO xX uU p prec
	c_len = (arg->cnt[0] == '-') ? c_len - 1 : c_len;
	p_len = 0;
	if (arg->prec > c_len && arg->c_type != 's' && arg->c_type != 'S')
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		if (*end_content[0] == '-')
		{
			tmp[0] = '-';
			*end_content[0] = '0';
			i++;
		}
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		*end_content = ft_strjoin(tmp, *end_content);
		free(tmp);
	}
}

static int	is_zpad_c(char ch)
{
	if (ft_strchr("diDoOuUxXp", ch))
		return (0);
	return (1);
}

void	zero_minus_format(t_pfarg *arg, char **end_content)
{
	int		z_flag;
	int		c_len;
	int		i;
	char	*tmp;

	// diD oO xX uU % sS 
	c_len = ft_strlen(*end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		// SIMILAR to oO xX uU % str char 
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		*end_content = ft_strjoin(*end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		// SIMILAR to oO xX uU % str
		z_flag = ((arg->fmt_flags & 8) == 8 && (arg->prec == -1 || is_zpad_c(arg->c_type))) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		
		if (z_flag && (arg->c_type == 'p' || ((arg->c_type == 'x' || arg->c_type == 'X') && (arg->fmt_flags & 16) == 16)))
			(*end_content)[1] = '0';

		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';

		if (z_flag && ft_strchr(" -+", (*end_content)[0]) && ft_strchr("diD", arg->c_type))
		{
			tmp[0] = (*end_content)[0];
			(*end_content)[0] = '0';
		}

		*end_content = ft_strjoin(tmp, *end_content);

		if (z_flag && (arg->c_type == 'p' || ((arg->c_type == 'x' || arg->c_type == 'X') && (arg->fmt_flags & 16) == 16)))
			(*end_content)[1] = 'x';

		free(tmp);
	}
}


























