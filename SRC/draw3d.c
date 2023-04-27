/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/04/27 19:32:55 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_hive *hive, int i)
{
	int		lineH;
	//int		lineOff;

	lineH = (32*S_HEIGHT) / hive->shortest_dist_to_wall;
	//lineOff = S_HEIGHT - (lineH>>1);
	if (lineH > S_HEIGHT)
		lineH = S_HEIGHT;
	hive->line[0] = 50 - i;
	hive->line[1] = 150;
	hive->line[2] = 50 - i;
	hive->line[3] = hive->line[1] + lineH;
	draw_line(hive, 178102255);
	hive->line[0] = 50 - i;
	hive->line[1] = 150;
	hive->line[2] = 50 - i;
	hive->line[3] = hive->line[1] - lineH;
	draw_line(hive, 178102255);
}
