/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/04/27 18:32:45 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_hive *hive)
{
	int		lineH;
	int		i = -1;

	while(++i < S_HEIGHT)
	{
		lineH = (32*S_HEIGHT) / hive->shortest_dist_to_wall;
		if (lineH > S_HEIGHT)
			lineH = S_HEIGHT;
		hive->line[0] = 200;
		hive->line[1] = 200;
		hive->line[2] = 200;
		hive->line[3] = hive->line[1] - lineH;
		draw_line(hive, 178102255);
	}
}