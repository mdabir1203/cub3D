/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:11:19 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/27 10:13:00 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * FILE (init.c) FUNCTION (initialize_main):
 * initializes all of the information in t_main struct to default state. 
 */
void	initialize_main(t_main *main)
{
	main->file_fd = -1;
	main->p_dir = '0';
	main->p_pos_x = 0;
	main->p_pos_y = 0;
	main->p_x = 0;
	main->p_y = 0;
	main->height = 0;
	main->north_t = NULL;
	main->south_t = NULL;
	main->west_t = NULL;
	main->east_t = NULL;
	main->floor = 0;
	main->roof = 0;
	main->map = NULL;
}

void	initialize_hive(t_hive *hive)
{
	int	i;

	i = 0;
	hive->main = ft_calloc(sizeof(t_main), 1);
	hive->data = ft_calloc(sizeof(t_data), 1);
	hive->vars = ft_calloc(sizeof(t_vars), 1);
	hive->b = ft_calloc(sizeof(t_brez), 1);
	hive->b->decision_v = 0;
	hive->b->delta_x = 0;
	hive->b->delta_y = 0;
	hive->b->direction = 0;
	while (i < 4)
		hive->line[i++] = 0;
	hive->angle = 0;
	hive->move = 15;
	hive->p_offset = 0;
	i = 0;
	while (i < 8)
	{
		hive->r[i] = 0;
		hive->p_c[i] = 0;
		hive->p_m[i++] = 0;
	}
}

void	initialize_mlx(t_data *img, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	img->img = mlx_new_image(vars->mlx, S_WIDTH, S_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
}
