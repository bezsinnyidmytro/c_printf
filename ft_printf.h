#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct 		s_pfarg
{
	char			*cnt;
	size_t			cnt_len;
	int				fmt_flags;
	int				width;
	int				prec;
	int				size_flag;
	char			c_type;
	//int				bytes;
	va_list			*argp;
}					t_pfarg;

int					ft_printf(char *str, ...);
void				struct_parse(char **str, va_list *ap, int *b_printed);
char				*ft_uitoa_base(size_t val, int base);		// need to change size-type of arg

/*	FORMAT FUNCTIONS	*/
void				diD_format(char **cnt, int flag_mask, int width, int prec);
void				oO_format(char **cnt, int flag_mask, int width, int prec);
void				xX_format(char **cnt, int flag_mask, int width, int prec, char c_type);
void				uU_format(char **cnt, int flag_mask, int width, int prec);
void				percent_format(char **cnt, int flag_mask, int width, int prec);
void				str_format(char **cnt, int flag_mask, int width, int prec);

/*	LIBFT FUNCTIONS	*/
char				*ft_strnew(size_t size);
char				*ft_itoa(ssize_t n);
char				*ft_uitoa(size_t n);
char				*ft_strchr(const char *s, int c);
unsigned long int	ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
void				ft_putstr(char const *str);
void				ft_putchar(char ch);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strcat(char *s1, const char *s2);
void				ft_strcap(char *str);

#endif