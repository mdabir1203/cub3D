# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/03/17 17:19:19 by lkavalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	./SRC/main.c 		\
		./SRC/errors.c 		\
		./SRC/parsing.c		\
		./SRC/init.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address

MLX_PATH = mlx

all:$(NAME)

%.o: %.c
	$(CC) -fsanitize=address -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS) ft_printf/libftprintf.a
	$(CC) $(OBJS) -fsanitize=address -Lmlx -lmlx  -framework OpenGL -framework AppKit libftprintf.a -o $(NAME)

ft_printf/libftprintf.a:
	make -C ft_printf
	cp ft_printf/libftprintf.a .
	@echo "Making libftprintf..."

clean:
	make clean -C ft_printf
	rm -f $(OBJS)
	@echo "cleaning..."

fclean: clean
	rm -f $(NAME)
	@echo "force cleaning..."

re: fclean all
	@echo "remaking files..."