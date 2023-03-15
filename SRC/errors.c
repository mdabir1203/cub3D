/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rehernan <rehernan@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:19:31 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/15 22:10:22 by rehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: ENUMS for readability

void	ft_exiterr(int err)
{
	if (err == 1)
		ft_putstr_fd("Not enough arguments.\n", 2);
	else if (err == 2)
		ft_putstr_fd("Invalid arguments.\n", 2);
	exit (err);
}
