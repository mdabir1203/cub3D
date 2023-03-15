# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/03/15 18:28:27 by lkavalia         ###   ########.fr        #
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
	$(CC) $(OBJS) -Lmlx -lmlx  -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJS)
	@echo "cleaning..."

fclean: clean
	rm -f $(NAME)
	@echo "force cleaning..."

re: fclean all
	@echo "remaking files..."