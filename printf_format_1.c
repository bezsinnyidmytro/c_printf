#include "ft_printf.h"
#include <string.h>

void	p_format(char **cnt, int flag_mask, int width, int prec)
{
	// Assumed that content stores str of positive value
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(*cnt);

	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';
	else if (*cnt[0] == '0')
		flag_mask = (flag_mask & 15);

	end_content = ft_strdup(*cnt);

	// Precision parse
	if (prec > c_len)
	{
		p_len = prec - c_len;
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
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8 && prec == -1) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		if (z_flag)
			end_content[1] = '0';
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		if (z_flag)
			end_content[1] = 'x';
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
}

void	cC_format(char **cnt, int flag_mask, int width, int prec, size_t *cnt_len, int *is_zero_char)
{
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	c_len = ft_strlen(*cnt);
	if (*cnt[0] == '\0')
	{
		width--;
		*cnt_len += 1;
		*is_zero_char = 1;
	}

	end_content = ft_strdup(*cnt);
	
	int		z_flag;

	// Precision parse
	if (prec == -1)
		prec = -1;

	c_len = ft_strlen(end_content);
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
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
		if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		{
			tmp[++i] = end_content[0];
			end_content[0] = '0';
		}
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	arg->cnt = end_content;
}

void	percent_format(char **cnt, int flag_mask, int width, int prec)
{
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	end_content = ft_strdup(*cnt);

	// -, 0 flag parse
	int		z_flag;

	// Precision parse
	if (prec == -1)
		prec = -1;

	c_len = ft_strlen(end_content);
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		{
			tmp[++i] = end_content[0];
			end_content[0] = '0';
		}
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
}

void	diD_format(char **cnt, int flag_mask, int width, int prec)
{
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(*cnt);
	c_len = (*cnt[0] == '-') ? c_len - 1 : c_len;
	
	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';

	end_content = ft_strdup(*cnt);
	// Precision parse
	if (prec > c_len)
	{
		p_len = prec - c_len;
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
	if ((flag_mask & 1) == 1 && end_content[0] != '-')
		end_content = ft_strjoin("+", end_content);
	else if ((flag_mask & 2) == 2 && end_content[0] != '-')
		end_content = ft_strjoin(" ", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8 && prec == -1) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		if (z_flag && (end_content[0] == ' ' || end_content[0] == '+' || end_content[0] == '-'))
		{
			tmp[0] = end_content[0];
			end_content[0] = '0';
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
}

void	oO_format(char **cnt, int flag_mask, int width, int prec)
{
	// Assumed that content stores str of positive value
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(*cnt);

	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';

	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
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
	else if (end_content[0] != '0' && (flag_mask & 16) == 16)	// # parse
		end_content = ft_strjoin("0", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8 && prec == -1) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
}

void	xX_format(char **cnt, int flag_mask, int width, int prec, char c_type)
{
	// Assumed that content stores str of positive value
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(*cnt);

	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';
	else if (*cnt[0] == '0')
		flag_mask = (flag_mask & 15);

	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
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
	if ((flag_mask & 16) == 16 && (prec != 0 || *cnt[0] != '\0'))
		end_content = ft_strjoin("0x", end_content);

	// -, 0 flag parse
	int		z_flag;

	c_len = ft_strlen(end_content);
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8 && prec == -1) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		if (z_flag && (flag_mask & 16) == 16)
			end_content[1] = '0';
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);
		if (z_flag && (flag_mask & 16) == 16)
			end_content[1] = 'x';
		free(tmp);
	}
	free(*cnt);
	if (c_type == 'X')
		ft_strcap(end_content);
	*cnt = end_content;
}

void	uU_format(char **cnt, int flag_mask, int width, int prec)
{
	// Assumed that content stores str of positive value
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	p_len = 0;
	c_len = ft_strlen(*cnt);

	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';

	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
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
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = ' ';
		end_content = ft_strjoin(end_content, tmp);
		free(tmp);
	}
	else if (width > c_len)
	{
		z_flag = ((flag_mask & 8) == 8 && prec == -1) ? 1 : 0;
		tmp = ft_strnew(width - c_len);
		i = -1;
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);	
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
}
