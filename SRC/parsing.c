/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:11:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/27 18:14:03 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void	check_for_elements(char *buffer, t_main *main)
{
	if (match("NO", buffer) == true)
		take_care_of_texure(buffer, main, 'N');
	else if (match("SO", buffer) == true)
		take_care_of_texure(buffer, main, 'S');
	else if (match("WE", buffer) == true)
		take_care_of_texure(buffer, main, 'W');
	else if (match("EA", buffer) == true)
		take_care_of_texure(buffer, main, 'E');
	else if (match("F", buffer) == true)
		take_care_of_color(buffer, main, 'F');
	else if (match("C", buffer) == true)
		take_care_of_color(buffer, main, 'C');
}

void	find_elements(t_main *main)
{
	int		size;
	int		i;
	char	*buffer;

	size = 1;
	i = 0;
	buffer = get_next_line(main->file_fd);
	while (buffer != NULL)
	{
		check_for_elements(buffer, main);
		printf("%s\n", buffer);
		free(buffer);
		buffer = get_next_line(main->file_fd);
	}
	close(main->file_fd);
}


static char	*save_map_line(char *buffer)
{
	int		len;
	char	*map_line;

	len = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	map_line = malloc((len + 1) * sizeof(char));
	map_line[len--] = '\0';
	while (len >= 0)
	{
		map_line[len] = buffer[len];
		len--;
	}
	return (map_line);
}

static void	save_map(t_main *main, char **argv, int len)
{
	int		i;
	int		line_len;
	char	*buffer;

	i = 0;
	line_len = 0;
	close(main->file_fd);
	open_the_file(main, argv);
	buffer = get_next_line(main->file_fd);
	while (buffer != NULL && check_for_map_start(buffer, main) == false)
	{
		free(buffer);
		buffer = get_next_line(main->file_fd);
	}
	if (buffer != NULL)
		printf("Start of the map: [%s]\n", buffer);
	main->map = malloc((len + 1) * sizeof(char *));
	while (buffer != NULL && i < len)
	{
		main->map[i] = save_map_line(buffer);
		free(buffer);
		buffer = get_next_line(main->file_fd);
		i++;
	}
	main->map[i] = NULL;
	main->height = len;
	close(main->file_fd);
	printf("MAP SAVED SUCCESFULLY!\n");
}

static void	find_map(t_main *main, char **argv)
{
	int		len;
	int		c;
	bool	empty_found;
	char	*buffer;

	printf(YELL "MAP PARSING ----------------------------------\n" B);
	len = 0;
	c = 0;
	empty_found = false;
	buffer = get_next_line(main->file_fd);
	while (buffer != NULL && check_for_map_start(buffer, main) == false)
	{
		free(buffer);
		buffer = get_next_line(main->file_fd);
	}
	if (buffer != NULL)
		printf("Start of the map: [%s]\n", buffer);
	while (buffer != NULL)
	{
		len++;
		if (check_map_fragments(main, buffer, &c) == 1 && c == 2)
			parsing_cleaning(main, buffer, EMPTY_LINE_IN_MAP);
		free(buffer);
		buffer = get_next_line(main->file_fd);
	}
	save_map(main, argv, len);
}

static void	check_map(t_main *main)
{
	int i;

	i = 0;
	while (main->map[i] != NULL)
	{
		printf("Check_map[%d]: [%s]\n", i, main->map[i]);
		i++;
	}
}

static void	check_player_direction(t_main *main)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (main->map[i] != NULL)
	{
		while (main->map[i][x] != '\0')
		{
			if (main->map[i][x] == 'N' || main->map[i][x] == 'S' || \
				main->map[i][x] == 'E' || main->map[i][x] == 'W')
			{
				if (main->p_dir != '0')
					parsing_cleaning(main, NULL, MORE_THAN_ONE_PLAYER);
				main->p_dir = main->map[i][x];
				main->p_pos_x = x;
				main->p_pos_y = i;
			}
			x++;
		}
		x = 0;
		i++;
	}
	if (main->p_dir == '0')
		parsing_cleaning(main, NULL, PLAYER_DOES_NOT_EXIST);
}

static void	check_line_top_and_bottom(t_main *main)
{
	int	i;
	int	len;

	i = 0;
	len = main->height - 1;
	while (main->map[0][i] != '\0' && \
			main->map[0][i] != '0' && main->map[0][i] != main->p_dir)
		i++;
	if (main->map[0][i] == '0' || main->map[0][i] == main->p_dir)
		parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
	i = 0;
	while (main->map[len][i] != '\0' && \
			main->map[len][i] != '0' && main->map[len][i] != main->p_dir)
		i++;
	if (main->map[len][i] == '0' || main->map[len][i] == main->p_dir)
		parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
}

static int	check_right(t_main *main, int x, int y)
{
	int	x_r;
	int	y_up;
	int	y_down;

	x_r = x + 1;
	y_up = y + 1;
	y_down = y - 1;
	printf("check right down corner!\n");
	if (y != 0 && x_r < (int)ft_strlen(main->map[y_down]) && \
	(main->map[y_down][x_r] == '0' || main->map[y_down][x_r] == main->p_dir))
	{
		if (main->map[y_down][x] != '1')
			return (1);
		else if (x_r < (int)ft_strlen(main->map[y]) && main->map[y][x_r] != '1')
			return (1);
	}
	printf("check right middle!\n");
	if (x_r < (int)ft_strlen(main->map[y]) && \
		(main->map[y][x_r] == '0' || main->map[y][x_r] == main->p_dir))
		return (1);
	printf("check right up corner!\n");
	if (y_up < main->height && (x_r < (int)ft_strlen(main->map[y_up])) && \
		(main->map[y_up][x_r] == '0' || main->map[y_up][x_r] == main->p_dir))
	{
		if (main->map[y_up][x] != '1')
			return (1);
		else if (x_r < (int)ft_strlen(main->map[y]) && main->map[y][x_r] != '1')
			return (1);
	}
	return (0);
}

static int	check_middle(t_main *main, int x, int y)
{
	int	y_up;
	int	y_down;

	y_up = y + 1;
	y_down = y - 1;
	printf ("middle down\n");
	if (y != 0 && x < (int)ft_strlen(main->map[y_down]) && (main->map[y_down][x] == '0' || main->map[y_down][x] == main->p_dir))
		return (1);
	printf ("middle middle\n");
	if (main->map[y][x] == '0' || main->map[y][x] == main->p_dir)
		return (1);
	printf ("middle up\n");
	if (y_up < main->height && x < (int)ft_strlen(main->map[y_up]) && (main->map[y_up][x] == '0' || main->map[y_up][x] == main->p_dir))
		return (1);
	printf("After\n");
	return (0);
}

static int	check_left(t_main *main, int x, int y)
{
	int	y_d;
	int	y_up;
	int	x_l;

	y_d = y - 1;
	y_up = y + 1;
	x_l = x - 1;
	if (y != 0 && x != 0  && x_l < (int)ft_strlen(main->map[y_d]) && main->map[y_d][x_l] == '0')
	{
		printf("first!\n");
		if (x < (int)ft_strlen(main->map[y_d]) && main->map[y_d][x] != '1')
			return (1);
		printf("second!\n");
		if (main->map[y][x_l] != '1')
			return (1);
		printf("third!\n");
	}
	if (x != 0 && x_l < (int)ft_strlen(main->map[y]) && (main->map[y][x_l] == '0' || main->map[y][x_l] == main->p_dir))
		return (1);
	if (x != 0 && (y_up < main->height) && x - 1 < (int)ft_strlen(main->map[y_up]) && \
					main->map[y_up][x_l] == '0')
	{
		if (main->map[y][x_l] != '1')
			return (1);
		else if (main->map[y_up][x] != '1')
			return (1);
	}
	return (0);
}
static void	check_spaces(t_main *main)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < main->height)
	{
		while (x < (int)ft_strlen(main->map[y]) && main->map[y][x] != '\0')
		{
			if (main->map[y][x] != '\0' && main->map[y][x] == ' ')
			{
				main->map[y][x] = '+';
				printf("ISsue1\n");
				if (check_right(main, x, y) == 1)
					parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
				printf("Issue2\n");
				if (check_middle(main, x, y) == 1)
					parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
				printf("Issue3\n");
				if (check_left(main, x, y) == 1)
					parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
				printf("Issue4\n");
			}
			if (x + 3 < (int)ft_strlen(main->map[y]) && main->map[y][x + 3] == ' ')
				x += 3;
			else
				x++;
		}
		check_map(main);
		x = 0;
		y++;
	}
}

static void	check_for_open_walls(t_main *main)
{
	if (main->height < 3)
		parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
	check_line_top_and_bottom(main);
	check_spaces(main);
}

void	parsing(t_main *main, char **argv)
{
	printf("checking fd: %d\n", main->file_fd);
	find_elements(main);
	open_the_file(main, argv);
	find_map(main, argv);
	check_map(main);
	check_player_direction(main);
	
	printf("check players direction:	[%c]\n", main->p_dir);
	printf("check players position x:	[%d]\n", main->p_pos_x);
	printf("check players position y:	[%d]\n", main->p_pos_y);
	printf("height of the map:			[%d]\n", main->height);
	check_for_open_walls(main);
	check_map(main);
}
