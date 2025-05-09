#include "../../inc/cub3D.h"

void	render_floor(t_game *game)
{
	int				x;
	int				y;
	int				r;
	int				g;
	int				b;
	t_fray			f;
	// int				cell_x;
	// int				cell_y;
	// int				t_x;
	// int				t_y;
	// int				floor_t;
	// int				ceiling_t;
	// int				t_offset;

	f = game->floor_ray;
	y = 0;
	while (y < S_HEIGHT)
	{
		f.ray_dx0 = game->p.d_x - game->p.plane_x;
		f.ray_dy0 = game->p.d_y - game->p.plane_y;
		f.ray_dx1 = game->p.d_x + game->p.plane_x;
		f.ray_dy1 = game->p.d_y + game->p.plane_y;
		f.pos = y - S_HEIGHT / 2;
		f.pos_z = 0.5 * S_HEIGHT;
		f. row_d = f.pos_z / f.pos;
		f.floor_sx = f.row_d * (f.ray_dx1 - f.ray_dx0) / S_HEIGHT;
		f.floor_sy = f.row_d * (f.ray_dy1 - f.ray_dy0) / S_HEIGHT;
		f.floor_x = game->p.p_x + f.row_d * f.ray_dx0;
		f.floor_y = game->p.p_y + f.row_d * f.ray_dy0;
		x = 0;
		while (x++ < S_WIDTH)
		{
			// cell_x = (int)f.floor_x;
			// cell_y = (int)f.floor_y;
			// t_x = ((int)(tex_w * (floor_x - cell_x))) & (tex_w - 1);
			// t_y = ((int)(tex_w * (floor_y - cell_y))) & (tex_w - 1);
			f.floor_x += f.floor_sx;
			f.floor_y += f.floor_sy;
			// floor texture
			// t_offset = t_y * game->t[floor_t].line_len + t_x * (game->t[floor_t].bpp / 8);
			// color = *(unsigned int *)(game->t[floor_t].data + t_offset);
			r = 50;
			g = 50;
			b = 50;
			f.color = (r << 16) | (g << 8) | b;
			f.img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
			*(unsigned int *)(game->img.data + f.img_offset) = f.color;
			// ceiling texture
			// t_offset = t_y * game->t[ceiling_t].line_len + t_x * (game->t[ceiling_t].bpp / 8);
			// color = *(unsigned int *)(game->t[ceiling_t].data + t_offset);
			r = 70;
			g = 70;
			b = 70;
			f.color = (r << 16) | (g << 8) | b;
			f.ceiling_y = S_HEIGHT - y - 1;
			f.img_offset = f.ceiling_y * game->img.line_len + x * (game->img.bpp / 8);
			*(unsigned int *)(game->img.data + f.img_offset) = f.color;
		}
		y++;
	}
}

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
	int				line_h;
	int				draw_start;
	int				draw_end;
	int				t_num;
	int				t_x;
	int				t_y;
	int				t_offset;
	int				img_offset;
	unsigned int	color;
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
		camera_x = 2 * x / (double)S_WIDTH - 1;
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
		line_h = (int)(S_HEIGHT / pwall_d);
		
		// calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_h / 2 + S_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + S_HEIGHT / 2;
		if (draw_end >= S_HEIGHT)
			draw_end = S_HEIGHT - 1;
		
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
		p_step = 1.0 * tex->h / line_h;
		
		// starting texture coordinate
		t_pos = (draw_start - S_HEIGHT / 2 + line_h / 2) * p_step;
		y = draw_start;
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
