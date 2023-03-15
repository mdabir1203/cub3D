# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/03/15 21:48:13 by rehernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = main.c \
		errors.c \
		parsing.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

MLX_PATH = mlx

all:$(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx  -framework OpenGL -framework AppKit libftprintf.a -o $(NAME)

ft_printf/libftprintf.a:
	make -C ft_printf
	cp ft_printf/libftprintf.a .
	@echo "Making libftprintf..."

clean:
	rm -f $(OBJS)
	@echo "cleaning..."

fclean: clean
	rm -f $(NAME)
	@echo "force cleaning..."

re: fclean all
	@echo "remaking files..."