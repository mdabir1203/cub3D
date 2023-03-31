/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:00:09 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/31 12:34:36 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//Headers
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libftprintf/ft_printf.h"

typedef struct s_main
{
	int		file_fd;

	char	p_dir;
	char	p_pos_x;
	char	p_pos_y;
	char	*north_t;
	char	*south_t;
	char	*west_t;
	char	*east_t;
	char	**map;
	int		height;
	int		floor;
	int		roof;
}t_main;

//checking_map.c
void	check_line_top_and_bottom(t_main *main);
int		check_right(t_main *main, int x, int y, int x_r);
int		check_middle(t_main *main, int x, int y);
int		check_left(t_main *main, int x, int y, int x_l);
void	check_spaces(t_main *main, int x, int y);

//colors.c
void	take_care_of_color(char *buffer, t_main *m, char id);

//debugging.c
void	check_map(t_main *main);

//errors_utils.c
bool	map_fragment_found(char *buffer);
bool	match_component_name(char *name);
bool	component_found(char *str);
void	find_trash(t_main *main, char *s);
void	parsing_cleaning(t_main *main, char *arr, int err);

//errors.c
void	ft_exiterr(int err);
void	check_basic_errors(t_main *main, int argc, char **argv);

//free.c
void	clear_the_main_struct(t_main *main);

//init.c
void	initialize_main(t_main *main);

//map.c
void	save_map(t_main *main, char **argv, int len);
bool	check_for_map_start(char *buffer, t_main *main);
int		map_skip_space(int i, char *b, char id);
int		check_map_fragments(t_main *main, char *b, int *c);

//parsing.c
void	parsing(t_main *main, char **argv);

//player.c
void	check_player_direction(t_main *main);

//texure_handling.c
char	*save_element(t_main *main, char *buffer);
void	take_care_of_texure(char *buffer, t_main *main, char name);

//utils.c
bool	match(char *searched, char *str);
void	open_the_file(t_main *main, char **argv);

//ERROR Codes
# define NOT_ENOUGH_ARGS 		1
# define INVALID_ARGS			2
# define WRONG_FILE_EXTENSION 	3
# define FILE_IS_NOT_THERE 		4
# define INCORECT_FILE_CONFIG	5
# define CUB_CONTAINS_TRASH		6
# define MISSING_ELEMENT_PATH	7
# define FOUND_ELEMENT_TRASH	8
# define INCORECT_COLOR_VAL		9
# define TAB_IN_MAP_FOUND		10
# define MAP_NOT_CLOSED			11
# define WRONG_INFO_IN_MAP		12
# define EMPTY_LINE_IN_MAP		13
# define MORE_THAN_ONE_PLAYER	14
# define MAP_IS_NOT_CLOSED		15
# define PLAYER_DOES_NOT_EXIST	16

//Colors
# define B "\033[0m"
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
