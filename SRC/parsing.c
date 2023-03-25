/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:11:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/25 16:11:33 by lkavalia         ###   ########.fr       */
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

static void	check_the_map(t_main *main)
{
	int i;

	i = 0;
	while (main->map[i] != NULL)
	{
		printf("Check_map: [%s]\n", main->map[i]);
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
				if (main->player_direction != '0')
					parsing_cleaning(main, NULL, MORE_THAN_ONE_PLAYER);
				main->player_direction = main->map[i][x];
				main->player_pos_x = x;
				main->player_pos_y = i;
			}
			x++;
		}
		x = 0;
		i++;
	}
}

void	parsing(t_main *main, char **argv)
{
	printf("checking fd: %d\n", main->file_fd);
	find_elements(main);
	open_the_file(main, argv);
	find_map(main, argv);
	check_the_map(main);
	check_player_direction(main);
	printf("check players direction: [%c]\n", main->player_direction);
	printf("check players position x: [%d]\n", main->player_pos_x);
	printf("check players position y: [%d]\n", main->player_pos_y);
}
