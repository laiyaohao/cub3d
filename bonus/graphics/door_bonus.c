/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:29 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:40:58 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	count_doors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'D')
				game->d_count++;
			j++;
		}
		i++;
	}
}

void	process_door(t_game *game, int x, int y, int *counter)
{
	if (game->map[y][x] != 'D')
		return ;
	game->doors[*counter]->map_x = x;
	game->doors[*counter]->map_y = y;
	game->doors[*counter]->state = 1;
	*counter += 1;
}

void	store_door(t_game *game)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			process_door(game, j, i, &counter);
			j++;
		}
		i++;
	}
	game->doors[counter] = NULL;
}

void	add_doors(t_game *game)
{
	int	i;

	count_doors(game);
	game->doors = malloc(sizeof(t_door *) * (game->d_count + 1));
	if (!game->doors)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	i = 0;
	while (i < game->d_count)
	{
		game->doors[i] = malloc(sizeof(t_door));
		if (!game->doors[i])
		{
			ft_putstr_fd("Error: Fatal\n", 2);
			exit_game(game);
		}
		i++;
	}
	game->doors[game->d_count] = NULL;
	store_door(game);
}
