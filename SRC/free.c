/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:28:17 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/21 11:40:26 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_the_main_struct(t_main *main)
{
	if (main->file_fd > 2)
		close(main->file_fd);
	if (main->north_t != NULL)
		free(main->north_t);
	if (main->south_t != NULL)
		free(main->south_t);
	if (main->west_t != NULL)
		free(main->west_t);
	if (main->east_t != NULL)
		free(main->east_t);
}
