/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:11:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/23 18:40:18 by lkavalia         ###   ########.fr       */
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

static void	find_map(t_main *main)
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
}

void	parsing(t_main *main, char **argv)
{
	printf("checking fd: %d\n", main->file_fd);
	find_elements(main);
	open_the_file(main, argv);
	find_map(main);
}
