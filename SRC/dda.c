/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:32:54 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/04 00:17:14 by lkavalia         ###   ########.fr       */
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
		offsety = s_t_posy + (T_HEIGHT) - h->p_c_y;
	else
		offsety = h->p_c_y - s_t_posy;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
		a = 10000000;
	else
		a  = fabs(offsety / tan(h->real_angle * RADIAN));
	h->c_horizontal = a / cos(h->real_angle * RADIAN);
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
	h->c_horizontal = h->horizontal_y / sin(h->real_angle * RADIAN);
	if (h->quadrant == 4 || h->quadrant == 3)
		h->c_hor_y = s_t_posy + (T_HEIGHT) + ((T_HEIGHT) * step);
	else
		h->c_hor_y = s_t_posy - ((T_HEIGHT) * step);
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
		a  = s_t_posx + (T_WIDTH) - h->p_c_x;
	else
		a = h->p_c_x - s_t_posx;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
		b = 10000000;
	else
		b = fabs(a * tan(h->real_angle * RADIAN));
	h->c_vertical = b / sin(h->real_angle * RADIAN);
	h->c_ver_x = s_t_posx;
	h->c_ver_y =  s_t_posy + offsety - b;
	if (h->quadrant == 1 || h->quadrant == 4)
		h->c_ver_x = s_t_posx + (T_WIDTH);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = s_t_posy + offsety + b;
}

void	rest_vertical(t_hive *h, int s_t_posx, int step)
{
	h->c_ver_x = s_t_posx + (T_WIDTH) * step + (T_WIDTH);
	h->c_vertical = h->vertical_x / cos(h->real_angle * RADIAN);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = h->c_ver_y + h->vertical_y_scaling;
	else
		h->c_ver_y = h->c_ver_y - h->vertical_y_scaling;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_ver_x = s_t_posx - (T_WIDTH) * step;
}

int	check_horizontal_wall(t_hive *h)
{
	int	wallx;
	int	wally;

	wallx = (h->c_hor_x - T_WIDTH) / (T_WIDTH);
	if (h->quadrant == 3 || h->quadrant == 4)
		wally = (h->c_hor_y - T_HEIGHT) / (T_HEIGHT);
	else
		wally = (h->c_hor_y - T_HEIGHT) / (T_HEIGHT) - 1;
	if (wally >= 0 && wally < h->main->height && wallx >= 0 && \
		wallx < (int)ft_strlen(h->main->map[wally]))
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
		wallx = (h->c_ver_x - T_WIDTH) / (T_WIDTH);
	else
		wallx = (h->c_ver_x - T_WIDTH) / (T_WIDTH) - 1;
	wally = (h->c_ver_y - T_HEIGHT) / T_HEIGHT;
	if (wally >= 0 && wally < h->main->height && \
		wallx >= 0 && wallx < (int)ft_strlen(h->main->map[wally]))
	{
		if (h->main->map[wally][wallx] == '1')
			return (1);
	}
	else
		return (2);
	return (0);
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

void	count_horizontal_scaling(t_hive *h)
{
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
		h->horizontal_x_scaling = 10000000;
	else
		h->horizontal_x_scaling  =  fabs(T_HEIGHT / tan(h->real_angle * RADIAN));
	h->horizontal_y = T_HEIGHT;
}

void	count_vertical_scaling(t_hive *h)
{
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
		h->vertical_y_scaling = 10000000;
	else
		h->vertical_y_scaling = fabs(tan(h->real_angle * RADIAN) * T_WIDTH);
	h->vertical_x = T_WIDTH;
}

double	calculate_distances_draw(t_hive *h)
{
	double	smallest_magnitude;
	double	magnitude_horizontal_v;
	double	magnitude_vertical_v;

	smallest_magnitude = 0;
	magnitude_horizontal_v = sqrt(fabs(pow(h->c_hor_x - h->p_c_x, 2)) + fabs(pow(h->c_hor_y - h->p_c_y, 2)));
	magnitude_vertical_v = sqrt(fabs(pow(h->c_ver_x - h->p_c_x, 2)) + fabs(pow(h->c_ver_y - h->p_c_y, 2)));
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (h->main->v_hit == 2)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (h->main->h_hit == 2)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (magnitude_horizontal_v < magnitude_vertical_v)
	{
		h->line[0] = h->p_c_x;
		h->line[1] = h->p_c_y;
		h->line[2] = h->c_hor_x;
		h->line[3] = h->c_hor_y;
		//h->wall_color = 178102255;
		smallest_magnitude = magnitude_horizontal_v;
		h->x_ray = true;
	}
	else
	{
		h->line[0] = h->p_c_x;
		h->line[1] = h->p_c_y;
		h->line[2] = h->c_ver_x;
		h->line[3] = h->c_ver_y;
		//h->wall_color = 0x00FFFF;
		smallest_magnitude = magnitude_vertical_v;
		h->x_ray = false;
	}
	return (smallest_magnitude);
}

void	dda(t_hive *h)
{
	h->main->v_hit = 0;
	h->main->h_hit = 0;
	h->real_angle = fabs((double)90 - remainder(h->angle + (double)h->p_offset, (double)180));
	decide_quadrant(h);
	h->c_tile_pos_x = (h->p_c_x - T_WIDTH) / T_WIDTH;
	h->c_tile_pos_y = (h->p_c_y - T_WIDTH) / T_WIDTH; 
	int	s_t_posx = (T_HEIGHT + (h->c_tile_pos_x  * T_HEIGHT));
	int	s_t_posy = (T_HEIGHT + (h->c_tile_pos_y  * T_HEIGHT));
	first_horizontal(h, s_t_posx, s_t_posy);
	first_vertical(h, s_t_posx, s_t_posy);
	count_horizontal_scaling(h);
	count_vertical_scaling(h);
	h->main->h_hit = check_horizontal_wall(h);
	h->main->v_hit = check_vertical_wall(h);
	int	step = 1;
	while (h->main->h_hit == 0)
	{
		if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
			break;
		rest_horizontal(h, s_t_posy, step);
		h->main->h_hit = check_horizontal_wall(h);
		if (h->main->h_hit != 0)
			break;
		step++;
	}
	step = 1;
	while (h->main->v_hit == 0)
	{
		if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
			break;
		rest_vertical(h, s_t_posx, step);
		h->main->v_hit = check_vertical_wall(h);
		if (h->main->v_hit != 0)
			break;
		step++;
	}
	if (h->main->v_hit != 0 && h->main->h_hit != 0)
		h->shortest_dist_to_wall = calculate_distances_draw(h);
}
