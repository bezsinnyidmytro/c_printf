#include "ft_printf.h"

/*------------------------------*/
/*		PARSE SIZE FLAGS		*/
/*______________________________*/

size_t		udef_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->c_type == 'o' || arg->c_type == 'O')
		parsed_arg = va_arg(*(arg->argp), unsigned int);
	else if (arg->c_type == 'x' || arg->c_type == 'X')
		parsed_arg = va_arg(*(arg->argp), unsigned int);
	else if (arg->c_type == 'u')
		parsed_arg = va_arg(*(arg->argp), unsigned int);
	else if (arg->c_type == 'U')
		parsed_arg = va_arg(*(arg->argp), unsigned long int);
	return (parsed_arg);
}

size_t		u_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->size_flag == 1)
		parsed_arg = (unsigned char)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 2)
		parsed_arg = (unsigned short int)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 3)
		parsed_arg = va_arg(*(arg->argp), unsigned long int);
	else if (arg->size_flag == 4)
		parsed_arg = va_arg(*(arg->argp), unsigned long long int);
	else if (arg->size_flag == 5)
		parsed_arg = va_arg(*(arg->argp), uintmax_t);
	else if (arg->size_flag == 6)
		parsed_arg = va_arg(*(arg->argp), size_t);
	else
		parsed_arg = udef_size_parse(arg);
	return (parsed_arg);
}

size_t		sdef_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->c_type == 'd' || arg->c_type == 'i')
		parsed_arg = va_arg(*(arg->argp), int);
	else if (arg->c_type == 'D')
		parsed_arg = va_arg(*(arg->argp), long int);
	return (parsed_arg);
}

size_t		s_size_parse(t_pfarg *arg)
{
	size_t	parsed_arg;

	parsed_arg = 0;
	if (arg->size_flag == 1)
		parsed_arg = (char)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 2)
		parsed_arg = (short int)va_arg(*(arg->argp), int);
	else if (arg->size_flag == 3)
		parsed_arg = va_arg(*(arg->argp), long int);
	else if (arg->size_flag == 4)
		parsed_arg = va_arg(*(arg->argp), long long int);
	else if (arg->size_flag == 5)
		parsed_arg = va_arg(*(arg->argp), intmax_t);
	else if (arg->size_flag == 6)
		parsed_arg = va_arg(*(arg->argp), ssize_t);
	else
		parsed_arg = sdef_size_parse(arg);
	return (parsed_arg);
}


char		*char_parse(t_pfarg *arg)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * 2);
	res[1] = 0;
	res[0] = (unsigned char)va_arg(*(arg->argp), int);
	return (res);
}

void		parse_arg(t_pfarg *arg)
{
	// HERE CAN USE LIST of FUNCTIONS

	if (ft_strchr("idDoOxXuUpcCsS%", arg->c_type))
	{
		if (arg->c_type == 'i' || arg->c_type == 'd' || arg->c_type == 'D')
			arg->cnt = ft_itoa(s_size_parse(arg));
		if (arg->c_type == 'o' || arg->c_type == 'O')
			arg->cnt = ft_uitoa_base(u_size_parse(arg), 8);
		if (arg->c_type == 'x' || arg->c_type == 'X')
			arg->cnt = ft_uitoa_base(u_size_parse(arg), 16);
		if (arg->c_type == 'u' || arg->c_type == 'U')
			arg->cnt = ft_uitoa_base(u_size_parse(arg), 10);
		if (arg->c_type == 'c' || arg->c_type == 'C')
			arg->cnt = char_parse(arg);
		if (arg->c_type == 's' || arg->c_type == 'S')
		{
			arg->cnt = va_arg(*(arg->argp), char *);
			arg->cnt = (arg->cnt == NULL) ? "(null)" : arg->cnt;
		}
		if (arg->c_type == '%')
			arg->cnt = ft_strdup("%");
		if (arg->c_type == 'p')
			arg->cnt = ft_uitoa_base((uintmax_t)va_arg(*(arg->argp), void *), 16);
	}
}

/*------------------------------*/
/*		FLAGS_PARSING			*/
/*______________________________*/

int			parse_size_flags(char **str, t_pfarg *arg)
{
	int		cur_size;
	char	*flags;

	flags = ft_strdup("hljz");						// can be global
	cur_size = 0;
	while (**str != '\0' && ft_strchr(flags, **str))
	{
		if (**str == 'h' && *(*str + 1) == 'h')
		{
			cur_size = (cur_size > 1) ? cur_size : 1;
			*str = *str + 1;
		}
		else if (**str == 'h')
			cur_size = (cur_size > 2) ? cur_size : 2;
		if (**str == 'l')
			cur_size = (cur_size > 3) ? cur_size : 3;
		if (**str == 'l' && *(*str + 1) == 'l')
			cur_size = (cur_size > 4) ? cur_size : 4;
		if (**str == 'j')
			cur_size = (cur_size > 5) ? cur_size : 5;
		if (**str == 'z')
			cur_size = 6;
		*str = *str + 1;
	}
	if (arg->size_flag < cur_size)
		arg->size_flag = cur_size;
	return ((cur_size > 0) ? 1 : 0);
}

int			parse_prec(char **str, t_pfarg *arg)
{
	int		prec;

	prec = -1;
	if (**str == '.')
	{
		prec = 0;
		*str = *str + 1;
		if (**str >= '0' && **str <= '9')
		{
			prec = 0;
			while (**str >= '0' && **str <= '9')
			{
				prec = prec * 10 + (**str - '0');
				*str = *str + 1;
			}
		}
		else if (**str == '*')
		{
			prec = va_arg(*(arg->argp), int);
			prec = (prec < 0) ? -1 : prec;
			*str = *str + 1;
		}
		arg->prec = prec;
		return (1);
	}
	return (0);
}

int			parse_width(char **str, t_pfarg *arg)
{
	int		width;

	width = 0;
	while ((**str != '\0' && **str > '0' && **str <= '9') ||
		(**str == '0' && width != 0))
	{
		width = width * 10 + (**str - '0');
		*str = *str + 1;
	}

	if (width > 0)
	{
		arg->width = width;
		return (1);
	}

	if (**str != '\0' && **str == '*')
	{
		arg->width = va_arg(*(arg->argp), int);
		if (arg->width < 0)
		{
			arg->width *= -1;
			arg->fmt_flags = arg->fmt_flags | 4;
		}
		*str = *str + 1;
		return (1);
	}

	return (0);
}

int			parse_fmt_flags(char **str, t_pfarg *arg)
{
	char	*flags;
	int		is_found;

	flags = ft_strdup("#0- +");							// can be global
	is_found = 0;
	while (**str != '\0' && ft_strchr(flags, **str))
	{
		is_found = 1;
		if (**str == '#')
			arg->fmt_flags = arg->fmt_flags | 16;
		else if (**str == '0')
			arg->fmt_flags = arg->fmt_flags | 8;
		else if (**str == '-')
			arg->fmt_flags = arg->fmt_flags | 4;
		else if (**str == ' ')
			arg->fmt_flags = arg->fmt_flags | 2;
		else if (**str == '+')
			arg->fmt_flags = arg->fmt_flags | 1;
		*str = *str + 1;
	}
	//*str = *str - 1;									// if there are no flags ?????

	// PROBABLY SHOULD BE EXTERNAL FUNCTION
	if ((arg->fmt_flags & 4) == arg->fmt_flags)			// - overrides 0
		arg->fmt_flags = arg->fmt_flags & 23;
	if ((arg->fmt_flags & 1) == arg->fmt_flags)			// + overrides space
		arg->fmt_flags = arg->fmt_flags & 29;
	
	return (is_found);
}

void		parse_conv(char **str, t_pfarg *arg)		// how to understand if there is no correct type flag??
{
	if (**str != '\0')										// CHECK FOR THE END OF STRING
	{
		arg->c_type = **str;
		if (arg->c_type == 'U' || arg->c_type == 'D' || arg->c_type == 'O')				// ADDING SIZE L IF IT IS U CONVERSION
			arg->size_flag = (arg->size_flag > 3) ? arg->size_flag : 3;
		if (arg->c_type == 'C' || arg->c_type == 'S')
			arg->size_flag = 3;
		*str = *str + 1;
	}
}

void		struct_parse(char **str, va_list *ap, int *b_printed)
{
	t_pfarg		*arg;

	arg = (t_pfarg*)malloc(sizeof(t_pfarg));		// check for malloc
	arg->cnt = NULL;
	arg->fmt_flags = 0;
	arg->width = 0;									// default width
	arg->prec = -1;									// default prec
	arg->size_flag = 0;
	arg->c_type = 0;
	arg->is_zero_char = 0;
	//arg->bytes = 0;
	arg->argp = ap;
	*str = *str + 1;
	// is_found = 1;
	//printf("%s\n", str);
	while (**str && (parse_fmt_flags(str, arg) ||
		parse_width(str, arg) || parse_prec(str, arg) || 
		parse_size_flags(str, arg)))
	{
		// READING FLAGS
	}
	parse_conv(str, arg);
	parse_arg(arg);
	if (arg->cnt)
	{
		if (arg->c_type == 'u' || arg->c_type == 'U')
			uU_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec);
		else if (arg->c_type == 'o' || arg->c_type == 'O')
			oO_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec);
		else if (arg->c_type == 'x' || arg->c_type == 'X')
			xX_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec, arg->c_type);
		else if (arg->c_type == 'i' || arg->c_type == 'd' || arg->c_type == 'D')
			diD_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec);
		else if (arg->c_type == '%')
			percent_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec);
		else if (arg->c_type == 'c' || arg->c_type == 'C')
			cC_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec, &(arg->cnt_len), &(arg->is_zero_char));
		else if (arg->c_type == 's' || arg->c_type == 'S')
			str_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec);
		else if (arg->c_type == 'p')
			p_format(&(arg->cnt), arg->fmt_flags, arg->width, arg->prec);
		ft_pfputstr(arg);
		*b_printed += ft_strlen(arg->cnt) + arg->cnt_len;
	}
	//	printf("%s\n", (arg->cnt));
	// printf("Parsed mask of fmt_flags: %d\n", arg->fmt_flags);
	// printf("Parsed width: %d\n", arg->width);
	// printf("Parsed precission: %d\n", arg->prec);
	// printf("Parsed size_flag: %d\n", arg->size_flag);
	// printf("Parsed type_conv: %c\n", arg->c_type);
}