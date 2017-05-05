#include "ft_printf.h"
#include <string.h>

void	p_format(char **cnt, int flag_mask, int width, int prec)
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

	if (*cnt[0] == '0' && prec == 0)			// why it should be checked here, have no idea but works fine for 42FC
		*cnt[0] = '\0';
	else if (*cnt[0] == '0')					// maybe should use atoi_base here to check if the result is 0
		flag_mask = (flag_mask & 15);
	//c_len = (content[0] == '-') ? c_len - 1 : c_len;
	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		// if (end_content[0] == '-')
		// {
		// 	tmp[0] = '-';
		// 	end_content[0] = '0';
		// 	i++;
		// }
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	//if ((flag_mask & 16) == 16 && prec != 0)	// # parse
	end_content = ft_strjoin("0x", end_content);	// here must be check for 0x || 0X

	// Space, + flags parse
	// if ((flag_mask & 1) == 1 && end_content[0] != '-')
	// 	end_content = ft_strjoin("+", end_content);
	// else if ((flag_mask & 2) == 2 && end_content[0] != '-')
	// 	end_content = ft_strjoin(" ", end_content);

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
		// if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		// {
		// 	tmp[++i] = end_content[0];
		// 	end_content[0] = '0';
		// }
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
		end_content = ft_strjoin(tmp, end_content);
		//if (z_flag && (flag_mask & 16) == 16)
		if (z_flag)
			end_content[1] = 'x';						// or X
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
	//printf("Start %s end.\n", end_content);
}

void	cC_format(char **cnt, int flag_mask, int width, int prec, size_t *cnt_len, int *is_zero_char)
{
	// Precision parse
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

	c_len = ft_strlen(end_content);
	if ((flag_mask & 4) == 4 && width > c_len)
	{
		//i = (*cnt[0] == '\0') ? write(1, '\0', 1) : -1;
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
		// if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		// {
		// 	tmp[++i] = end_content[0];
		// 	end_content[0] = '0';
		// }
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	//free(*cnt);
	*cnt = end_content;
	//printf("Start %s end.\n", end_content);
}

void	str_format(t_pfarg *arg)
{
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	// printf("The flags mask in diD_format: %d\n", flag_mask);
	// fflush(stdout);

	p_len = 0;
	c_len = ft_strlen(arg->cnt);
	//c_len = (*cnt[0] == '-') ? c_len - 1 : c_len;
	
	// if (*cnt[0] == '0' && prec == 0)
	// 	*cnt[0] = '\0';
	//printf("Inside the percent_format\n");
	end_content = ft_strdup(arg->cnt);
	if (arg->prec < c_len)
	{
		end_content[arg->prec] = '\0';
		// p_len = prec - c_len;
		// tmp = ft_strnew(p_len);
		// tmp[p_len] = '\0';
		// i = 0;
		// if (end_content[0] == '-')
		// {
		// 	tmp[0] = '-';
		// 	end_content[0] = '0';
		// 	i++;
		// }
		// while (i < p_len)
		// {
		// 	tmp[i] = '0';
		// 	i++;
		// }
		// end_content = ft_strjoin(tmp, end_content);
		// free(tmp);
	}

	// // Space, + flags parse
	// if ((flag_mask & 1) == 1 && end_content[0] != '-')
	// 	end_content = ft_strjoin("+", end_content);
	// else if ((flag_mask & 2) == 2 && end_content[0] != '-')
	// 	end_content = ft_strjoin(" ", end_content);

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
		if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		{
			tmp[++i] = end_content[0];
			end_content[0] = '0';
		}
		while (++i < arg->width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	//free(*cnt);
	arg->cnt = end_content;
	//printf("Start %s end.\n", end_content);
}

void	percent_format(char **cnt, int flag_mask, int width, int prec)
{
	// Precision parse
	//int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	// printf("The flags mask in diD_format: %d\n", flag_mask);
	// fflush(stdout);

	//p_len = 0;
	//c_len = ft_strlen(*cnt);
	//c_len = (*cnt[0] == '-') ? c_len - 1 : c_len;
	
	// if (*cnt[0] == '0' && prec == 0)
	// 	*cnt[0] = '\0';
	//printf("Inside the percent_format\n");
	end_content = ft_strdup(*cnt);
	// if (prec > c_len)
	// {
	// 	p_len = prec - c_len;
	// 	tmp = ft_strnew(p_len);
	// 	tmp[p_len] = '\0';
	// 	i = 0;
	// 	if (end_content[0] == '-')
	// 	{
	// 		tmp[0] = '-';
	// 		end_content[0] = '0';
	// 		i++;
	// 	}
	// 	while (i < p_len)
	// 	{
	// 		tmp[i] = '0';
	// 		i++;
	// 	}
	// 	end_content = ft_strjoin(tmp, end_content);
	// 	free(tmp);
	// }

	// // Space, + flags parse
	// if ((flag_mask & 1) == 1 && end_content[0] != '-')
	// 	end_content = ft_strjoin("+", end_content);
	// else if ((flag_mask & 2) == 2 && end_content[0] != '-')
	// 	end_content = ft_strjoin(" ", end_content);

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
		if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		{
			tmp[++i] = end_content[0];
			end_content[0] = '0';
		}
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
	//printf("Start %s end.\n", end_content);
}

void	diD_format(char **cnt, int flag_mask, int width, int prec)
{
	// Precision parse
	int		p_len;
	int		c_len;
	char	*tmp;
	int		i;
	char	*end_content;

	// printf("The flags mask in diD_format: %d\n", flag_mask);
	// fflush(stdout);

	p_len = 0;
	c_len = ft_strlen(*cnt);
	c_len = (*cnt[0] == '-') ? c_len - 1 : c_len;
	
	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';

	end_content = ft_strdup(*cnt);
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
		// if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		// {
		// 	tmp[++i] = end_content[0];
		// 	end_content[0] = '0';
		// }
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
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
	//printf("Start %s end.\n", end_content);
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
	//c_len = (content[0] == '-') ? c_len - 1 : c_len;

	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';

	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		// if (end_content[0] == '-')
		// {
		// 	tmp[0] = '-';
		// 	end_content[0] = '0';
		// 	i++;
		// }
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

	// Space, + flags parse
	// if ((flag_mask & 1) == 1 && end_content[0] != '-')
	// 	end_content = ft_strjoin("+", end_content);
	// else if ((flag_mask & 2) == 2 && end_content[0] != '-')
	// 	end_content = ft_strjoin(" ", end_content);

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
		// if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		// {
		// 	tmp[++i] = end_content[0];
		// 	end_content[0] = '0';
		// }
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
	//printf("Start %s end.\n", end_content);
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

	if (*cnt[0] == '0' && prec == 0)			// why it should be checked here, have no idea but works fine for 42FC
		*cnt[0] = '\0';
	else if (*cnt[0] == '0')					// maybe should use atoi_base here to check if the result is 0
		flag_mask = (flag_mask & 15);
	//c_len = (content[0] == '-') ? c_len - 1 : c_len;
	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		// if (end_content[0] == '-')
		// {
		// 	tmp[0] = '-';
		// 	end_content[0] = '0';
		// 	i++;
		// }
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	if ((flag_mask & 16) == 16 && prec != 0)	// # parse
		end_content = ft_strjoin("0x", end_content);	// here must be check for 0x || 0X

	// Space, + flags parse
	// if ((flag_mask & 1) == 1 && end_content[0] != '-')
	// 	end_content = ft_strjoin("+", end_content);
	// else if ((flag_mask & 2) == 2 && end_content[0] != '-')
	// 	end_content = ft_strjoin(" ", end_content);

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
		// if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		// {
		// 	tmp[++i] = end_content[0];
		// 	end_content[0] = '0';
		// }
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';				// need to shift the sign if it's present
		end_content = ft_strjoin(tmp, end_content);
		if (z_flag && (flag_mask & 16) == 16)
			end_content[1] = 'x';						// or X
		free(tmp);
	}
	free(*cnt);
	if (c_type == 'X')
		ft_strcap(end_content);
	*cnt = end_content;
	//printf("Start %s end.\n", end_content);
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
	//c_len = (content[0] == '-') ? c_len - 1 : c_len;

	if (*cnt[0] == '0' && prec == 0)
		*cnt[0] = '\0';

	end_content = ft_strdup(*cnt);

	if (prec > c_len)
	{
		p_len = prec - c_len;
		tmp = ft_strnew(p_len);
		tmp[p_len] = '\0';
		i = 0;
		// if (end_content[0] == '-')
		// {
		// 	tmp[0] = '-';
		// 	end_content[0] = '0';
		// 	i++;
		// }
		while (i < p_len)
		{
			tmp[i] = '0';
			i++;
		}
		end_content = ft_strjoin(tmp, end_content);
		free(tmp);
	}

	// Space, + flags parse
	// if ((flag_mask & 1) == 1 && end_content[0] != '-')
	// 	end_content = ft_strjoin("+", end_content);
	// else if ((flag_mask & 2) == 2 && end_content[0] != '-')
	// 	end_content = ft_strjoin(" ", end_content);

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
		// if ((end_content[0] == '-' || end_content[0] == '+') && z_flag)
		// {
		// 	tmp[++i] = end_content[0];
		// 	end_content[0] = '0';
		// }
		while (++i < width - c_len)
			tmp[i] = z_flag ? '0' : ' ';
		end_content = ft_strjoin(tmp, end_content);	
		free(tmp);
	}
	free(*cnt);
	*cnt = end_content;
	//printf("Start %s end.\n", end_content);
}
