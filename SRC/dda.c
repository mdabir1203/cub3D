/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:01:30 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/16 16:27:31 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	dda_line(t_hive *h)
// {
// 	int	i;
// 	int delta_x;
// 	int	delta_y;
// 	float x_1;
// 	float y_1;

// 	i = 0;
// 	x_1 = h->x1;
// 	y_1 = h->y1;
// 	delta_x = h->x2 - h->x1;
// 	delta_y = h->y2 - h->y1;
// 	if (abs(delta_x) > abs(delta_y))
// 		h->steps = abs(delta_x);
// 	else
// 		h->steps = abs(delta_y);
// 	h->x_inc = (float)delta_x / (float)h->steps;
// 	h->y_inc = (float)delta_y / (float)h->steps;
// 	printf("steps: %d\n", h->steps);
// 	printf("x_inc: %f\n", h->x_inc);
// 	printf("y_inc: %f\n", h->y_inc);
// 	while (i < h->steps)
// 	{
// 		x_1 += h->x_inc;
// 		y_1 += h->y_inc;
// 		my_mlx_pixel_put(h->data, (int)round(x_1), (int)round(y_1), 16711680);
// 		i++;
// 	}
// }

void	pixel_placement_decider(t_hive *h, int x, int color)
{
	if (x == 1)
	{
		my_mlx_pixel_put(h->data, h->line[0], h->line[1], color);
		if (h->decision_v < 0)
			h->decision_v = h->decision_v + (2 * h->delta_y);
		else
		{
			h->decision_v = h->decision_v + (2 * h->delta_y) \
					- (2 * h->delta_x);
			h->line[1] = h->line[1] + h->direction;
		}
	}
	else
	{
		my_mlx_pixel_put(h->data, h->line[0], h->line[1], color);
		if (h->decision_v < 0)
			h->decision_v = h->decision_v + (2 * h->delta_x);
		else
		{
			h->decision_v = h->decision_v + (2 * h->delta_x) \
													- (2 * h->delta_y);
			h->line[0] = h->line[0] + h->direction;
		}
	}
}

static void	draw_low_slope(t_hive *h, int color)
{
	h->direction = 1;
	h->delta_x = h->line[2] - h->line[0];
	h->delta_y = h->line[3] - h->line[1];
	if (h->delta_y < 0)
	{
		h->delta_y = -1 * h->delta_y;
		h->direction = -1;
	}
	h->decision_v = (2 * h->delta_y) - h->delta_x;
	while (h->line[0] <= h->line[2])
	{
		pixel_placement_decider(h, 1, color);
		h->line[0]++;
	}
}

static void	draw_high_slope(t_hive *h, int color)
{
	h->direction = 1;
	h->delta_x = h->line[2] - h->line[0];
	h->delta_y = h->line[3] - h->line[1];
	if (h->delta_x < 0)
	{
		h->delta_x = -1 * h->delta_x;
		h->direction = -1;
	}
	h->decision_v = (2 * h->delta_x) - h->delta_y;
	while (h->line[1] <= h->line[3])
	{
		pixel_placement_decider(h, 0, color);
		h->line[1]++;
	}
}

static void	rotate(t_hive *h)
{
	int	temp_x;
	int	temp_y;

	temp_x = h->line[0];
	temp_y = h->line[1];
	h->line[0] = h->line[2];
	h->line[2] = temp_x;
	h->line[1] = h->line[3];
	h->line[3] = temp_y;
}

void 	draw_line(t_hive *h, int color)
{
	if (fabs((double)h->line[3] - (double)h->line[1]) <= \
						fabs((double)h->line[2] - (double)h->line[0]))
	{
		if (h->line[0] > h->line[2])
		{
			rotate(h);
			draw_low_slope(h, color);
		}
		else
			draw_low_slope(h, color);
	}
	else
	{
		if (h->line[1] > h->line[3])
		{
			rotate(h);
			draw_high_slope(h, color);
		}
		else
			draw_high_slope(h, color);
	}
}
