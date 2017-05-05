#include <stdlib.h>
#include "ft_printf.h"

#define ABS(n) ((n) < 0 ? -(n) : (n))

static void	parse(size_t n, int b, char *res, int *i)
{
	char	base[] = "0123456789abcdef";

	if ((unsigned int)b <= n)
		parse(n / b, b, res, i);
	res[(*i)++] = base[n % b];
}

char		*ft_uitoa_base(size_t val, int base)
{
	int		i;
	char	*res;

	//printf("The value at the start of uitoa_base: %zi\n", val);
	if (base < 2 || 16 < base || !(res = ft_strnew(65)))
		return (NULL);
	i = 0;
	parse(val, base, res, &i);
	//printf("The result str at the end of uitoa_base: %s\n", res);
	return (res);
}
