/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:26:31 by tiatan            #+#    #+#             */
/*   Updated: 2025/07/01 19:08:46 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	render_values(t_game *game, t_fray *f, int y)
{
	f->ray_dx0 = game->p.d_x - game->p.plane_x;
	f->ray_dy0 = game->p.d_y - game->p.plane_y;
	f->ray_dx1 = game->p.d_x + game->p.plane_x;
	f->ray_dy1 = game->p.d_y + game->p.plane_y;
	f->pos = y - S_HEIGHT / 2;
	f->pos_z = 0.5 * S_HEIGHT;
	f->row_d = f->pos_z / f->pos;
	f->floor_sx = f->row_d * (f->ray_dx1 - f->ray_dx0) / S_HEIGHT;
	f->floor_sy = f->row_d * (f->ray_dy1 - f->ray_dy0) / S_HEIGHT;
	f->floor_x = game->p.p_x + f->row_d * f->ray_dx0;
	f->floor_y = game->p.p_y + f->row_d * f->ray_dy0;
}

void	set_color(t_game *game, t_fray *f, int x, int y)
{
	int	r;
	int	g;
	int	b;

	(void)x;
	r = game->fl_r;
	g = game->fl_g;
	b = game->fl_b;
	f->color = (r << 16) | (g << 8) | b;
	f->img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.data + f->img_offset) = f->color;
	r = game->ce_r;
	g = game->ce_g;
	b = game->ce_b;
	f->color = (r << 16) | (g << 8) | b;
	f->ceiling_y = S_HEIGHT - y - 1;
	f->img_offset = f->ceiling_y * game->img.line_len + x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.data + f->img_offset) = f->color;
}

void	render_floor(t_game *game)
{
	int		x;
	int		y;
	t_fray	f;

	f = game->floor_ray;
	y = 0;
	while (y < S_HEIGHT)
	{
		render_values(game, &f, y);
		x = 0;
		while (x++ < S_WIDTH)
		{
			f.floor_x += f.floor_sx;
			f.floor_y += f.floor_sy;
			set_color(game, &f, x, y);
		}
		y++;
	}
}
