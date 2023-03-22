/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:11:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/22 18:29:34 by lkavalia         ###   ########.fr       */
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
	printf("checking n_t: [%s]\n", main->north_t);
	printf("checking n_t: [%s]\n", main->south_t);
	printf("checking n_t: [%s]\n", main->west_t);
	printf("checking n_t: [%s]\n", main->east_t);
	printf("roof [%d]\n", main->roof);
	printf("floor: [%d]\n", main->floor);
}

void	parsing(t_main *main)
{
	printf("checking fd: %d\n", main->file_fd);
	find_elements(main);
}
