#include "ft_printf.h"
#include <string.h>

void	p_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	char	*end_content;

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);

	// Precision parse
	prec_format(arg, &end_content);

	end_content = ft_strjoin("0x", end_content);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	arg->cnt = end_content;
}

void	cC_format(t_pfarg *arg)
{
	int		c_len;
	char	*end_content;

	c_len = ft_strlen(arg->cnt);
	if (arg->cnt[0] == '\0')
	{
		arg->width--;
		arg->cnt_len += 1;
		arg->is_zero_char = 1;
	}

	end_content = ft_strdup(arg->cnt);
	
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	arg->cnt = end_content;
}

void	str_format(t_pfarg *arg)
{
	char	*end_content;

	end_content = ft_strdup(arg->cnt);

	// Precision parse
	prec_format(arg, &end_content);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);
	arg->cnt = end_content;
}

void	percent_format(t_pfarg *arg)
{
	char	*end_content;

	end_content = ft_strdup(arg->cnt);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	arg->cnt = end_content;
}

void	diD_format(t_pfarg *arg)
{
	char	*end_content;
	
	// SIMILAR to oO xX uU p can add some usefull free on arg->cnt
	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);
	
	// Precision parse
	// SIMILAR to oO xX uU p
	prec_format(arg, &end_content);

	// Space, + flags parse
	if ((arg->fmt_flags & 1) == 1 && end_content[0] != '-')
		end_content = ft_strjoin("+", end_content);
	else if ((arg->fmt_flags & 2) == 2 && end_content[0] != '-')
		end_content = ft_strjoin(" ", end_content);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	arg->cnt = end_content;
}

void	oO_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	char	*end_content;

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);

	// Precision parse
	prec_format(arg, &end_content);
	
	// # parse
	if (end_content[0] != '0' && (arg->fmt_flags & 16) == 16)
		end_content = ft_strjoin("0", end_content);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	arg->cnt = end_content;
}

void	xX_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value

	char	*end_content;

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	else if (arg->cnt[0] == '0')
		arg->fmt_flags = (arg->fmt_flags & 15);
	end_content = ft_strdup(arg->cnt);

	// prec parse
	prec_format(arg, &end_content);

	// # parse
	if ((arg->fmt_flags & 16) == 16 && (arg->prec != 0 || arg->cnt[0] != '\0'))
		end_content = ft_strjoin("0x", end_content);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);

	free(arg->cnt);
	if (arg->c_type == 'X')
		ft_strcap(end_content);
	arg->cnt = end_content;
}

void	uU_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	char	*end_content;

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);

	// prec parse
	prec_format(arg, &end_content);

	// -, 0 flag parse
	zero_minus_format(arg, &end_content);
	free(arg->cnt);
	arg->cnt = end_content;
}
