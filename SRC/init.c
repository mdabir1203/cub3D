/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:11:19 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/20 19:01:45 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * FILE (init.c) FUNCTION (initialize_main):
 * initializes all of the information in t_main struct to default state. 
 */
void	initialize_main(t_main *main)
{
	int	i;

	i = 0;
	main->file_fd = -1;
	main->north_t = NULL;
	main->south_t = NULL;
	main->west_t = NULL;
	main->east_t = NULL;
	while (i < 3)
	{
		main->f[i] = -1;
		main->c[i] = -1;
		i++;
	}
}
