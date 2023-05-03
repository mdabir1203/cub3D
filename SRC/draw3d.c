/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/05/04 00:17:30 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_mlx_pixel_get(t_hive *h, t_texture *texture, int x, int y)
{
	char	*color;

	color = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	if (h->x_ray == true)
		return (*(uint32_t *)color);
	else
		return (*(int *)color >> 1 & 8355711);
}

int	get_start_row(double lineH)
{
	if (lineH > S_HEIGHT)
		return ((lineH - S_HEIGHT) / 2);
	return (0);
}

void	draw_vertical_line(t_hive *h, double temp_lineH)
{
	int		y1;
	int		row;
	int		column;
	int		ver_tex_line;

	y1 = h->line[1];
	row = get_start_row(temp_lineH);
	ver_tex_line = 0;
	h->texure_to_tile_ratio_x = h->wall_tex->texture_north->img_width / (double)T_WIDTH;
	h->texure_to_lineH_ratio_y = h->wall_tex->texture_north->img_height / temp_lineH;
	if (h->x_ray == true)
		ver_tex_line = fmod(h->c_hor_x, T_WIDTH);
	else
		ver_tex_line = fmod(h->c_ver_y, T_WIDTH);
	column = ver_tex_line * h->texure_to_tile_ratio_x;
	while (y1 != h->line[3])
	{
		my_mlx_pixel_put(h->data, h->line[0], y1, \
				my_mlx_pixel_get(h, h->wall_tex->texture_north, column, row * h->texure_to_lineH_ratio_y));
		y1++;
		row++;
	}
}

void	draw_3d(t_hive *h, int a, double fov)
{
	double	fish_eye_compensation;
	double	lineH;
	double	temp_lineH;

	(void)a;
	fish_eye_compensation = fabs(h->shortest_dist_to_wall * cos(fov * RADIAN));
	lineH = fabs((T_WIDTH / fish_eye_compensation) * h->p_dist_from_projection_plane);
	if (lineH > S_HEIGHT)
	{
		temp_lineH = lineH;
		lineH = S_HEIGHT;
	}
	else
		temp_lineH = lineH;
	h->line[0] = a;								//x1
	h->line[2] = a;								//x2
	h->line[1] = (S_HEIGHT / 2) - (lineH / 2);	//y1
	h->line[3] = (S_HEIGHT / 2) + (lineH / 2);	//y2
	draw_vertical_line(h, temp_lineH);
	h->line[1] = (S_HEIGHT / 2) + (lineH / 2);	//y1
	h->line[3] = S_HEIGHT;	//y2
	draw_line(h, 0x00AA00, 0);
	//put_textures(h);
}
