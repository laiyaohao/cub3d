/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:26:48 by tiatan            #+#    #+#             */
/*   Updated: 2025/07/01 19:16:47 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/**
 * check if file has all the map elements
 * i.e example, NO ./path
 * SO ./path
 * .
 * .
 * and shun bian store the map in last part of map_file in map
 */

int	missing_path(t_game *game)
{
	int	i;

	i = 0;
	while (i < T_COUNT)
	{
		if (!ft_strlen(game->t_path[i]))
		{
			printf("index: %i\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	create_map(t_game *game, int i, int j)
{
	int	k;

	game->map = malloc(sizeof(char *) * (i - j + 1));
	if (!game->map)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	k = 0;
	while (j < i)
	{
		game->map[k] = ft_strdup(game->map_file[j]);
		k++;
		j++;
	}
	game->map[k] = NULL;
}

void	check_f_str(t_game *game)
{
	int	i;
	int	tex_num;
	int	j;

	i = 0;
	tex_num = 0;
	while (game->map_file[i])
	{
		store_help(game, i, &tex_num);
		i++;
		if (tex_num == 6 && missing_path(game))
		{
			ft_putstr_fd("Error: Missing texture paths\n", 2);
			exit_game(game);
		}
		else if (tex_num == 6)
			break ;
	}
	j = i;
	i = valid_map(game, i);
	create_map(game, i, j);
}
