#include <stdlib.h>
#include "ft_printf.h"

#define ABS(n) ((n) < 0 ? -(n) : (n))

// static void	parse(int n, int b, char *res, int *i)
// {
// 	char	base[] = "0123456789ABCDEF";

// 	if (n <= -b || b <= n)
// 		parse(n / b, b, res, i);
// 	res[(*i)++] = base[ABS(n % b)];
// }

// char		*ft_itoa_base(int val, int base)									// need to change size-type of int arg to hold larger types
// {
// 	int		i;
// 	char	*res;

// 	if (base < 2 || 16 < base || !(res = (char *)malloc(sizeof(char) * 35)))	// libft ft_strnew() here can 
// 		return (NULL);
// 	i = 0;
// 	if (base == 10 && val < 0)
// 		res[i++] = '-';
// 	parse(val, base, res, &i);
// 	return (res);
// }

static void	parse(size_t n, int b, char *res, int *i)
{
	char	base[] = "0123456789abcdef";

	//if (n <= -b || b <= n)
	if ((unsigned int)b <= n)
		parse(n / b, b, res, i);
	res[(*i)++] = base[n % b];
}

char		*ft_uitoa_base(size_t val, int base)									// need to change size-type of int arg to hold larger types
{
	int		i;
	char	*res;

	//printf("The value at the start of uitoa_base: %zi\n", val);
	if (base < 2 || 16 < base || !(res = ft_strnew(65)))	// libft ft_strnew() here can 
		return (NULL);
	i = 0;
	// if (base == 10 && val < 0)
	// 	res[i++] = '-';
	parse(val, base, res, &i);
	//printf("The result str at the end of uitoa_base: %s\n", res);
	return (res);
}