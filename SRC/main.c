/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/07 16:42:07 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_game(t_hive *hive)
{
	mlx_destroy_image(hive->vars->mlx, hive->data->img);
	mlx_destroy_window(hive->vars->mlx, hive->vars->win);
	clear_the_main_struct(hive->main);
	// free(hive->data);
	// free(hive->vars);
	// free(hive->main);
	// free(hive);

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
		close_game(hive);
	}
	printf("Hello from key_hook! %d\n", keycode);
	return (0);
}

void	mlx_f(t_hive *h)
{
	//img->img = mlx_xpm_file_to_image(vars->mlx, D_NO, &img_width, &img_height);
	mlx_put_image_to_window(h->vars->mlx, h->vars->win, h->data->img, 0, 0);
	mlx_key_hook(h->vars->win, key_hook, h);
	mlx_hook(h->vars->win, 17, 0L, close_game, h);
	mlx_loop(h->vars->mlx);
}

void	initialize_mlx(t_data *img, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 800, 600, "Hello world!");
	img->img = mlx_new_image(vars->mlx, 800, 600);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
}

// void	initialize_hive(t_hive *hive, t_main *main, t_data *data, t_vars *vars)
// {
// 	hive->main = main;
// 	hive->data = data;
// 	hive->vars = vars;
// }
void	initialize_hive(t_hive *hive)
{
	hive->main = ft_calloc(sizeof(t_main), 1);
	hive->data = ft_calloc(sizeof(t_data), 1);
	hive->vars = ft_calloc(sizeof(t_vars), 1);
}

int	main(int argc, char **argv)
{
	// t_main	main;
	// t_data	data;
	// t_vars	vars;
	t_hive	*hive = ft_calloc(sizeof(t_hive), 1);

	// initialize_hive(&hive, &main, &data, &vars);
	initialize_hive(hive);
	initialize_main(hive->main);
	check_basic_errors(hive->main, argc, argv);
	parsing(hive->main, argv);
	initialize_mlx(hive->data, hive->vars);
	draw_flat_map(hive->main, hive->data);
	mlx_f(hive);
	return (0);
}
