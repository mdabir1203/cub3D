/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/06 20:19:08 by lkavalia         ###   ########.fr       */
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

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	// (void)img;
	// (void)main;
	if (keycode == 124)
		printf("Left arrow key!\n");
	if (keycode == 123)
		printf("Right arrow key!\n");
	if (keycode == W_KEY)
	{
		printf("W key!\n");
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
		close_game(vars);
	}
	printf("Hello from key_hook! %d\n", keycode);
	return (0);
}

void	mlx_f(t_data *img, t_vars *vars, t_main *main)
{
	int	i;
	int img_width;
	int img_height;
	
	img_height = 0;
	img_width = 0;
	//img->img = mlx_xpm_file_to_image(vars->mlx, D_NO, &img_width, &img_height);
	i = 0;
	// while (i < 100)
	// {
	// 	my_mlx_pixel_put(img, 0 + i, 0, 16711680);
	// 	i++;
	// }
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_hook(vars->win, 17, 0L, close_game, vars);
	mlx_loop(vars->mlx);
	(void)main;
}

void	initialize_mlx(t_data *img, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "Hello world!");
	img->img = mlx_new_image(vars->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
}

int	main(int argc, char **argv)
{
	t_main	main;
	t_data	img;
	t_vars	vars;

	initialize_main(&main);
	check_basic_errors(&main, argc, argv);
	parsing(&main, argv);
	initialize_mlx(&img, &vars);
	draw_flat_map(&main, &img);
	mlx_f(&img, &vars, &main);
	return (0);
}
