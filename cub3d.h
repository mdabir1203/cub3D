/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:00:09 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/15 18:31:12 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//Headers
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_main
{
	char	*north_t;
	char	*south_t;
	char	*west_t;
	char	*east_t;

	int		f[3];
	int		c[3];
}t_main;

//void	parsing(t_main *main);

//Colors
# define BLANK "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELL "\033[0;33m"
# define CYAN "\033[0;36m"

//Things
# define D_NO
# define D_SO
# define D_WE
# define D_EA
# define D_F "220,100,0"
# define D_C "225,30,0"
#endif
