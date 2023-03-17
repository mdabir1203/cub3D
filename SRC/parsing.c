/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:11:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/17 18:39:47 by lkavalia         ###   ########.fr       */
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

void	find_texures(t_main *main)
{
	int		buffer_size;
	int		read_size;
	char	buffer[buffer_size];

	buffer_size = 100;
	read_size = 0;
	read(main->file_fd, &buffer, buffer_size);
	buffer[buffer_size - 1] = '\0';
	printf("buffer: %s\n", buffer);
//	read(main->file_fd, &buffer, 4);
//	buffer[4] = '\0';
//	printf("buffer: %s\n", buffer);
}

void	parsing(t_main *main)
{
	printf("checking fd: %d\n", main->file_fd);
	find_texures(main);
}
