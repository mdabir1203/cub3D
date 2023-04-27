/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/27 10:07:44 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_data *img, int start_x, int start_y, char tile)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (tile == '1')
	{
		while (y <= T_HEIGHT)
		{
			while (x <= T_WIDTH)
				my_mlx_pixel_put(img, start_x + x++, start_y + y, 16711680);
			x = 0;
			y++;
		}
		return ;
	}
	x = 1;
	y = 1;
	while (y < T_HEIGHT)
	{
		while (x < T_WIDTH)
			my_mlx_pixel_put(img, start_x + x++, start_y + y, 8421504);
		x = 1;
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
	start_x = T_WIDTH;
	start_y = T_HEIGHT;
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
		start_y += T_HEIGHT;
		x = 0;
		start_x = T_WIDTH;
	}
}
