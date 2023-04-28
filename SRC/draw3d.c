/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/04/28 18:46:02 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_hive *h, int i, int a)
{
	double	lineH;
	double	fish_eye_compensation;
	int	x;
	//while(++i < S_HEIGHT)
		//{
	(void)i;
	x = 0;
	//lineH = fabs((32 * S_HEIGHT) / h->shortest_dist_to_wall);
	fish_eye_compensation = h->shortest_dist_to_wall * cos(i * M_PI / 180);
	printf("fish_eye: %f\n", fish_eye_compensation);
	lineH = fabs((32 * S_HEIGHT) / fish_eye_compensation);
	printf("before fisheye: %f\n", lineH);
	printf("after fisheye: %f\n", lineH);
	// if (i == 0)
	// 	lineH = fabs((32 * S_HEIGHT) / h->shortest_dist_to_wall);
	// else
	// 	lineH = fabs((32 * S_HEIGHT) / fish_eye_compensation);
	///int	lineOff = S_HEIGHT - (lineH>>1);
	printf("lineH: %f\n", lineH);
	if (lineH > S_HEIGHT)
		lineH = S_HEIGHT - 150;
	printf("S_HEIGHT: %d\n", S_HEIGHT);
	printf("int i: %d\n", i);
	printf("h->angle: %d", abs(((h->angle + h->p_offset) % 180)));
	h->line[0] = 35 + (a * 32);				//x1
	h->line[1] = (S_HEIGHT / 2) - lineH;	//y1
	h->line[2] = 35 + (a * 32);				//x2
	h->line[3] = (S_HEIGHT / 2) + lineH;	//y2
	printf("x: %d, x1: %d y1: %d, x2: %d, y2: %d\n", x, h->line[0], h->line[1], h->line[2], h->line[3]);
	while (x < 32)
	{
		h->line[1] = 0;
		h->line[3] = (S_HEIGHT / 2) - lineH;
		draw_line(h, h->main->roof);
		h->line[1] = (S_HEIGHT / 2) + lineH;
		h->line[3] = S_HEIGHT;
		draw_line(h, h->main->ground);
		h->line[0] = h->line[0] + 1;
		h->line[1] = (S_HEIGHT / 2) - lineH;
		h->line[2] = h->line[2] + 1;
		draw_line(h, h->wall_color);
		printf("x: %d, x1: %d y1: %d, x2: %d, y2: %d\n", x, h->line[0], h->line[1], h->line[2], h->line[3]);
		x++;
	}
}

