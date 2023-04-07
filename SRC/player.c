/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:30:40 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/06 14:40:22 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * FUNCTION: (check_player_direction) checks that there would be a player.
 * 				That there would not be more than one player. And then it saves
 * 				the position of the player and its direction in the main struct.
 */
void	check_player_direction(t_main *main)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (main->map[i] != NULL)
	{
		while (main->map[i][x] != '\0')
		{
			if (main->map[i][x] == 'N' || main->map[i][x] == 'S' || \
				main->map[i][x] == 'E' || main->map[i][x] == 'W')
			{
				if (main->p_dir != '0')
					parsing_cleaning(main, NULL, MORE_THAN_ONE_PLAYER);
				main->p_dir = main->map[i][x];
				main->p_pos_x = x;
				main->p_pos_y = i;
			}
			x++;
		}
		x = 0;
		i++;
	}
	if (main->p_dir == '0')
		parsing_cleaning(main, NULL, PLAYER_DOES_NOT_EXIST);
}
