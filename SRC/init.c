/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:11:19 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/25 16:14:26 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * FILE (init.c) FUNCTION (initialize_main):
 * initializes all of the information in t_main struct to default state. 
 */
void	initialize_main(t_main *main)
{
	main->file_fd = -1;
	main->player_direction = '0';
	main->player_pos_x = 0;
	main->player_pos_y = 0;
	main->north_t = NULL;
	main->south_t = NULL;
	main->west_t = NULL;
	main->east_t = NULL;
	main->floor = 0;
	main->roof = 0;
	main->map = NULL;
}
