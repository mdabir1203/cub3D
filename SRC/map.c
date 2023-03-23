/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:29:41 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/23 18:39:59 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_for_map_start(char *buffer, t_main *main)
{
	int	i;

	i = 0;
	(void)main;
	while (buffer[i] != '\0' && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	if (buffer[i] != '\0' && (buffer[i] == '0' || buffer[i] == '1'))
		return (true);
	return (false);
}

int	map_skip_space(int i, char *b, char id)
{
	int	x;

	x = 0;
	if (id == '+')
	{
		while (b[i] != '\0' && b[i] == ' ')
			i++;
		return (i);
	}
	if (id == '-')
	{
		x = ft_strlen(b) - 1;
		if (b[x] == '\n')
			x--;
		while (x > i && b[x] == ' ')
			x--;
		return (x);
	}
	return (0);
}

int	check_map_fragments(t_main *main, char *b, int *c)
{
	int	i;
	int	x;

	i = map_skip_space(0, b, '+');
	x = map_skip_space(i, b, '-');
	if (x == -1 || x < i)
	{
		*c = 2;
		return (2);
	}
	if (b[x] != '1' || b[i] != '1')
		parsing_cleaning(main, b, MAP_NOT_CLOSED);
	while (b[i] != '\0' && i != x)
	{
		if (b[i] == '1' || b[i] == '0' || b[i] == 'N' || b[i] == 'S' || \
			b[i] == 'E' || b[i] == 'W' || b[i] == ' ')
			i++;
		else if (b[i] == '\t')
			parsing_cleaning(main, b, TAB_IN_MAP_FOUND);
		else
			parsing_cleaning(main, b, WRONG_INFO_IN_MAP);
	}
	return (1);
}
