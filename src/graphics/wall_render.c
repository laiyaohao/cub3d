/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:25:24 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:25:41 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ray_pos(t_game *game, t_wray *w, int x)
{
	w->camera_x = 1.0 - 2.0 * (double)x / (double)S_WIDTH;
	w->ray_dx = game->p.d_x + game->p.plane_x * w->camera_x;
	w->ray_dy = game->p.d_y + game->p.plane_y * w->camera_x;
	w->map_x = (int)game->p.p_x;
	w->map_y = (int)game->p.p_y;
	if (w->ray_dx == 0)
		w->delta_dx = 1e30;
	else
		w->delta_dx = fabs(1 / w->ray_dx);
	if (w->ray_dy == 0)
		w->delta_dy = 1e30;
	else
		w->delta_dy = fabs(1 / w->ray_dy);
}

void	ray_step(t_game *game, t_wray *w)
{
	if (w->ray_dx < 0)
	{
		w->step_x = -1;
		w->side_dx = (game->p.p_x - w->map_x) * w->delta_dx;
	}
	else
	{
		w->step_x = 1;
		w->side_dx = (w->map_x + 1.0 - game->p.p_x) * w->delta_dx;
	}
	if (w->ray_dy < 0)
	{
		w->step_y = -1;
		w->side_dy = (game->p.p_y - w->map_y) * w->delta_dy;
	}
	else
	{
		w->step_y = 1;
		w->side_dy = (w->map_y + 1.0 - game->p.p_y) * w->delta_dy;
	}
}

void	dda(t_game *game, t_wray *w)
{
	w->hit = 0;
	while (w->hit == 0)
	{
		if (w->side_dx < w->side_dy)
		{
			w->side_dx += w->delta_dx;
			w->map_x += w->step_x;
			w->side = 0;
		}
		else
		{
			w->side_dy += w->delta_dy;
			w->map_y += w->step_y;
			w->side = 1;
		}
		if (game->map[w->map_y][w->map_x] == '1')
			w->hit = 1;
	}
}

void	draw_values(t_wray *w)
{
	if (w->side == 0)
		w->pwall_d = w->side_dx - w->delta_dx;
	else
		w->pwall_d = w->side_dy - w->delta_dy;
	w->line_h = (double)S_HEIGHT / w->pwall_d;
	w->draw_start = -w->line_h / 2.0 + (double)S_HEIGHT / 2.0;
	if (w->draw_start < 0.0)
		w->draw_start = 0.0;
	w->draw_end = w->line_h / 2.0 + (double)S_HEIGHT / 2.0;
	if (w->draw_end >= (double)S_HEIGHT)
		w->draw_end = (double)S_HEIGHT - 1.0;
}

void	render_wall(t_game *game)
{
	int			x;
	t_wray		w;
	t_texture	*tex;

	x = 0;
	w = game->wall_ray;
	while (x < S_WIDTH)
	{
		ray_pos(game, &w, x);
		ray_step(game, &w);
		dda(game, &w);
		draw_values(&w);
		select_texture(game, &w, &tex);
		texture_value(game, &w, tex);
		cast_texture(game, &w, x, tex);
		x++;
	}
}
