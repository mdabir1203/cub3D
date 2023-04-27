/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:54:45 by rehernan          #+#    #+#             */
/*   Updated: 2023/04/27 10:43:32 by rehernan         ###   ########.fr       */
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
		draw_line(hive, 178102255);
	}
}