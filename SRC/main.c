/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/07 14:49:05 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_game(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	// clear_the_main_struct(main);
	exit(0);
}

int	key_hook(int keycode, t_hive *hive)
{
	if (keycode == 124)
		printf("Left arrow key!\n");
	if (keycode == 123)
		printf("Right arrow key!\n");
	if (keycode == W_KEY)
	{
		printf("W key!\n");
		mlx_clear_window(hive->vars->mlx, hive->vars->win);
		check_map(hive->main);
		//main->p_pos_y += 10;
		//draw_player(img, main->p_pos_x, main->p_pos_y);
	}
	if (keycode == 1)
		printf("S key!\n");
	if (keycode == 2)
		printf("D key!\n");
	if (keycode == 0)
		printf("A key!\n");
	if (keycode == 53)
	{
		printf("ESC key!\n");
		close_game(hive->vars);
	}
	printf("Hello from key_hook! %d\n", keycode);
	return (0);
}

void	mlx_f(t_hive *h)
{
	int	i;
	int	img_width;
	int	img_height;

	img_height = 0;
	img_width = 0;
	//img->img = mlx_xpm_file_to_image(vars->mlx, D_NO, &img_width, &img_height);
	i = 0;
	mlx_put_image_to_window(h->vars->mlx, h->vars->win, h->data->img, 0, 0);
	mlx_key_hook(h->vars->win, key_hook, h);
	mlx_hook(h->vars->win, 17, 0L, close_game, h->vars);
	mlx_loop(h->vars->mlx);
}

void	initialize_mlx(t_data *img, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "Hello world!");
	img->img = mlx_new_image(vars->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
}

void	initialize_hive(t_hive *hive, t_main *main, t_data *data, t_vars *vars)
{
	hive->main = main;
	hive->data = data;
	hive->vars = vars;
}

int	main(int argc, char **argv)
{
	t_main	main;
	t_data	data;
	t_vars	vars;
	t_hive	hive;	

	initialize_main(&main);
	initialize_hive(&hive, &main, &data, &vars);
	check_basic_errors(&main, argc, argv);
	parsing(&main, argv);
	initialize_mlx(&data, &vars);
	draw_flat_map(&main, &data);
	mlx_f(&hive);
	return (0);
}
