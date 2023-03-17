/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:19:31 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/17 17:45:06 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: ENUMS for readability

void	ft_exiterr(int err)
{
	if (err == NOT_ENOUGH_ARGS)
		ft_putstr_fd(RED "Not enough arguments!\n" BLANK, 2);
	else if (err == INVALID_ARGS)
		ft_putstr_fd(RED "Invalid arguments!\n" BLANK, 2);
	else if (err == WRONG_FILE_EXTENSION)
		ft_putstr_fd(RED "Incorrect file extension! I only accept files with [.cub] extension!\n" BLANK, 2);
	else if (err == FILE_IS_NOT_THERE)
		ft_putstr_fd(RED "File does not exist!\n" BLANK, 2);
	exit (err);
}

//Checks if the file extension is .cub
static void	check_file_extension(char *filename)
{
	int		i;
	char	*file_ex;

	i = ft_strlen(filename);
	file_ex = ft_substr(filename, i - 4, 4);
	printf("[1] Check the extension: %s\n", file_ex);
	if (ft_strncmp(file_ex, ".cub", ft_strlen(".cub")) != 0)
	{
		free(file_ex);
		ft_exiterr(WRONG_FILE_EXTENSION);
	}
	free(file_ex);
}

void	check_basic_errors(t_main *main, int argc, char **argv)
{
	if (argc != 2)
		ft_exiterr(NOT_ENOUGH_ARGS);
	check_file_extension(argv[1]);
	open_the_file(main, argv);
}
