/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:32 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:29:33 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	calculate_fval(t_game *game, t_fray *f, int y)
{
	f->ray_dx0 = game->p.d_x + game->p.plane_x;
	f->ray_dy0 = game->p.d_y + game->p.plane_y;
	f->ray_dx1 = game->p.d_x - game->p.plane_x;
	f->ray_dy1 = game->p.d_y - game->p.plane_y;
	f->pos = y - S_HEIGHT / 2;
	f->pos_z = 0.5 * S_HEIGHT;
	f->row_d = f->pos_z / f->pos;
	f->floor_sx = f->row_d * (f->ray_dx1 - f->ray_dx0) / S_WIDTH;
	f->floor_sy = f->row_d * (f->ray_dy1 - f->ray_dy0) / S_WIDTH;
	f->floor_x = game->p.p_x + f->row_d * f->ray_dx0;
	f->floor_y = game->p.p_y + f->row_d * f->ray_dy0;
}

void	texture_values(t_game *game, t_fray *f, int *t_x, int *t_y)
{
	int		cell_x;
	int		cell_y;
	double	fractional_x;
	double	fractional_y;

	cell_x = (int)f->floor_x;
	cell_y = (int)f->floor_y;
	fractional_x = f->floor_x - (double)cell_x;
	fractional_y = f->floor_y - (double)cell_y;
	*t_x = (int)(fractional_x * (double)(game->b[0].w)) & (game->b[0].w
			- 1);
	*t_y = (int)(fractional_y * (double)(game->b[0].h)) & (game->b[0].h
			- 1);
}

void	calculate_textures(t_game *game, t_fray *f, int x, int y)
{
	int	t_x;
	int	t_y;
	int	t_offset;

	texture_values(game, f, &t_x, &t_y);
	f->floor_x += f->floor_sx;
	f->floor_y += f->floor_sy;
	t_offset = t_y * game->b[0].line_len + t_x * (game->b[0].bpp / 8);
	f->color = *(unsigned int *)(game->b[0].data + t_offset);
	f->img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.data + f->img_offset) = f->color;
	t_offset = t_y * game->b[1].line_len + t_x * (game->b[1].bpp / 8);
	f->color = *(unsigned int *)(game->b[1].data + t_offset);
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
		calculate_fval(game, &f, y);
		x = 0;
		while (x++ < S_WIDTH)
			calculate_textures(game, &f, x, y);
		y++;
	}
}
