/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:58:29 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/05/08 16:58:33 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <wchar.h>

typedef struct		s_pfarg
{
	char			*cnt;
	size_t			cnt_len;
	int				fmt_flags;
	int				width;
	int				prec;
	int				size_flag;
	char			c_type;
	int				is_zero_char;
	va_list			*argp;
}					t_pfarg;

int					ft_printf(const char *str, ...);

void				struct_parse(const char **str, va_list *ap,
								size_t *b_printed);
int					parse_size_flags(const char **str, t_pfarg *arg);
int					parse_prec(const char **str, t_pfarg *arg, int prec);
int					parse_width(const char **str, t_pfarg *arg);
int					parse_fmt_flags(const char **str, t_pfarg *arg);

size_t				s_size_parse(t_pfarg *arg);
size_t				u_size_parse(t_pfarg *arg);
char				*string_parse(t_pfarg *arg);
char				*char_parse(t_pfarg *arg, int udef_flag);

char				*pre_format(t_pfarg *arg);
void				prec_format(t_pfarg *arg, char **end_content);
void				hash_format(t_pfarg *arg, char **end_content);
void				signed_sign_format(t_pfarg *arg, char **end_content);
void				zero_minus_format(t_pfarg *arg, char **end_content);
void				common_format(t_pfarg *arg);

char				*ft_uitoa_base(size_t val, int base);
char				*ft_strnew(size_t size);
char				*ft_itoa(ssize_t n);
char				*ft_uitoa(size_t n);
char				*ft_strchr(const char *s, int c);
unsigned long int	ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, unsigned int n);
void				ft_pfputstr(t_pfarg *arg);
void				ft_putchar(char ch);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strcat(char *s1, const char *s2);
void				ft_strcap(char *str);
void				ft_swap_chars(char *a, char *b);

#endif
