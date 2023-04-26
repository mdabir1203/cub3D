/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:32:54 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/26 21:18:59 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_horizontal(t_hive *h, int s_t_posx, int s_t_posy)
{
	double	a;
	int		offsetx;
	int		offsety;

	offsetx = h->p_c_x - s_t_posx;
	if (h->quadrant == 4 || h->quadrant == 3)
		offsety = s_t_posy + T_HEIGTH - h->p_c_y;
	else
		offsety = h->p_c_y - s_t_posy;
	if (abs((h->angle + h->p_offset) % 180) == 90)
		a = 10000000;
	else
		a  = fabs(offsety / tan(h->real_angle * M_PI / 180));
	h->c_horizontal = a / cos(h->real_angle * M_PI / 180);
	h->c_hor_x = s_t_posx + offsetx + a;
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_hor_y = h->p_c_y + offsety;
	else
		h->c_hor_y = s_t_posy;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_hor_x =  s_t_posx + offsetx - a;
}

void	rest_horizontal(t_hive *h, int s_t_posy, int step)
{
	h->c_horizontal = h->horizontal_y / sin(h->real_angle * M_PI / 180);
	if (h->quadrant == 4 || h->quadrant == 3)
		h->c_hor_y = s_t_posy + T_HEIGTH + (T_HEIGTH * step);
	else
		h->c_hor_y = s_t_posy - (T_HEIGTH * step);
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_hor_x =  h->c_hor_x - h->horizontal_x_scaling;
	else
		h->c_hor_x = h->c_hor_x + h->horizontal_x_scaling;
}

void	first_vertical(t_hive *h, int s_t_posx, int s_t_posy)
{
	double	a;
	double	b;
	int	offsety = h->p_c_y - s_t_posy;

	if (h->quadrant == 1 || h->quadrant == 4)
		a  = s_t_posx + T_WIDTH - h->p_c_x;
	else
		a = h->p_c_x - s_t_posx;
	if (abs((h->angle + h->p_offset) % 180) == 0)
		b = 10000000;
	else
		b = fabs(a * tan(h->real_angle * M_PI / 180));
	h->c_vertical = b / sin(h->real_angle * M_PI / 180);
	h->c_ver_x = s_t_posx;
	h->c_ver_y =  s_t_posy + offsety - b;
	if (h->quadrant == 1 || h->quadrant == 4)
		h->c_ver_x = s_t_posx + T_WIDTH;
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = s_t_posy + offsety + b;
}

void	rest_vertical(t_hive *h, int s_t_posx, int step)
{
	h->c_ver_x = s_t_posx + T_WIDTH * step + T_WIDTH;
	h->c_vertical = h->vertical_x / cos(h->real_angle * M_PI / 180);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = h->c_ver_y + h->vertical_y_scaling;
	else
		h->c_ver_y = h->c_ver_y - h->vertical_y_scaling;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_ver_x = s_t_posx - T_WIDTH * step;
}

int	check_horizontal_wall(t_hive *h)
{
	int	wallx;
	int	wally;
	
	wallx = (h->c_hor_x - T_WIDTH) / T_WIDTH;
	if (h->quadrant == 3 || h->quadrant == 4)
		wally = (h->c_hor_y - T_HEIGTH) / T_HEIGTH;
	else
		wally = (h->c_hor_y - T_HEIGTH) / T_HEIGTH - 1;
	if (wally >= 0 && wally < h->main->height && wallx >= 0 && wallx < (int)ft_strlen(h->main->map[wally]))
	{
		if (h->main->map[wally][wallx] == '1')
			return (1);
	}
	else
		return (2);
	return (0);
}

int	check_vertical_wall(t_hive *h)
{
	int	wallx;
	int	wally;

	if (h->quadrant == 1 || h->quadrant == 4)
		wallx = (h->c_ver_x - T_WIDTH) / T_WIDTH;
	else
		wallx = (h->c_ver_x - T_WIDTH) / T_WIDTH - 1;
	wally = (h->c_ver_y - T_HEIGTH) / T_HEIGTH;
	if (wally >= 0 && wally < h->main->height && wallx >= 0 && wallx < (int)ft_strlen(h->main->map[wally]))
	{
		if (h->main->map[wally][wallx] == '1')
			return (1);
	}
	else
		return (2);
	return (0);
}

void	decide_quodrant(t_hive *h)
{
	if (h->angle + h->p_offset < 0)
	{
		if ((h->angle + h->p_offset) % 360 >= -90)
			h->quadrant = 2;
		else
		{
			if ((h->angle + h->p_offset) % 360 <= -90 && (h->angle + h->p_offset) % 360 >= -180)
				h->quadrant = 3;
			else if ((h->angle + h->p_offset) % 360 < -180 && (h->angle + h->p_offset) % 360 >= -270)
				h->quadrant = 4;
			else
				h->quadrant = 1;
		}
	}
	else
	{
		if ((h->angle + h->p_offset) % 360 <= 90)
			h->quadrant = 1;
		else
		{
			if ((h->angle + h->p_offset) % 360 > 90 && (h->angle + h->p_offset) % 360 <= 180)
				h->quadrant = 4;
			else if ((h->angle + h->p_offset) % 360 > 180 && (h->angle + h->p_offset) % 360 <= 270)
				h->quadrant = 3;
			else
				h->quadrant = 2;
		}
	}
}

void	count_horizontal_scaling(t_hive *h)
{
	if (abs((h->angle + h->p_offset) % 180) == 90)
		h->horizontal_x_scaling = 10000000;
	else
		h->horizontal_x_scaling  =  fabs(T_HEIGTH / tan(h->real_angle * M_PI / 180));
	h->horizontal_y = T_HEIGTH;
}

void	count_vertical_scaling(t_hive *h)
{
	if (abs((h->angle + h->p_offset) % 180) == 0)
		h->vertical_y_scaling = 10000000;
	else
		h->vertical_y_scaling = fabs(tan(h->real_angle * M_PI / 180) * T_WIDTH);
	h->vertical_x = T_WIDTH;
}

double	calculate_distances_draw(t_hive *h, int ver_wall, int hor_wall, int color)
{
	double	smallest_magnitude;
	double	magnitude_horizontal_v;
	double	magnitude_vertical_v;

	smallest_magnitude = 0;
	magnitude_horizontal_v = sqrt(fabs(h->c_hor_x * h->c_hor_x - h->p_c_x * h->p_c_x) + fabs(h->c_hor_y * h->c_hor_y - h->p_c_y * h->p_c_y));
	magnitude_vertical_v = sqrt(fabs(h->c_ver_x * h->c_ver_x - h->p_c_x * h->p_c_x) + fabs(h->c_ver_y * h->c_ver_y - h->p_c_y * h->p_c_y));
	if (abs((h->angle + h->p_offset) % 180) == 90)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (abs((h->angle + h->p_offset) % 180) == 0)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (ver_wall == 2)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (hor_wall == 2)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (magnitude_horizontal_v < magnitude_vertical_v)
	{
		h->line[0] = h->p_c_x;
		h->line[1] = h->p_c_y;
		h->line[2] = h->c_hor_x;
		h->line[3] = h->c_hor_y;
		smallest_magnitude = magnitude_horizontal_v;
	}
	else
	{
		h->line[0] = h->p_c_x;
		h->line[1] = h->p_c_y;
		h->line[2] = h->c_ver_x;
		h->line[3] = h->c_ver_y;
		smallest_magnitude = magnitude_vertical_v;
	}
	draw_line(h, color);
	return (smallest_magnitude);
}

void	dda(t_hive *h, int color)
{
	int		vertical_wall;
	int		horizontal_wall;

	vertical_wall = 0;
	horizontal_wall = 0;
	h->real_angle = abs(90 - ((h->angle + h->p_offset) % 180));
	decide_quodrant(h);
	h->c_tile_pos_x = (h->p_c_x - T_WIDTH) / T_WIDTH;
	h->c_tile_pos_y = (h->p_c_y - T_WIDTH) / T_WIDTH;
	int	s_t_posx = (T_HEIGTH + (h->c_tile_pos_x  * T_HEIGTH));
	int	s_t_posy = (T_HEIGTH + (h->c_tile_pos_y  * T_HEIGTH));
	first_horizontal(h, s_t_posx, s_t_posy);
	first_vertical(h, s_t_posx, s_t_posy);
	count_horizontal_scaling(h);
	count_vertical_scaling(h);
	horizontal_wall = check_horizontal_wall(h);
	vertical_wall = check_vertical_wall(h);
	int	step = 1;
	while (horizontal_wall == 0)
	{
		if (abs((h->angle + h->p_offset) % 180) == 90)
			break;
		rest_horizontal(h, s_t_posy, step);
		horizontal_wall = check_horizontal_wall(h);
		if (horizontal_wall != 0)
			break;
		step++;
	}
	step = 1;
	while (vertical_wall == 0)
	{
		if (abs((h->angle + h->p_offset) % 180) == 0)
			break;
		rest_vertical(h, s_t_posx, step);
		vertical_wall = check_vertical_wall(h);
		if (vertical_wall != 0)
			break;
		step++;
	}
	if (vertical_wall != 0 && horizontal_wall != 0)
		h->shortest_dist_to_wall = calculate_distances_draw(h, vertical_wall, horizontal_wall, color);
}
