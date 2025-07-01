/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:35:47 by tiatan            #+#    #+#             */
/*   Updated: 2025/07/01 12:36:03 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	update_sprite(t_game *game, double c_time)
{
	if (c_time >= game->l_time + 20)
	{
		game->l_time = c_time;
		game->sprite.c_frame = (game->sprite.c_frame + 1) % FRAMES;
	}
}
