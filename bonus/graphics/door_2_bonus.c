/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:36:33 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:41:23 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	something_door(t_game *game)
{
	int	i;
	int	x_diff;
	int	y_diff;

	i = 0;
	while (game->doors[i])
	{
		x_diff = abs(game->doors[i]->map_x - (int)game->p.p_x);
		y_diff = abs(game->doors[i]->map_y - (int)game->p.p_y);
		if ((x_diff <= 2 && y_diff == 0) || (x_diff == 0 && y_diff <= 2))
		{
			if (game->doors[i]->state)
				game->doors[i]->state = 0;
			else
				game->doors[i]->state = 1;
		}
		i++;
	}
}

void	door_hit(t_game *game, t_wray *w)
{
	int		i;
	double	x_diff;
	double	y_diff;

	i = 0;
	while (game->doors[i])
	{
		x_diff = game->doors[i]->map_x - w->map_x;
		y_diff = game->doors[i]->map_y - w->map_y;
		if ((x_diff == 0 || y_diff == 0))
		{
			w->hit = game->doors[i]->state;
			break ;
		}
		i++;
	}
}
