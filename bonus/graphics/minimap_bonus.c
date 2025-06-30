/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:45 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:29:46 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	minimap_bg(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MM_PX - 8)
	{
		x = 0;
		while (x < MM_PX - 8)
		{
			draw_to_img(game, MM_OFFSET + x, MM_OFFSET + y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_tiles(t_game *game, int x, int y)
{
	int				map_x;
	int				map_y;
	int				mm_x;
	int				mm_y;
	unsigned int	color;

	map_x = (int)(game->p.p_x) + x;
	map_y = (int)(game->p.p_y) + y;
	if (map_x >= 0 && map_x < game->max_w && map_y >= 0 && map_y < game->max_h)
	{
		mm_x = (x + MM_RADIUS) * MM_SCALE - (game->p.p_x - (int)game->p.p_x);
		mm_y = (y + MM_RADIUS) * MM_SCALE - (game->p.p_y - (int)game->p.p_y);
		if (game->map[map_y][map_x] == '1')
			color = 0xFFFFFF;
		else
			color = 0x444444;
		draw_to_img(game, MM_OFFSET + mm_x, MM_OFFSET + mm_y, color);
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	minimap_bg(game);
	y = -MM_RADIUS;
	while (y <= MM_RADIUS)
	{
		x = -MM_RADIUS;
		while (x <= MM_RADIUS)
		{
			draw_tiles(game, x, y);
			x++;
		}
		y++;
	}
	draw_to_img(game, MM_OFFSET + MM_RADIUS * MM_SCALE, MM_OFFSET + MM_RADIUS
		* MM_SCALE, 0xFF0000);
}
