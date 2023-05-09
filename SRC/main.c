/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbas <mabbas@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/09 04:15:12 by mabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_hive *hive, int indentifier)
{
	if (indentifier == W_KEY)
	{
		hive->p_c_x = hive->p_m[0];
		hive->p_c_y = hive->p_m[1];
	}
	if (indentifier == S_KEY)
	{
		hive->p_c_x = hive->p_m[6];
		hive->p_c_y = hive->p_m[7];
	}
	if (indentifier == A_KEY)
	{
		hive->p_c_x = hive->p_m[4];
		hive->p_c_y = hive->p_m[5];
	}
	if (indentifier == D_KEY)
	{
		hive->p_c_x = hive->p_m[2];
		hive->p_c_y = hive->p_m[3];
	}
}

int	key_hook(int keycode, t_hive *hive)
{
	if (keycode == ESC_KEY)
		close_game(hive);
	if (keycode == LEFT_KEY)
		hive->angle += 5;
	else if (keycode == RIGHT_KEY)
		hive->angle -= 5;
	else
	{
		if (wall_colision_check(hive, keycode) == 0)
			move_player(hive, keycode);
	}
	return (0);
}

int	render(t_hive *h)
{
	h->data->img = mlx_new_image(h->vars->mlx, S_WIDTH, S_HEIGHT);
	h->data->addr = mlx_get_data_addr(h->data->img, &h->data->bits_per_pixel, \
	&h->data->line_length, &h->data->endian);
	draw_player(h);
	draw_2d_rays(h);
	mlx_put_image_to_window(h->vars->mlx, h->vars->win, h->data->img, 0, 0);
	mlx_destroy_image(h->vars->mlx, h->data->img);
	return (0);
}

void hooks_n_loops(t_hive *hive)
{
	hive->p_c_x = TILE + (hive->main->p_x * (TILE)) + ((TILE) / 2);
	hive->p_c_y = TILE + (hive->main->p_y * (TILE)) + ((TILE) / 2);
	play_music();
	mlx_hook(hive->vars->win, 2, (1L) << 0, &key_hook, hive);
	mlx_hook(hive->vars->win, 17, 0L, close_game, hive);
	mlx_loop_hook(hive->vars->mlx, &render, hive);
	mlx_loop(hive->vars->mlx);
}

int	main(int argc, char **argv)
{
	t_hive	*hive;
	t_main	*main;

	hive = NULL;
	hive = ft_calloc(sizeof(t_hive), 1);
	main = ft_calloc(sizeof(t_main), 1);
	initialize_main(main);
	initialize_hive(hive, main);
	check_basic_errors(main, argc, argv);
	parsing(main, argv);
	position_offset(main, hive);
	initialize_mlx(hive->data, hive->vars);
	load_assets(hive);
	hooks_n_loops(hive);
	return (0);
}
