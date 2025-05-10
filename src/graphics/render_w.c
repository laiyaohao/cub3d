#include "../../inc/cub3D.h"

void	render_wall(t_game *game)
{
	int				x;
	int				y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			draw_start;
	double			draw_end;
	int				t_num;
	int				t_x;
	int				t_y;
	int				t_offset;
	int				img_offset;
	unsigned int	color;
    double          line_h;
	double			wall_x;
	double			camera_x;
	double			ray_dx;
	double			ray_dy;
	double			side_dx;
	double			side_dy;
	double			delta_dx;
	double			delta_dy;
	double			pwall_d;
	double			p_step;
	double			t_pos;
	t_texture		*tex;

	x = 0;
	while (x < S_WIDTH)
	{
		// calculate ray position and direction
		camera_x = 2.0 * (double)x / (double)S_WIDTH - 1;
		ray_dx = game->p.d_x + game->p.plane_x * camera_x;
		ray_dy = game->p.d_y + game->p.plane_y * camera_x;

		// which box of the map the player is in
		map_x = (int)game->p.p_x;
		map_y = (int)game->p.p_y;
		
		// length of ray from one x or y side to the next x or y side
		if (ray_dx == 0)
			delta_dx = 1e30;
		else
			delta_dx = fabs(1 / ray_dx);
		if (ray_dy == 0)
			delta_dy = 1e30;
		else
			delta_dy = fabs(1 / ray_dy);
		
			// calculate step and initial side distance
		if (ray_dx < 0)
		{
			step_x = -1;
			side_dx = (game->p.p_x - map_x) * delta_dx;
		}
		else
		{
			step_x = 1;
			side_dx = (map_x + 1.0 - game->p.p_x) * delta_dx;
		}
		if (ray_dy < 0)
		{
			step_y = -1;
			side_dy = (game->p.p_y - map_y) * delta_dy;
		}
		else
		{
			step_y = 1;
			side_dy = (map_y + 1.0 - game->p.p_y) * delta_dy;
		}
		
		// DDA
		hit = 0;
		while (hit == 0)
		{
			// jump to next map square, either in x or y direction
			if (side_dx < side_dy)
			{
				side_dx += delta_dx;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dy += delta_dy;
				map_y += step_y;
				side = 1;
			}
			// check if ray has hit a wall
			if (game->map[map_y][map_x] == '1')
				hit = 1;
		}
		
		// calculate distance of perpendicular ray
		if (side == 0)
			pwall_d = side_dx - delta_dx;
		else
			pwall_d = side_dy - delta_dy;
		
			// calculate height of line to draw on screen
		line_h = (double)S_HEIGHT / pwall_d;
		
		// calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_h / 2.0 + (double)S_HEIGHT / 2.0;
		if (draw_start < 0.0)
			draw_start = 0.0;
		draw_end = line_h / 2.0 + (double)S_HEIGHT / 2.0;
		if (draw_end >= (double)S_HEIGHT)
			draw_end = (double)S_HEIGHT - 1.0;
		
		// determine texture to use based on ray
		if (side == 0)
		{
			if (ray_dx > 0)
				t_num = E_T;
			else
				t_num = W_T;
		}
		else
		{
			if (ray_dy > 0)
				t_num = S_T;
			else
				t_num = N_T;
		}
		tex = &game->t[t_num];
		
		// calculate value of wall_x (where the wall is hit)
		if (side == 0)
			wall_x = game->p.p_y + pwall_d * ray_dy;
		else
			wall_x = game->p.p_x + pwall_d * ray_dx;
		wall_x -= floor(wall_x);
		
		// x coordinate on texture
		t_x = (int)(wall_x * (double)tex->w);
		if (side == 0 && ray_dx > 0)
			t_x = tex->w - t_x - 1;
		if (side == 1 && ray_dy < 0)
			t_x = tex->w - t_x - 1;
		
		// how much to increase the texture coordinate per screen pixel
		p_step = (double)tex->h / line_h;
		
		// starting texture coordinate
		t_pos = (draw_start - (double)S_HEIGHT / 2.0 + line_h / 2.0) * p_step;
		y = (int)draw_start;
		while (y < draw_end)
		{
			// cast texture coordinate to int, mask with (tex->h - 1)
			t_y = (int)t_pos & (tex->h - 1);
			t_pos += p_step;
			t_offset = t_y * tex->line_len + t_x * (tex->bpp / 8);
			color = *(unsigned int *)(tex->data + t_offset);
			// make color darker
			if (side == 1)
				color = (color >> 1) & 8355711;
			img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
			*(unsigned int *)(game->img.data + img_offset) = color;
			y++;
		}
		x++;
	}
}
