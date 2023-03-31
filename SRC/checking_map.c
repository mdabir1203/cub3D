/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:24:37 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/31 12:29:58 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_line_top_and_bottom(t_main *main)
{
	int	i;
	int	len;

	i = 0;
	len = main->height - 1;
	while (main->map[0][i] != '\0' && \
			main->map[0][i] != '0' && main->map[0][i] != main->p_dir)
		i++;
	if (main->map[0][i] == '0' || main->map[0][i] == main->p_dir)
		parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
	i = 0;
	while (main->map[len][i] != '\0' && \
			main->map[len][i] != '0' && main->map[len][i] != main->p_dir)
		i++;
	if (main->map[len][i] == '0' || main->map[len][i] == main->p_dir)
		parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
}

int	check_right(t_main *main, int x, int y, int x_r)
{
	int	y_up;
	int	y_d;

	y_up = y + 1;
	y_d = y - 1;
	if (y != 0 && x_r < (int)ft_strlen(main->map[y_d]) && \
	(main->map[y_d][x_r] == '0' || main->map[y_d][x_r] == main->p_dir))
	{
		if (main->map[y_d][x] != '1')
			return (1);
		else if (x_r < (int)ft_strlen(main->map[y]) && main->map[y][x_r] != '1')
			return (1);
	}
	if (x_r < (int)ft_strlen(main->map[y]) && \
		(main->map[y][x_r] == '0' || main->map[y][x_r] == main->p_dir))
		return (1);
	if (y_up < main->height && (x_r < (int)ft_strlen(main->map[y_up])) && \
		(main->map[y_up][x_r] == '0' || main->map[y_up][x_r] == main->p_dir))
	{
		if (main->map[y_up][x] != '1')
			return (1);
		else if (x_r < (int)ft_strlen(main->map[y]) && main->map[y][x_r] != '1')
			return (1);
	}
	return (0);
}

int	check_middle(t_main *main, int x, int y)
{
	int	y_up;
	int	y_down;

	y_up = y + 1;
	y_down = y - 1;
	if (y != 0 && x < (int)ft_strlen(main->map[y_down]) && \
		(main->map[y_down][x] == '0' || main->map[y_down][x] == main->p_dir))
		return (1);
	if (main->map[y][x] == '0' || main->map[y][x] == main->p_dir)
		return (1);
	if (y_up < main->height && x < (int)ft_strlen(main->map[y_up]) && \
		(main->map[y_up][x] == '0' || main->map[y_up][x] == main->p_dir))
		return (1);
	return (0);
}

int	check_left(t_main *main, int x, int y, int x_l)
{
	int	y_d;
	int	y_up;

	y_d = y - 1;
	y_up = y + 1;
	if (y != 0 && x != 0 && x_l < (int)ft_strlen(main->map[y_d]) && \
									main->map[y_d][x_l] == '0')
	{
		if (x < (int)ft_strlen(main->map[y_d]) && main->map[y_d][x] != '1')
			return (1);
		if (main->map[y][x_l] != '1')
			return (1);
	}
	if (x != 0 && x_l < (int)ft_strlen(main->map[y]) && \
		(main->map[y][x_l] == '0' || main->map[y][x_l] == main->p_dir))
		return (1);
	if (x != 0 && (y_up < main->height) && \
		x_l < (int)ft_strlen(main->map[y_up]) && main->map[y_up][x_l] == '0')
	{
		if (main->map[y][x_l] != '1')
			return (1);
		else if (main->map[y_up][x] != '1')
			return (1);
	}
	return (0);
}

void	check_spaces(t_main *main, int x, int y)
{
	while (y < main->height)
	{
		while (x < (int)ft_strlen(main->map[y]) && main->map[y][x] != '\0')
		{
			if (main->map[y][x] != '\0' && main->map[y][x] == ' ')
			{
				main->map[y][x] = '+';
				if (check_right(main, x, y, x + 1) == 1)
					parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
				if (check_middle(main, x, y) == 1)
					parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
				if (check_left(main, x, y, x - 1) == 1)
					parsing_cleaning(main, NULL, MAP_IS_NOT_CLOSED);
			}
			if (x + 3 < (int)ft_strlen(main->map[y]) && \
									main->map[y][x + 3] == ' ')
				x += 3;
			else
				x++;
		}
		x = 0;
		y++;
	}
}
