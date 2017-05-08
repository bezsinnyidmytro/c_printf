#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/30 16:12:36 by dbezsinn          #+#    #+#              #
#    Updated: 2017/04/30 16:12:38 by dbezsinn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SRC = 	ft_printf.c \
		itoa_base.c \
		arg_struct_parse.c \
		format_controller.c \
		printf_formats.c \
		zero_minus_flags.c \
		ft_itoa.c \
		ft_strnew.c \
		libft_func_01.c \
		libft_func_02.c

OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra

# norminette ft_printf.c itoa_base.c arg_struct_parse.c format_controller.c printf_formats.c zero_minus_flags.c ft_itoa.c ft_strnew.c libft_func_01.c libft_func_02.c

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -c $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all