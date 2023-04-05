/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/04 18:42:04 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//void	

void	draw_tile(t_data *img, int start_x, int start_y, char tile)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (tile == '1')
	{
		while (y < T_HEIGTH)
		{
			while (x < T_WIDTH)
				my_mlx_pixel_put(img, start_x + x++, start_y + y, 16711680);
			x = 0;
			y++;
		}
		return ;
	}
	while (y < T_HEIGTH - 1)
	{
		while (x < T_WIDTH - 1)
			my_mlx_pixel_put(img, start_x + x++, start_y + y, 8421504);
		x = 0;
		y++;
	}
}

void	draw_player(t_data *img, int x_p, int y_p)
{
	int	x;
	int	y;
	int	p_start_x;
	int	p_start_y;

	x = 0;
	y = 0;
	p_start_x = 30 + (x_p * T_WIDTH) + 9;
	p_start_y = 30 + (y_p * T_HEIGTH) + 9;
	while (y < 10)
	{
		while (x < 10)
			my_mlx_pixel_put(img, p_start_x + x++, p_start_y + y, 3139839);
		x = 0;
		y++;
	}
}

void	draw_flat_map(t_main *main, t_data *img)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	x = 0;
	y = 0;
	start_x = 30;
	start_y = 30;
	while (main->map[y] != NULL)
	{
		while (main->map[y][x] != '\0')
		{
			if (main->map[y][x] == '1' || main->map[y][x] == '0')
				draw_tile(img, start_x, start_y, main->map[y][x]);
			x++;
			start_x += T_WIDTH;
		}
		y++;
		start_y += T_HEIGTH;
		x = 0;
		start_x = 30;
	}
	draw_player(img, main->p_pos_x, main->p_pos_y);
}
