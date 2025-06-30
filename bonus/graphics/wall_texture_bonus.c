/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:30:22 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:30:23 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	select_texture(t_game *game, t_wray *w, t_texture **tex)
{
	int	t_num;

	if (game->map[w->map_y][w->map_x] == 'D')
	{
		*tex = &game->b[2];
		return ;
	}
	else if (w->side == 0)
	{
		if (w->ray_dx > 0)
			t_num = E_T;
		else
			t_num = W_T;
	}
	else
	{
		if (w->ray_dy > 0)
			t_num = S_T;
		else
			t_num = N_T;
	}
	*tex = &game->t[t_num];
}

void	texture_value(t_game *game, t_wray *w, t_texture *tex)
{
	if (w->side == 0)
		w->wall_x = game->p.p_y + w->pwall_d * w->ray_dy;
	else
		w->wall_x = game->p.p_x + w->pwall_d * w->ray_dx;
	w->wall_x -= floor(w->wall_x);
	w->t_x = (int)(w->wall_x * (double)tex->w);
	if (w->side == 0 && w->ray_dx > 0)
		w->t_x = tex->w - w->t_x - 1;
	if (w->side == 1 && w->ray_dy < 0)
		w->t_x = tex->w - w->t_x - 1;
	w->p_step = (double)tex->h / w->line_h;
}

void	cast_texture(t_game *game, t_wray *w, int x, t_texture *tex)
{
	int		y;
	int		t_offset;
	double	t_pos;

	t_pos = (w->draw_start - (double)S_HEIGHT / 2.0 + w->line_h / 2.0)
		* w->p_step;
	y = (int)w->draw_start;
	while (y < w->draw_end)
	{
		w->t_y = (int)t_pos & (tex->h - 1);
		t_pos += w->p_step;
		t_offset = w->t_y * tex->line_len + w->t_x * (tex->bpp / 8);
		w->color = *(unsigned int *)(tex->data + t_offset);
		if (w->side == 1)
			w->color = (w->color >> 1) & 8355711;
		w->img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
		*(unsigned int *)(game->img.data + w->img_offset) = w->color;
		y++;
	}
}
