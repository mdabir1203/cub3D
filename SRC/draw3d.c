/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/04/30 00:43:37 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_hive *h, int a, double i, double p)
{
	double	lineH;
	
	double	fish_eye_compensation;
	int	x;
	x = 0;
	(void)a;
	fish_eye_compensation = fabs(h->shortest_dist_to_wall * cos(i * (M_PI / 180)));
	lineH = fabs((32 / fish_eye_compensation) * p);
	if (lineH > S_HEIGHT)
		lineH = S_HEIGHT;
	h->line[0] = a;								//x1
	h->line[2] = a;								//x2
	h->line[1] = (S_HEIGHT / 2) - (lineH / 2);	//y1
	h->line[3] = (S_HEIGHT / 2) + (lineH / 2);	//y2
	draw_line(h, h->wall_color);
	h->line[1] = (S_HEIGHT / 2) + (lineH / 2);	//y1
	h->line[3] = S_HEIGHT;	//y2
	draw_line(h, 0x00AA00);
}