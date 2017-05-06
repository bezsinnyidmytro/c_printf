#include "ft_printf.h"
#include <string.h>

void	p_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(arg->cnt);

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);

	// Precision parse
	if (arg->prec > c_len)
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	end_content = ft_strjoin("0x", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8 && arg->prec == -1) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		if (z_flag)
			end_content[1] = '0';
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		if (z_flag)
			end_content[1] = 'x';
		free(tmp);
	}
	free(arg->cnt);
	arg->cnt = end_content;
}

void	cC_format(t_pfarg *arg)
{
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	c_len = ft_strlen(arg->cnt);
	if (arg->cnt[0] == '\0')
	{
		arg->width--;
		arg->cnt_len += 1;
		arg->is_zero_char = 1;
	}

	end_content = ft_strdup(arg->cnt);
	
	int		z_flag;

	// Precision parse
	if (arg->prec == -1)
		arg->prec = -1;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(arg->cnt);
	arg->cnt = end_content;
}

void	str_format(t_pfarg *arg)
{
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(arg->cnt);
	end_content = ft_strdup(arg->cnt);

	// Precision parse
	if (arg->prec < c_len)
		end_content[arg->prec] = '\0';

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	arg->cnt = end_content;
}

void	percent_format(t_pfarg *arg)
{
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	end_content = ft_strdup(arg->cnt);

	// -, 0 flag parse
	int		z_flag;

	// Precision parse
	if (arg->prec == -1)
		arg->prec = -1;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(arg->cnt);
	arg->cnt = end_content;
}

void	diD_format(t_pfarg *arg)
{
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(arg->cnt);
	c_len = (arg->cnt[0] == '-') ? c_len - 1 : c_len;
	
	// SIMILAR to oO xX uU p can add some usefull free on arg->cnt
	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);
	
	// Precision parse
	// SIMILAR to oO xX uU p
	if (arg->prec > c_len)
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		if (end_content[0] == '-')
		{
			tmp[0] = '-';
			end_content[0] = '0';
			i++;
		}
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	// Space, + flags parse
	if ((arg->fmt_flags & 1) == 1 && end_content[0] != '-')
		end_content = ft_strjoin("+", end_content);
	else if ((arg->fmt_flags & 2) == 2 && end_content[0] != '-')
		end_content = ft_strjoin(" ", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		// SIMILAR to oO xX uU % str char 
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		// SIMILAR to oO xX uU % str
		z_flag = ((arg->fmt_flags & 8) == 8 && arg->prec == -1) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		if (z_flag && (end_content[0] == ' ' || end_content[0] == '+' || end_content[0] == '-'))
		{
			tmp[0] = end_content[0];
			end_content[0] = '0';
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(arg->cnt);
	arg->cnt = end_content;
}

void	oO_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(arg->cnt);

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);

	// Precision parse
	if (arg->prec > c_len)
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	else if (end_content[0] != '0' && (arg->fmt_flags & 16) == 16)	// # parse
		end_content = ft_strjoin("0", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8 && arg->prec == -1) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(arg->cnt);
	arg->cnt = end_content;
}

void	xX_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(arg->cnt);

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	else if (arg->cnt[0] == '0')
		arg->fmt_flags = (arg->fmt_flags & 15);
	end_content = ft_strdup(arg->cnt);

	if (arg->prec > c_len)
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	// # parse
	if ((arg->fmt_flags & 16) == 16 && (arg->prec != 0 || arg->cnt[0] != '\0'))
		end_content = ft_strjoin("0x", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8 && arg->prec == -1) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		if (z_flag && (arg->fmt_flags & 16) == 16)
			end_content[1] = '0';
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		if (z_flag && (arg->fmt_flags & 16) == 16)
			end_content[1] = 'x';
		free(tmp);
	}
	free(arg->cnt);
	if (arg->c_type == 'X')
		ft_strcap(end_content);
	arg->cnt = end_content;
}

void	uU_format(t_pfarg *arg)
{
	// Assumed that content stores str of positive value
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(arg->cnt);

	if (arg->cnt[0] == '0' && arg->prec == 0)
		arg->cnt[0] = '\0';
	end_content = ft_strdup(arg->cnt);

	if (arg->prec > c_len)
	{
		p_len = arg->prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((arg->fmt_flags & 4) == 4 && arg->width > c_len)
	{
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (arg->width > c_len)
	{
		z_flag = ((arg->fmt_flags & 8) == 8 && arg->prec == -1) ? 1 : 0;
		tmp = ft_strnew(arg->width - c_len);
		i = -1;
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);	
		free(tmp);
	}
	free(arg->cnt);
	arg->cnt = end_content;
}
