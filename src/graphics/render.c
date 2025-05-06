#include "../../inc/cub3D.h"

void	render_floor(t_game *game)
{
	int				x;
	int				y;
	int				pos;
	int				cell_x;
	int				cell_y;
	int				t_x;
	int				t_y;
	unsigned int	color;
	float			pos_z;
	float			row_d;
	float			ray_dx0;
	float			ray_dy0;
	float			ray_dx1;
	float			ray_dy1;
	float			floor_x;
	float			floor_y;
	float			floor_sx;
	float			floor_sy;
	int				floor_t;
	int				ceiling_t;

	y = 0;
	while (y < game->max_h)
	{
		ray_dx0 = game->p->d_x - game->plane_x;
		ray_dy0 = game->p->d_y - game->plane_y;
		ray_dx1 = game->p->d_x + game->plane_x;
		ray_dy1 = game->p->d_y + game->plane_y;
		pos = y - 720 / 2;
		pos_z = 0.5 * 720;
		row_d = pos_z / pos;
		floor_sx = row_d * (ray_dx1 - ray_dx0) / 720;
		floor_sy = row_d * (ray_dy1 - ray_dy0) / 720;
		floor_x = game->p->p_x + row_d * ray_dx0;
		floor_y = game->p->py + row_d * ray_dy0;
		x = 0;
		while (x++ < 1280)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = ((int)(tex_w * (floor_x - cell_x))) & (tex_w - 1);
			ty = ((int)(tex_w * (floor_y - cell_y))) & (tex_w - 1);
			floor_x += floor_sx;
			floor_y += floor_sy;
			// choose texture and draw the pixel
			floor_t = 3;
			ceiling_t = 6;
			// floor
			color = texture[floor_t][tex_w * ty + tx];
			buffer[y][x] = color;
			// ceiling
			color = texture[ceiling_t][tex_w * ty + tx];
			buffer[720 - y - 1][x] = color;
		}
		y++;
	}
}

void	render_wall(t_game *game)
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;
    int     step_x;
    int     step_y;
    int     hit;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		t_num;
	int		t_x;
	int		t_y;
	unsigned int	color;
	double	wall_x;
	double	camera_x;
	double	ray_dx;
	double	ray_dy;
    double  side_dx;
    double  side_dy;
    double  delta_dx;
    double  delta_dy;
    double  pwall_d;
	double	p_step;
	double	t_pos;

	x = 0;
	while (x < game->max_w)
	{
		// calculate ray position and direction
		camera_x = 2 * x / (double)game->max_w - 1;
		ray_dx = game->p->d_x + game->plane_x * camera_x;
		ray_dy = game->p->d_y + game->plane_y * camera_x;

		// which box of the map the player is in
		map_x = game->p.p_x;
		map_y = game->p.p_y;

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
			step_x -1;
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
			if (game->map[map_y][map_x] > 0)
				hit = 1;
		}

		// calculate distance of perpendicular ray
		if (side == 0)
			pwall_d = side_dx - delta_dx;
		else
			pwall_d = side_dy - delta_dy;

		// calculate height of line to draw on screen
		line_h = (int)(game->max_h / pwall_d);

		// calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_h / 2 + game->max_h / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + h / 2;
		if (draw_end >= h)
			draw_end = h - 1;
		
		// texturing calculations (minus 1 so that texture 0 can be used)
		t_num = game->map[map_y][map_x] - 1;

		// calculate value of wall_x (where the wall is hit)
		if (side == 0)
			wall_x = game->p.p_y + pwall_d * ray_dy;
		else
			wall_x = game->p.p_x + pwall_d * ray_dx;
		wall_x -= floor(wall_x);

		// x coordinate on texture
		t_x = (int)(wall_x * (double)texture_width);
		if (side == 0 && ray_dx > 0)
			t_x = texture_width - t_x - 1;
		if (side == 1 && ray_dy < 0)
			t_x = texture_width - t_x - 1;

		// how much to increase the texture coordinate per screen pixel
		p_step = 1.0 * texture_height / line_h;

		// starting texture coordinate
		t_pos = (draw_start - game->max_h / 2 + line_h / 2) * p_step;
		y = draw_start;
		while (y < draw_end)
		{
			// cast texture coordinate to int, mask with (texture_height - 1) in case of overflow
			t_y = (int)t_pos & (texture_height - 1);
			t_pos += p_step;
			color = texture[t_num][texture_width * t_y + t_x];
			// make color darker
			if (side == 1)
				color = (color >> 1) & 8355711;
			buffer[y][x] = color;
			y++;
		}
		x++;
	}
}
