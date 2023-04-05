# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/04/04 14:01:18 by lkavalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	./SRC/main.c 			\
		./SRC/errors.c 			\
		./SRC/parsing.c			\
		./SRC/init.c			\
		./SRC/errors_utils.c	\
		./SRC/free.c			\
		./SRC/texure_handling.c \
		./SRC/utils.c			\
		./SRC/colors.c			\
		./SRC/map.c				\
		./SRC/checking_map.c 	\
		./SRC/player.c 			\
		./SRC/debugging.c 		\
		./SRC/drawing2d_map.c 	\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address

MLX_PATH = mlx

all:$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): libftprintf/libftprintf.a $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -Lmlx -lmlx  -framework OpenGL -framework AppKit libftprintf.a -o $(NAME)

libftprintf/libftprintf.a:
	make -C libftprintf
	cp libftprintf/libftprintf.a .
	@echo "Making libftprintf..."

clean:
	make -C libftprintf clean
	rm -f $(OBJS)
	@echo "cleaning..."

fclean: clean
	make -C libftprintf fclean
	rm -f $(NAME)
	@echo "fully cleaning..."

re: fclean all
	@echo "remaking files..."