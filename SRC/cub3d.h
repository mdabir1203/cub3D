/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:00:09 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/17 17:45:41 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//Headers
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../ft_printf/ft_printf.h"

typedef struct s_main
{
	int		file_fd;
	char	*north_t;
	char	*south_t;
	char	*west_t;
	char	*east_t;

	int		f[3];
	int		c[3];
}t_main;

//errors.c
void	ft_exiterr(int err);
void	check_basic_errors(t_main *main, int argc, char **argv);

//init.c
void	initialize_main(t_main *main);

//parsing.c
void	parsing(t_main *main);
void	open_the_file(t_main *main, char **argv);

//ERROR Codes
# define NOT_ENOUGH_ARGS 		1
# define INVALID_ARGS			2
# define WRONG_FILE_EXTENSION 	3
# define FILE_IS_NOT_THERE 		4

//Colors
# define BLANK "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELL "\033[0;33m"
# define CYAN "\033[0;36m"

//Things
# define D_NO
# define D_SO
# define D_WE
# define D_EA
# define D_F "220,100,0"
# define D_C "225,30,0"
#endif
