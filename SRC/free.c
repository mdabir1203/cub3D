/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:28:17 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/08 13:13:00 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_wall_texures(t_hive *hive)
{
	if (hive->wall_tex->texture_east != NULL)
	{
		mlx_destroy_image(hive->vars->mlx, hive->wall_tex->texture_east->img);
		free(hive->wall_tex->texture_east);
	}
	if (hive->wall_tex->texture_north != NULL)
	{
		mlx_destroy_image(hive->vars->mlx, hive->wall_tex->texture_north->img);
		free(hive->wall_tex->texture_north);
	}
	if (hive->wall_tex->texture_south != NULL)
	{
		mlx_destroy_image(hive->vars->mlx, hive->wall_tex->texture_south->img);
		free(hive->wall_tex->texture_south);
	}
	if (hive->wall_tex->texture_west != NULL)
	{
		mlx_destroy_image(hive->vars->mlx, hive->wall_tex->texture_west->img);
		free(hive->wall_tex->texture_west);
	}
	free(hive->wall_tex);
}

void	freeing_hive(t_hive *hive)
{
	if (hive->b != NULL)
		free(hive->b);
	destroy_wall_texures(hive);
	mlx_destroy_window(hive->vars->mlx, hive->vars->win);
	if (hive->data != NULL)
		free(hive->data);
	if (hive->vars != NULL)
		free(hive->vars);
	clear_the_main_struct(hive->main);
	free(hive->main);
	free(hive);
}

void	parsing_cleaning(t_main *main, char *arr, int err)
{
	if (arr != NULL)
		free(arr);
	clear_the_main_struct(main);
	free(main);
	ft_exiterr(err);
}

int	close_game(t_hive *hive)
{
	freeing_hive(hive);
	exit(0);
}

void	clear_the_main_struct(t_main *main)
{
	int	i;

	i = 0;
	if (main->file_fd > 2)
		close(main->file_fd);
	if (main->north_t != NULL)
		free(main->north_t);
	if (main->south_t != NULL)
		free(main->south_t);
	if (main->west_t != NULL)
		free(main->west_t);
	if (main->east_t != NULL)
		free(main->east_t);
	if (main->map != NULL)
	{
		while (main->map[i] != NULL)
			free(main->map[i++]);
		free(main->map);
	}
}
