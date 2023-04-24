/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:32:54 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/24 19:27:13 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	check_first_wall(t_hive *h, int len, int hor_or_ver)
// {
// 	int	wallx = 0;
// 	int	wally = 0;

// 	if (hor_or_ver == 0)
// 	{
// 		wallx = (h->f_int_x - T_HEIGTH) / T_HEIGTH;
// 		wally = (h->p_c_y - len - T_WIDTH) / T_WIDTH - 1;
// 		printf("wallx: %d wall[y]: %d\n", wallx, wally);
// 		printf("check1: [%s]\n", h->main->map[wally]);
// 		printf("check2: [%c]\n", h->main->map[wally][wallx]);
// 		if (h->main->map[wally][wallx] == '1')
// 		{
// 			h->line[0] = h->p_c_x;
// 			h->line[1] = h->p_c_y;
// 			h->line[2] = h->f_int_x;
// 			h->line[3] = h->p_c_y - len;
// 			draw_line(h, 0x00FF00);
// 		}
// 	}
// }

// void	first_horizontal(t_hive *h, int s_t_posx, int s_t_posy)
// {
// 	int offsetx = 0;
// 	offsetx = h->p_c_x - s_t_posx;
// 	int	offsety = 0;
// 	offsety = h->p_c_y - s_t_posy;
	
// 	double	a  = (h->p_c_x - h->p_c_x) * cos(h->angle * M_PI / 180) - (s_t_posy - h->p_c_y) * sin(h->angle * M_PI / 180) + h->p_c_x;
// 	//((h->r[2] - h->p_c_x) * c - (h->r[3] - h->p_c_y) * s) + h->p_c_x
// 	my_mlx_pixel_put(h->data, a, s_t_posy, 0x00FF00);
// 	printf("a: %f\n", a);
// 	//h->c_horizontal = a / cos(((90 - h->angle)) * M_PI / 180);
// 	//h->f_int_x =  s_t_posx + offsetx + a;
// 	//h->c_hor_x = h->f_int_x;
// 	//h->c_hor_y = s_t_posy;
// }

// void	first_vertical(t_hive *h, int s_t_posx, int s_t_posy)
// {
// 	int offsetx = h->p_c_x - s_t_posx;
// 	int	offsety = h->p_c_y - s_t_posy;
// 	(void)offsetx;
// 	double	a = s_t_posx + T_WIDTH -h->p_c_x;
// 	double	b = a * tan(((90 - h->angle)) * M_PI / 180);
// 	h->c_vertical = b / sin((90 - h->angle) * M_PI / 180);
// 	h->f_int_y =  s_t_posy + offsety + -b;
// 	h->c_ver_x = s_t_posx + T_WIDTH;
// 	h->c_ver_y = h->f_int_y;
// }

void	first_horizontal(t_hive *h, int s_t_posx, int s_t_posy)
{
	int		offsetx = h->p_c_x - s_t_posx;
	int		offsety;
	int		real_angle = abs(90 - (h->angle % 180));
	double	a;

	if (h->quadrant == 4 || h->quadrant == 3)
		offsety = s_t_posy + T_HEIGTH - h->p_c_y;
	else
		offsety = h->p_c_y - s_t_posy;
	if (abs(h->angle % 180) == 90)
		a = 10000000;
	else
		a  = fabs(offsety / tan(real_angle * M_PI / 180));
	h->c_horizontal = a / cos(real_angle * M_PI / 180);
	h->c_hor_x = s_t_posx + offsetx + a;
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_hor_y = h->p_c_y + offsety;
	else
		h->c_hor_y = s_t_posy;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_hor_x =  s_t_posx + offsetx - a;
	my_mlx_pixel_put(h->data, h->c_hor_x, h->c_hor_y, 0x00FF00);
}

void	rest_horizontal(t_hive *h, int s_t_posx, int s_t_posy, int step)
{
	(void)s_t_posx;
	int real_angle = abs(90 - (h->angle % 180));

	h->c_horizontal = h->horizontal_y / sin(real_angle * M_PI / 180);
	if (h->quadrant == 4 || h->quadrant == 3)
		h->c_hor_y = s_t_posy + T_HEIGTH + (T_HEIGTH * step);
	else
		h->c_hor_y = s_t_posy - (T_HEIGTH * step);
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_hor_x =  h->c_hor_x - h->horizontal_x_scaling;
	else
		h->c_hor_x = h->c_hor_x + h->horizontal_x_scaling;
	my_mlx_pixel_put(h->data, h->c_hor_x, h->c_hor_y, 0x00FF00);
}

void	first_vertical(t_hive *h, int s_t_posx, int s_t_posy)
{
	int	offsety = h->p_c_y - s_t_posy;
	int real_angle = abs(90 - (h->angle % 180));
	double	a;
	double	b;

	if (h->quadrant == 1 || h->quadrant == 4)
		a  = s_t_posx + T_WIDTH - h->p_c_x;
	else
		a = h->p_c_x - s_t_posx;
	if (abs(h->angle % 180) == 0)
		b = 10000000;
	else
		b = fabs(a * tan(real_angle * M_PI / 180));
	h->c_vertical = b / sin(real_angle * M_PI / 180);
	h->c_ver_x = s_t_posx;
	h->c_ver_y =  s_t_posy + offsety - b;
	if (h->quadrant == 1 || h->quadrant == 4)
		h->c_ver_x = s_t_posx + T_WIDTH;
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = s_t_posy + offsety + b;
	printf("---ver_x: %f\n", h->c_ver_x);
	printf("---ver_y: %f\n", h->c_ver_y);
	my_mlx_pixel_put(h->data, h->c_ver_x, h->c_ver_y, 0x00FFFF);
}

void	rest_vertical(t_hive *h, int s_t_posx, int s_t_posy, int step)
{
	(void)s_t_posy;
	(void)s_t_posx;
	int real_angle = abs(90 - (h->angle % 180));
	h->c_ver_x = s_t_posx + T_WIDTH * step + T_WIDTH;
	h->c_vertical = h->vertical_x / cos(real_angle * M_PI / 180);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->c_ver_y = h->c_ver_y + h->vertical_y_scaling;
	else
		h->c_ver_y = h->c_ver_y - h->vertical_y_scaling;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->c_ver_x = s_t_posx - T_WIDTH * step;
	my_mlx_pixel_put(h->data, h->c_ver_x, h->c_ver_y, 0xFFFFFF);
}

int	check_horizontal_wall(t_hive *h, int step)
{
	int	wallx;
	int	wally;

	printf("Checking horizontal wall %d ______________\n", step);
	
	wallx = (h->c_hor_x - T_WIDTH) / T_WIDTH;
	if (h->quadrant == 3 || h->quadrant == 4)
		wally = (h->c_hor_y - T_HEIGTH) / T_HEIGTH;
	else
		wally = (h->c_hor_y - T_HEIGTH) / T_HEIGTH - 1;
	printf("step %d\n", step);
	printf("wallx: %d\n", wallx);
	printf("wally: %d\n", wally);
	if (wally >= 0 && wally < h->main->height && wallx >= 0 && wallx < (int)ft_strlen(h->main->map[wally]))
	{
		//printf("check wallx %d: [%c]\n", wallx, h->main->map[wally][wallx]);
		if (h->main->map[wally][wallx] == '1')
		{
			printf(RED"WALL horizontal!\n"B);
			return (1);
		}
	}
	else
		return (2);
	return (0);
}

int	check_vertical_wall(t_hive *h, int step)
{
	int	wallx;
	int	wally;

	printf("Checking vertical wall: %d ______________\n", step);
	printf("h->c_ver_x: %f\n", h->c_ver_x);
	printf("h->c_ver_y: %f\n", h->c_ver_y);
	if (h->quadrant == 1 || h->quadrant == 4)
		wallx = (h->c_ver_x - T_WIDTH) / T_WIDTH;
	else
		wallx = (h->c_ver_x - T_WIDTH) / T_WIDTH - 1;
	wally = (h->c_ver_y - T_HEIGTH) / T_HEIGTH;
	printf("check wally %d\n", wally);
	printf("check wallx %d\n", wallx);
	if (wally >= 0 && wally < h->main->height && wallx >= 0 && wallx < (int)ft_strlen(h->main->map[wally]))
	{
		//printf("check wallx %d: [%c]\n", wallx, h->main->map[wally][wallx]);
		if (h->main->map[wally][wallx] == '1')
		{
			printf(RED"WALL vertical!\n"B);
			return (1);
		}
	}
	else
		return (2);
	return (0);
}

void	decide_quodrant(t_hive *h)
{
	if (h->angle < 0)
	{
		if (h->angle % 360 >= -90)
			h->quadrant = 2;
		else
		{
			if (h->angle % 360 <= -90 && h->angle % 360 >= -180)
				h->quadrant = 3;
			else if (h->angle % 360 < -180 && h->angle % 360 >= -270)
				h->quadrant = 4;
			else
				h->quadrant = 1;
		}
	}
	else
	{
		if (h->angle % 360 <= 90)
			h->quadrant = 1;
		else
		{
			if (h->angle % 360 > 90 && h->angle % 360 <= 180)
				h->quadrant = 4;
			else if (h->angle % 360 > 180 && h->angle % 360 <= 270)
				h->quadrant = 3;
			else
				h->quadrant = 2;
		}
	}
}

void	count_horizontal_scaling(t_hive *h)
{
	int real_angle = abs(90 - (h->angle % 180));
	if (abs(h->angle % 180) == 90)
		h->horizontal_x_scaling = 10000000;
	else
		h->horizontal_x_scaling  =  fabs(T_HEIGTH / tan(real_angle * M_PI / 180));
	h->horizontal_y = T_HEIGTH;
}

void	count_vertical_scaling(t_hive *h)
{
	int real_angle = abs(90 - (h->angle % 180));
	if (abs(h->angle % 180) == 0)
		h->vertical_y_scaling = 10000000;
	else
		h->vertical_y_scaling = fabs(tan(real_angle * M_PI / 180) * T_WIDTH);
	h->vertical_x = T_WIDTH;
}

void	calculate_distances_draw(t_hive *h, int ver_wall, int hor_wall)
{
	double	magnitude_horizontal_v;
	double	magnitude_vertical_v;

	magnitude_horizontal_v = sqrt(fabs(h->c_hor_x * h->c_hor_x - h->p_c_x * h->p_c_x) + fabs(h->c_hor_y * h->c_hor_y - h->p_c_y * h->p_c_y));
	magnitude_vertical_v = sqrt(fabs(h->c_ver_x * h->c_ver_x - h->p_c_x * h->p_c_x) + fabs(h->c_ver_y * h->c_ver_y - h->p_c_y * h->p_c_y));
	if (abs(h->angle % 180) == 90)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (abs(h->angle % 180) == 0)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (ver_wall == 2)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (hor_wall == 2)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	printf("magnitude_horizontal: %f\n", magnitude_horizontal_v);
	printf("magnitude_vertical: %f\n", magnitude_vertical_v);
	if (magnitude_horizontal_v < magnitude_vertical_v)
	{
		h->line[0] = h->p_c_x;
		h->line[1] = h->p_c_y;
		h->line[2] = h->c_hor_x;
		h->line[3] = h->c_hor_y;
	}
	else
	{
		h->line[0] = h->p_c_x;
		h->line[1] = h->p_c_y;
		h->line[2] = h->c_ver_x;
		h->line[3] = h->c_ver_y;
	}
	draw_line(h, 0xFFFF00);
}

void	dda(t_hive *h)
{
	int	horizontal_wall;
	int	vertical_wall;

	horizontal_wall = 0;
	vertical_wall = 0;
	decide_quodrant(h);
	printf("angle: %d quodrant: %d\n", h->angle, h->quadrant);
	h->c_tile_pos_x = (h->p_c_x - T_WIDTH) / T_WIDTH;
	h->c_tile_pos_y = (h->p_c_y - T_WIDTH) / T_WIDTH;
	int	s_t_posx = (T_HEIGTH + (h->c_tile_pos_x  * T_HEIGTH));
	int	s_t_posy = (T_HEIGTH + (h->c_tile_pos_y  * T_HEIGTH));
	printf("s_t_posx: %d s_t_posy: %d\n", s_t_posx, s_t_posy);
	first_horizontal(h, s_t_posx, s_t_posy);
	first_vertical(h, s_t_posx, s_t_posy);
	count_horizontal_scaling(h);
	count_vertical_scaling(h);
	horizontal_wall = check_horizontal_wall(h, 0);
	vertical_wall = check_vertical_wall(h, 0);
	int	step = 1;
	while (horizontal_wall == 0)
	{
		if (abs(h->angle % 180) == 90)
		{
			printf("hello horizontal impossible wall!\n");
			break;
		}
		rest_horizontal(h, s_t_posx, s_t_posy, step);
		horizontal_wall = check_horizontal_wall(h, step);
		if (horizontal_wall != 0)
		{
			printf(YELL"found horizontal wall !\n"B);
			break;
		}
		step++;
	}
	step = 1;
	while (vertical_wall == 0)
	{
		if (abs(h->angle % 180) == 0)
		{
			printf("hello vertical impossible wall!\n");
			break;
		}
		rest_vertical(h, s_t_posx, s_t_posy, step);
		vertical_wall = check_vertical_wall(h, step);
		if (vertical_wall != 0)
		{
			printf(YELL"found vertical wall !\n"B);
			break;
		}
		step++;
	}
	if (vertical_wall != 0 && horizontal_wall != 0)
	{
		printf("I have found both walls\n");
		calculate_distances_draw(h, vertical_wall, horizontal_wall);
	}
	printf("################-------\n");
}
