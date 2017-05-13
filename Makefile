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

PRINTF_DIR =	printf_src/
PRINTF_FILES =	ft_printf.c \
				arg_struct_parse.c \
				numeric_arg_parser.c \
				format_flags_parser.c \
				char_str_arg_parser.c \
				format_controller.c \
				printf_formats.c \
				zero_minus_flags.c \
				float_round.c \
				float_to_str.c \
				e_conversion.c
PRINTF_SRC =	$(addprefix $(PRINTF_DIR), $(PRINTF_FILES))

LIBFT_DIR =		libft_src/
LIBFT_FILES = 	itoa_base.c \
				ft_itoa.c \
				ft_strnew.c \
				libft_func_01.c \
				libft_func_02.c
LIBFT_SRC = 	$(addprefix $(LIBFT_DIR), $(LIBFT_FILES))

SRC =	$(PRINTF_SRC) $(LIBFT_SRC)
OBJ =	$(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra

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