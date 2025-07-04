/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:49 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:29:50 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		delta_x;
	double	rot_speed;

	(void)y;
	if (game->first_mouse)
	{
		game->prev_mouse_x = x;
		game->first_mouse = 0;
		return (0);
	}
	delta_x = x - game->prev_mouse_x;
	game->prev_mouse_x = x;
	if (delta_x == 0)
		return (0);
	rot_speed = delta_x * 0.002;
	rotate_player(game, rot_speed);
	return (0);
}
