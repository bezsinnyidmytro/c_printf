#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <wchar.h>

typedef struct 		s_pfarg
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

int					ft_printf(char *str, ...);
void				struct_parse(char **str, va_list *ap, int *b_printed);
char				*ft_uitoa_base(size_t val, int base);		// need to change size-type of arg

/*	FORMAT FUNCTIONS	*/
void				diD_format(t_pfarg *arg);
void				oO_format(t_pfarg *arg);
void				xX_format(t_pfarg *arg);
void				uU_format(t_pfarg *arg);
void				percent_format(t_pfarg *arg);
void				str_format(t_pfarg *arg);
void				p_format(t_pfarg *arg);
void				cC_format(t_pfarg *arg);
void				prec_format(t_pfarg *arg, char **end_content);
void				zero_minus_format(t_pfarg *arg, char **end_content);
char				*pre_format(t_pfarg *arg);
void				hash_format(t_pfarg *arg, char **end_content);
void				signed_sign_format(t_pfarg *arg, char **end_content);

void				common_format(t_pfarg *arg);

/*	LIBFT FUNCTIONS	*/
char				*ft_strnew(size_t size);
char				*ft_itoa(ssize_t n);
char				*ft_uitoa(size_t n);
char				*ft_strchr(const char *s, int c);
unsigned long int	ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, int n);
void				ft_pfputstr(t_pfarg *arg);
void				ft_putchar(char ch);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strcat(char *s1, const char *s2);
void				ft_strcap(char *str);

#endif