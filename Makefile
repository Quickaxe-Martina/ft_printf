# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmartina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 16:01:11 by qmartina          #+#    #+#              #
#    Updated: 2019/10/17 16:01:15 by qmartina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c ft_printf.c ft_add_c_s_d.c ft_color.c
OBJ= $(patsubst %.c,%.o,$(SRC))

HEADER = -I ft_printf.h
PATH_LIBFT = libft

all: $(NAME)

$(NAME): $(PATH_LIBFT)/libft.a $(OBJ)
	$(CC) $(CFLAGS) -I libftprintf.h -c $(SRC)
	@cp $(PATH_LIBFT)/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(PATH_LIBFT)/libft.a:
	make -C $(PATH_LIBFT)

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PATH_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
