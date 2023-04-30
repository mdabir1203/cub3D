/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:01:30 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/30 19:40:50 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_placement_decider(t_hive *h, int x, int color)
{
	if (x == 1)
	{
		my_mlx_pixel_put(h->data, h->line[0], h->line[1], color);
		if (h->b->decision_v < 0)
			h->b->decision_v = h->b->decision_v + (2 * h->b->delta_y);
		else
		{
			h->b->decision_v = h->b->decision_v + (2 * h->b->delta_y) \
					- (2 * h->b->delta_x);
			h->line[1] = h->line[1] + h->b->direction;
		}
	}
	else
	{
		my_mlx_pixel_put(h->data, h->line[0], h->line[1], color);
		if (h->b->decision_v < 0)
			h->b->decision_v = h->b->decision_v + (2 * h->b->delta_x);
		else
		{
			h->b->decision_v = h->b->decision_v + (2 * h->b->delta_x) \
													- (2 * h->b->delta_y);
			h->line[0] = h->line[0] + h->b->direction;
		}
	}
}

static void	draw_low_slope(t_hive *h, int color, int texture)
{
	h->b->direction = 1;
	h->b->delta_x = h->line[2] - h->line[0];
	h->b->delta_y = h->line[3] - h->line[1];
	if (h->b->delta_y < 0)
	{
		h->b->delta_y = -1 * h->b->delta_y;
		h->b->direction = -1;
	}
	h->b->decision_v = (2 * h->b->delta_y) - h->b->delta_x;
	while (h->line[0] <= h->line[2])
	{
		if (texture)
		{
			addr = get color from texture;
			color = *(unsigned int *)addr;
		}
		// 	load_xpm(h);
		pixel_placement_decider(h, 1, color);
		h->line[0]++;
	}
}

static void	draw_high_slope(t_hive *h, int color, int is_texture)
{
	(void) is_texture;
	h->b->direction = 1;
	h->b->delta_x = h->line[2] - h->line[0];
	h->b->delta_y = h->line[3] - h->line[1];
	if (h->b->delta_x < 0)
	{
		h->b->delta_x = -1 * h->b->delta_x;
		h->b->direction = -1;
	}
	h->b->decision_v = (2 * h->b->delta_x) - h->b->delta_y;
	while (h->line[1] <= h->line[3])
	{
		//if (is_texture)
			//load_xpm(h);
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

void	draw_line(t_hive *h, int color, void *texture)
{
	if (fabs((double)h->line[3] - (double)h->line[1]) <= \
						fabs((double)h->line[2] - (double)h->line[0]))
	{
		if (h->line[0] > h->line[2])
		{
			rotate(h);
			draw_low_slope(h, color, texture);
		}
		else
			draw_low_slope(h, color, texture);
	}
	else
	{
		if (h->line[1] > h->line[3])
		{
			rotate(h);
			draw_high_slope(h, color, texture);
		}
		else
			draw_high_slope(h, color, texture);
	}
}
