#include "../../inc/cub3D.h"

void	ray_pos(t_game *game, t_wray *w, int x)
{
	// calculate ray position and direction
	w->camera_x = 1.0 - 2.0 * (double)x / (double)S_WIDTH;
	w->ray_dx = game->p.d_x + game->p.plane_x * w->camera_x;
	w->ray_dy = game->p.d_y + game->p.plane_y * w->camera_x;
	// which box of the map the player is in
	w->map_x = (int)game->p.p_x;
	w->map_y = (int)game->p.p_y;
	// length of ray from one x or y side to the next x or y side
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
		// jump to next map square, either in x or y direction
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
		// check if ray has hit a wall
		if (game->map[w->map_y][w->map_x] == '1')
			w->hit = 1;
		if (game->map[w->map_y][w->map_x] == 'D')
			door_hit(game, w);
		if (game->map[w->map_y][w->map_x] == 'S')
			sprite(game, w);
	}
}

void	draw_values(t_wray *w)
{
	// calculate distance of perpendicular ray
	if (w->side == 0)
		w->pwall_d = w->side_dx - w->delta_dx;
	else
		w->pwall_d = w->side_dy - w->delta_dy;
	// calculate height of line to draw on screen
	w->line_h = (double)S_HEIGHT / w->pwall_d;
	// calculate lowest and highest pixel to fill in current stripe
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
		// calculate step and initial side distance
		ray_step(game, &w);
		// DDA
		dda(game, &w);
		draw_values(&w);
		// determine texture to use based on ray
		select_texture(game, &w, &tex);
		texture_value(game, &w, tex);
		cast_texture(game, &w, x, tex);
		x++;
	}
}
