/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:32:54 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/04 23:21:13 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_horizontal(t_hive *h, int start_tile_pos_x, int start_tile_pos_y)
{
	double	a;
	int		offsetx;
	int		offsety;

	offsetx = h->p_c_x - start_tile_pos_x;
	if (h->quadrant == 4 || h->quadrant == 3)
		offsety = start_tile_pos_y + (T_HEIGHT) - h->p_c_y;
	else
		offsety = h->p_c_y - start_tile_pos_y;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
		a = 10000000;
	else
		a  = fabs(offsety / tan(h->real_angle * RADIAN));
	h->c_horizontal = a / cos(h->real_angle * RADIAN);
	h->c_hor_x = start_tile_pos_x + offsetx + a;
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_hor_y = h->p_c_y + offsety;
	else
		h->c_hor_y = start_tile_pos_y;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_hor_x =  start_tile_pos_x + offsetx - a;
}

void	rest_horizontal(t_hive *h, int start_tile_pos_y, int step)
{
	h->c_horizontal = h->horizontal_y / sin(h->real_angle * RADIAN);
	if (h->quadrant == 4 || h->quadrant == 3)
		h->c_hor_y = start_tile_pos_y + (T_HEIGHT) + ((T_HEIGHT) * step);
	else
		h->c_hor_y = start_tile_pos_y - ((T_HEIGHT) * step);
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_hor_x = h->c_hor_x - h->horizontal_x_scaling;
	else
		h->c_hor_x = h->c_hor_x + h->horizontal_x_scaling;
}

void	first_vertical(t_hive *h, int start_tile_pos_x, int start_tile_pos_y)
{
	double	a;
	double	b;
	int		offsety;

	offsety = h->p_c_y - start_tile_pos_y;
	if (h->quadrant == 1 || h->quadrant == 4)
		a = start_tile_pos_x + (T_WIDTH) - h->p_c_x;
	else
		a = h->p_c_x - start_tile_pos_x;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
		b = 10000000;
	else
		b = fabs(a * tan(h->real_angle * RADIAN));
	h->c_vertical = b / sin(h->real_angle * RADIAN);
	h->c_ver_x = start_tile_pos_x;
	h->c_ver_y = start_tile_pos_y + offsety - b;
	if (h->quadrant == 1 || h->quadrant == 4)
		h->c_ver_x = start_tile_pos_x + (T_WIDTH);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = start_tile_pos_y + offsety + b;
}

void	rest_vertical(t_hive *h, int start_tile_pos_x, int step)
{
	h->c_ver_x = start_tile_pos_x + (T_WIDTH) * step + (T_WIDTH);
	h->c_vertical = h->vertical_x / cos(h->real_angle * RADIAN);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = h->c_ver_y + h->vertical_y_scaling;
	else
		h->c_ver_y = h->c_ver_y - h->vertical_y_scaling;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_ver_x = start_tile_pos_x - (T_WIDTH) * step;
}

void	decide_quadrant(t_hive *h)
{
	int	angle = ((int)h->angle + h->p_offset) % 360;

	if (h->angle + h->p_offset >= 0)
	{
		if (angle < 90)
			h->quadrant = 1;
		else
		{
			if (angle >= 90 && angle < 180)
				h->quadrant = 4;
			else if (angle >= 180 && angle < 270)
				h->quadrant = 3;
			else
				h->quadrant = 2;
		}
	}
	else
	{
		if (angle > -90)
			h->quadrant = 2;
		else
		{
			if (angle <= -90 && angle > -180)
				h->quadrant = 3;
			else if (angle <= -180 && angle > -270)
				h->quadrant = 4;
			else
				h->quadrant = 1;
		}
	}
}

void	raycasting(t_hive *h)
{
	int		step;
	int		start_tile_pos_x;
	int		start_tile_pos_y;
	int		hor_hit;
	int		ver_hit;

	ver_hit = 0;
	hor_hit = 0;
	h->real_angle = fabs((double)90 - remainder(h->angle + (double)h->p_offset, (double)180));
	decide_quadrant(h);
	h->c_tile_pos_x = (h->p_c_x - T_WIDTH) / T_WIDTH;
	h->c_tile_pos_y = (h->p_c_y - T_WIDTH) / T_WIDTH;
	step = 1;
	start_tile_pos_x = (T_HEIGHT + (h->c_tile_pos_x * T_HEIGHT));
	start_tile_pos_y = (T_HEIGHT + (h->c_tile_pos_y * T_HEIGHT));
	first_horizontal(h, start_tile_pos_x, start_tile_pos_y);
	first_vertical(h, start_tile_pos_x, start_tile_pos_y);
	count_horizontal_scaling(h);
	count_vertical_scaling(h);
	hor_hit = check_horizontal_wall(h);
	ver_hit = check_vertical_wall(h);
	while (hor_hit == 0)
	{
		if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
			break ;
		rest_horizontal(h, start_tile_pos_y, step);
		hor_hit = check_horizontal_wall(h);
		step++;
	}
	step = 1;
	while (ver_hit == 0)
	{
		if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
			break ;
		rest_vertical(h, start_tile_pos_x, step);
		ver_hit = check_vertical_wall(h);
		step++;
	}
	if (ver_hit != 0 && hor_hit != 0)
		h->shortest_dist_to_wall = calculate_dist_draw(h, hor_hit, ver_hit);
}
