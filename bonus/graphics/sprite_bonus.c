/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:54 by tiatan            #+#    #+#             */
/*   Updated: 2025/07/01 12:36:20 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	get_pixel(t_texture *frame, int x, int y)
{
	int	offset;

	if (x < 0 || y < 0 || x >= frame->w || y >= frame->h)
	{
		return (0);
	}
	offset = (y * frame->line_len) + (x * (frame->bpp / 8));
	return (*(unsigned int *)(frame->data + offset));
}

void	check_limits(t_sprite *s)
{
	if (s->draw_y_start < 0)
		s->draw_y_start = 0;
	s->draw_y_end = s->sprite_h / 2 + S_HEIGHT / 2;
	if (s->draw_y_end > S_HEIGHT)
		s->draw_y_end = S_HEIGHT - 1;
	s->draw_x_start = -s->sprite_w / 2 + s->screen_x;
	if (s->draw_x_start < 0)
		s->draw_x_start = 0;
	s->draw_x_end = s->sprite_w / 2 + s->screen_x;
	if (s->draw_x_end > S_WIDTH)
		s->draw_x_end = S_WIDTH - 1;
}

void	sprite_pixel(t_game *game, t_sprite *s, t_texture *frame, int coord[2])
{
	int	d;

	d = coord[1] * 256 - S_HEIGHT * 128 + s->sprite_h * 128;
	s->tex_y = ((d * frame->h) / s->sprite_h) / 256;
	s->color = get_pixel(frame, s->tex_x, s->tex_y);
	if ((s->color & 0x00FFFFFF) != 0)
		pixel_put(game, coord[0], coord[1], s->color);
}

void	draw_sprite(t_game *game, t_sprite *s, t_texture *frame)
{
	int	x;
	int	y;
	int	coord[2];

	x = s->draw_x_start;
	while (x < s->draw_x_end)
	{
		s->tex_x = (int)((x - (-s->sprite_w / 2 + s->screen_x)) * frame->w
				/ s->sprite_w);
		if (s->trans_y > 0 && x >= 0 && x < S_WIDTH
			&& s->trans_y < game->wall_ray.pd_buffer[x])
		{
			y = s->draw_y_start;
			while (y < s->draw_y_end)
			{
				coord[0] = x;
				coord[1] = y;
				sprite_pixel(game, s, frame, coord);
				y++;
			}
		}
		x++;
	}
}

void	render_sprite(t_game *game)
{
	t_sprite	*s;
	t_texture	*frame;

	s = &game->sprite;
	s->sprite_x = s->x - game->p.p_x;
	s->sprite_y = s->y - game->p.p_y;
	s->inv_det = 1.0 / (game->p.plane_x * game->p.d_y - game->p.d_x
			* game->p.plane_y);
	s->trans_x = s->inv_det * (-game->p.d_y * s->sprite_x + game->p.d_x
			* s->sprite_y);
	s->trans_y = s->inv_det * (-game->p.plane_y * s->sprite_x + game->p.plane_x
			* s->sprite_y);
	if (s->trans_y <= 0)
		return ;
	s->screen_x = (int)((S_WIDTH / 2.0) * (1.0 + s->trans_x / s->trans_y));
	s->sprite_h = abs((int)(S_HEIGHT / s->trans_y));
	s->sprite_w = s->sprite_h;
	s->draw_y_start = -s->sprite_h / 2 + S_HEIGHT / 2;
	frame = &game->s[game->sprite.c_frame];
	check_limits(s);
	draw_sprite(game, s, frame);
}
