# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 12:35:38 by lkavalia          #+#    #+#              #
#    Updated: 2023/04/07 15:58:10 by rehernan         ###   ########.fr        #
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

CFLAGS = -Wall -Werror -Wextra -g

all: submodule $(NAME)

UNAME := $(shell uname)
%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
minilibx-linux/libmlx.a:
	make -C minilibx-linux
	cp MLX/libmlx.a
	@echo "Making MLX..."

submodule:
	git submodule update --init

ifeq ($(UNAME), Darwin)
$(NAME): libftprintf/libftprintf.a $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -lmlx  -framework OpenGL -framework AppKit libftprintf.a -o $(NAME)
endif

ifeq ($(UNAME), Linux)
$(NAME): libftprintf/libftprintf.a  minilibx-linux/libmlx.a $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) minilibx-linux/libmlx.a -L/usr/include/X11/extensions -lX11 -lXext libftprintf.a -o $(NAME)
endif

libftprintf/libftprintf.a:
	make -C libftprintf
	cp libftprintf/libftprintf.a .
	@echo "Making libftprintf..."

clean:
	make -C libftprintf clean
	rm libftprintf.a
	rm -f $(OBJS)
	@echo "cleaning..."

fclean: clean
	make -C libftprintf fclean
	rm -f $(NAME)
	@echo "fully cleaning..."

re: fclean all
	@echo "remaking files..."

.PHONY: all clean fclean re submodule