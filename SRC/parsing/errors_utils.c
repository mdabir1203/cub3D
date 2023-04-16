/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:56:13 by lkavalia          #+#    #+#             */
/*   Updated: 2023/04/16 17:21:40 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief 
 * 
 * @param buffer 
 * @return true 	 -	when
 * @return false 
 */
bool	map_fragment_found(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] == ' ')
		i++;
	if (buffer[i] == '1' || buffer[i] == '0')
		return (true);
	return (false);
}

bool	match_component_name(char *name)
{
	int	len_name;

	len_name = ft_strlen(name);
	if (ft_strncmp(name, "NO", len_name) == 0)
		return (true);
	if (ft_strncmp(name, "SO", len_name) == 0)
		return (true);
	if (ft_strncmp(name, "WE", len_name) == 0)
		return (true);
	if (ft_strncmp(name, "EA", len_name) == 0)
		return (true);
	if (ft_strncmp(name, "F", len_name) == 0)
		return (true);
	if (ft_strncmp(name, "C", len_name) == 0)
		return (true);
	return (false);
}

bool	component_found(char *str)
{
	int		i;
	int		start;
	int		len;
	char	*name;
	bool	check;

	len = 0;
	start = 0;
	name = NULL;
	check = false;
	while (str[start] != '\0' && str[start] == ' ')
		start++;
	i = start;
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	len = i;
	while (str[len] != '\0' && str[len] == ' ')
		len++;
	if (str[len] == '\0' || str[len] == '\n')
		return (false);
	name = ft_substr(str, start, i - start);
	check = match_component_name(name);
	free(name);
	return (check);
}

void	find_trash(t_main *main, char *s)
{
	int	i;

	i = 0;
	if (map_fragment_found(s) == true || component_found(s) == true)
		return ;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\n'))
		i++;
	if (s[i] != '\0')
	{
		free (s);
		close(main->file_fd);
		ft_exiterr(CUB_CONTAINS_TRASH);
	}
}

void	parsing_cleaning(t_main *main, char *arr, int err)
{
	if (arr != NULL)
		free(arr);
	clear_the_main_struct(main);
	ft_exiterr(err);
}
