/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:11:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/20 19:02:11 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_the_file(t_main *main, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exiterr(FILE_IS_NOT_THERE);
	main->file_fd = fd;
}

static bool	match(char *searched, char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	while (searched[x] != '\0' && str[i] != '\0' && searched[x] == str[i])
	{
		x++;
		i++;
	}
	if (searched[x] == '\0')
		return (true);
	return (false);
}

static char	*save_texure(char *buffer)
{
	char	*texure_name;
	char	*texure_path;
	char	**split;

	texure_name = NULL;
	texure_path = NULL;
	split = ft_split(buffer, '.');
	texure_name = split[0];
	texure_path = split[1];
	free(texure_name);
	return (texure_path);
}

static void	check_for_elements(char *buffer, t_main *main)
{
	if (match("NO", buffer) == true)
	{
		if (main->north_t != NULL)
			free(main->north_t);
		main->north_t = save_texure(buffer);
	}
	else if (match("SO", buffer) == true)
	{
		if (main->south_t != NULL)
			free(main->south_t);
		main->south_t = save_texure(buffer);
	}
	else if (match("WE", buffer) == true)
	{
		if (main->west_t != NULL)
			free(main->west_t);
		main->west_t = save_texure(buffer);
	}
	else if (match("EA", buffer) == true)
	{
		if (main->east_t != NULL)
			free(main->east_t);
		main->east_t = save_texure(buffer);
	}
}

void	find_texures(t_main *main)
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
	printf("checking n_t: %s\n", main->north_t);
	printf("checking n_t: %s\n", main->south_t);
	printf("checking n_t: %s\n", main->west_t);
	printf("checking n_t: %s\n", main->east_t);
}

void	parsing(t_main *main)
{
	printf("checking fd: %d\n", main->file_fd);
	find_texures(main);
}
