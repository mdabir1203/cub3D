/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:33:45 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/16 17:21:35 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_map(t_main *main)
{
	int	i;

	i = 0;
	while (main->map[i] != NULL)
	{
		printf("Check_map[%d]: [%s]\n", i, main->map[i]);
		i++;
	}
}
