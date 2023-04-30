/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texure_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:30:45 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/30 18:08:58 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*prepare_element_path(char *str)
{
	int		len;
	char	*element_path;

	len = 0;
	element_path = NULL;
	if (str == NULL)
		ft_exiterr(MISSING_ELEMENT_PATH);
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	element_path = ft_calloc(len + 1, sizeof(char));
	if (element_path == NULL)
		printf(RED "calloc has failed!\n" B);
	element_path[len] = '\0';
	len--;
	while (len >= 0)
	{
		element_path[len] = str[len];
		len--;
	}
	return (element_path);
}

char	*save_element(t_main *main, char *buffer)
{
	int		i;
	char	*element_name;
	char	*element_path;
	char	**split;

	i = 0;
	element_name = NULL;
	element_path = NULL;
	split = ft_split(buffer, ' ');
	while (split[i] != NULL)
		i++;
	if (i != 2)
	{
		i = 0;
		while (split[i] != NULL)
			free(split[i++]);
		free(split);
		free(element_name);
		clear_the_main_struct(main);
		ft_exiterr(FOUND_ELEMENT_TRASH);
	}
	element_path = prepare_element_path(split[1]);
	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
	free(element_name);
	return (element_path);
}

void	load_xpm(t_hive *hive)
{
	hive->main->north_t = mlx_xpm_file_to_image(hive->vars->mlx, \
		D_NO, &(hive->data->width), &(hive->data->height));
	hive->main->south_t = mlx_xpm_file_to_image(hive->vars->mlx, \
		D_SO, &(hive->data->width), &(hive->data->height));
	hive->main->west_t = mlx_xpm_file_to_image(hive->vars->mlx, \
		D_WE, &(hive->data->width), &(hive->data->height));
	hive->main->east_t = mlx_xpm_file_to_image(hive->vars->mlx, \
		D_EA, &(hive->data->width), &(hive->data->height));
}

void	take_care_of_texure(char *buffer, t_main *main, char name)
{
	if (name == 'N')
	{
		if (main->north_t != NULL)
			free(main->north_t);
		main->north_t = save_element(main, buffer);
	}
	else if (name == 'S')
	{
		if (main->south_t != NULL)
			free(main->south_t);
		main->south_t = save_element(main, buffer);
	}
	else if (name == 'W')
	{
		if (main->west_t != NULL)
			free(main->west_t);
		main->west_t = save_element(main, buffer);
	}
	else if (name == 'E')
	{
		if (main->east_t != NULL)
			free(main->east_t);
		main->east_t = save_element(main, buffer);
	}
}
