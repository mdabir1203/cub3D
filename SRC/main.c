/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/27 11:07:00 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < S_WIDTH && y < S_HEIGHT && x > 0 && y > 0)
	{
		dst = data->addr + (y * data->line_length + x * \
												(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_game(t_hive *hive)
{
	//mlx_destroy_image(hive->vars->mlx, hive->data->img);
	mlx_destroy_window(hive->vars->mlx, hive->vars->win);
	clear_the_main_struct(hive->main);
	// free(hive->data);
	// free(hive->vars);
	// free(hive->main);
	// free(hive);

	exit(0);
}

void	move_player(t_hive *h, int indentifier)
{
	if (indentifier == W_KEY)
	{
		h->p_c_x = h->p_m[0];
		h->p_c_y = h->p_m[1];
	}
	if (indentifier == S_KEY)
	{
		h->p_c_x = h->p_m[6];
		h->p_c_y = h->p_m[7];
	}
	if (indentifier == A_KEY)
	{
		h->p_c_x = h->p_m[4];
		h->p_c_y = h->p_m[5];
	}
	if (indentifier == D_KEY)
	{
		h->p_c_x = h->p_m[2];
		h->p_c_y = h->p_m[3];
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
		move_player(hive, keycode);
	return (0);
}

void	player_rotation(t_hive *h, char indentifier, int offset)
{
	double	s;
	double	c;	
	int		tmp_x;

	s = sin((h->angle + offset) * M_PI / 180);
	c = cos((h->angle + offset) * M_PI / 180);
	if (indentifier == 'r')
	{
		tmp_x = h->r[0];
		h->r[0] = ((h->r[0] - h->p_c_x) * c - (h->r[1] - h->p_c_y) * s) + h->p_c_x;
		h->r[1] = ((tmp_x - h->p_c_x) * s + (h->r[1] - h->p_c_y) * c) + h->p_c_y;
		tmp_x = h->r[2];
		h->r[2] = ((h->r[2] - h->p_c_x) * c - (h->r[3] - h->p_c_y) * s) + h->p_c_x;
		h->r[3] = ((tmp_x - h->p_c_x) * s + (h->r[3] - h->p_c_y) * c) + h->p_c_y;
		tmp_x = h->r[4];
		h->r[4] = ((h->r[4] - h->p_c_x) * c - (h->r[5] - h->p_c_y) * s) + h->p_c_x;
		h->r[5] = ((tmp_x - h->p_c_x) * s + (h->r[5] - h->p_c_y) * c) + h->p_c_y;
		tmp_x = h->r[6];
		h->r[6] = ((h->r[6] - h->p_c_x) * c - (h->r[7] - h->p_c_y) * s) + h->p_c_x;
		h->r[7] = ((tmp_x - h->p_c_x) * s + (h->r[7] - h->p_c_y) * c) + h->p_c_y;
		return ;
	}
	tmp_x = h->p_c[0];
	h->p_c[0] = ((h->p_c[0] - h->p_c_x) * c - (h->p_c[1] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[1] = ((tmp_x - h->p_c_x) * s + (h->p_c[1] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->p_c[2];
	h->p_c[2] = ((h->p_c[2] - h->p_c_x) * c - (h->p_c[3] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[3] = ((tmp_x - h->p_c_x) * s + (h->p_c[3] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->p_c[4];
	h->p_c[4] = ((h->p_c[4] - h->p_c_x) * c - (h->p_c[5] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[5] = ((tmp_x - h->p_c_x) * s + (h->p_c[5] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->p_c[6];
	h->p_c[6] = ((h->p_c[6] - h->p_c_x) * c - (h->p_c[7] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[7] = ((tmp_x - h->p_c_x) * s + (h->p_c[7] - h->p_c_y) * c) + h->p_c_y;
}

void	draw_2d_rays(t_hive *h)
{
	int i = -30;
	
	h->angle = h->angle - 30;
	while (i < 0)
	{
		h->angle++;
		dda(h, 0xFFFF00);
		i++;
	}
	dda(h, 0x00FF00);
	while (i < 30)
	{
		h->angle++;
		dda(h, 0xFFFF00);
		i++;
	}
	h->angle -= 30;
}

int	render(t_hive *h)
{
	int x;
	int y;
	x = 0;
	y = 0;
	h->data->img = mlx_new_image(h->vars->mlx, S_WIDTH, S_HEIGHT);
	h->data->addr = mlx_get_data_addr(h->data->img, &h->data->bits_per_pixel, \
	&h->data->line_length, &h->data->endian);
	draw_flat_map(h->main, h->data);
	draw_2d_rays(h);
	draw_player(h, h->data);
	draw_3d(h);
	while (x++ < S_WIDTH || y++ < S_HEIGHT)
		my_mlx_pixel_put(h->data, x, y, 178024024);
	mlx_put_image_to_window(h->vars->mlx, h->vars->win, h->data->img, 0, 0);
	mlx_destroy_image(h->vars->mlx, h->data->img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_hive	*hive;

	hive = ft_calloc(sizeof(t_hive), 1);
	initialize_hive(hive);
	initialize_main(hive->main);
	check_basic_errors(hive->main, argc, argv);
	parsing(hive->main, argv);
	initialize_mlx(hive->data, hive->vars);
	hive->p_c_x = T_WIDTH + (hive->main->p_x * T_WIDTH) + (T_WIDTH / 2);
	hive->p_c_y = T_HEIGHT + (hive->main->p_y * T_HEIGHT) + (T_HEIGHT / 2);
	hive->c_tile_pos_x = hive->main->p_x;
	hive->c_tile_pos_y = hive->main->p_y;
	mlx_hook(hive->vars->win, 2, 1L<<0, &key_hook, hive);
	mlx_hook(hive->vars->win, 17, 0L, close_game, hive);
	mlx_loop_hook(hive->vars->mlx, &render, hive);
	mlx_loop(hive->vars->mlx);
	return (0);
}
