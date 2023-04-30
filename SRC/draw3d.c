/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/04/30 19:36:45 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_textures(t_hive *hive)
{
	char	*addr;
	t_img	*img_n = hive->main->north_t;
	t_img	*img_s = hive->main->south_t;
	t_img	*img_w = hive->main->west_t;
	t_img	*img_e = hive->main->east_t;
	//printf("%s", hive->main->north_t);
	
	if (hive->main->h_hit > 0)
	{
		if (hive->c_hor_y > hive->p_c_y)
		{
			addr = img_n->data + (0 % hive->data->height * \
				hive->data->line_length + 0 * (hive->data->bits_per_pixel / 8));
			draw_line(hive, *(unsigned int *)addr, 1);
		}
		else
		{
			addr = img_s->data + (0 % hive->data->height * \
				hive->data->line_length + 0 * (hive->data->bits_per_pixel / 8));
			draw_line(hive, *(unsigned int *)addr/ 2 & 0b011111110111111101111111, 1);
		}
	}
	else
	{
		if (hive->c_ver_x > hive->p_c_x)
		{
			addr = img_e->data + (0 % hive->data->height * \
				hive->data->line_length + 0 * (hive->data->bits_per_pixel / 8));
			draw_line(hive, *(unsigned int *)addr, 1);
		}
		else
		{
			addr = img_w->data + (0 % hive->data->height * \
				hive->data->line_length + 0 * (hive->data->bits_per_pixel / 8));
			draw_line(hive, *(unsigned int *)addr/ 2 & 0b011111110111111101111111, 1);
		}
	}
}

void	draw_3d(t_hive *h, int a, double fov)
{
	double	fish_eye_compensation;
	double	lineH;

	(void)a;
	fish_eye_compensation = fabs(h->shortest_dist_to_wall * cos(fov * RADIAN));
	lineH = fabs((32 / fish_eye_compensation) * h->p_dist_from_projection_plane);
	if (lineH > S_HEIGHT)
		lineH = S_HEIGHT;
	h->line[0] = a;								//x1
	h->line[2] = a;								//x2
	h->line[1] = (S_HEIGHT / 2) - (lineH / 2);	//y1
	h->line[3] = (S_HEIGHT / 2) + (lineH / 2);	//y2
	//draw_line(h, h->wall_color);
	put_textures(h);
	h->line[1] = (S_HEIGHT / 2) + (lineH / 2);	//y1
	h->line[3] = S_HEIGHT;	//y2
	draw_line(h, 0x00AA00, 0);
	//put_textures(h);
}
