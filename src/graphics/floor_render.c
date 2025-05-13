#include "../../inc/cub3D.h"

void	calculate_fval(t_game *game, t_fray *f, int y)
{
	f->ray_dx0 = game->p.d_x - game->p.plane_x;
	f->ray_dy0 = game->p.d_y - game->p.plane_y;
	f->ray_dx1 = game->p.d_x + game->p.plane_x;
	f->ray_dy1 = game->p.d_y + game->p.plane_y;
	f->pos = y - S_HEIGHT / 2;
	f->pos_z = 0.5 * S_HEIGHT;
	f->row_d = f->pos_z / f->pos;
	f->floor_sx = f->row_d * (f->ray_dx1 - f->ray_dx0) / S_WIDTH;
	f->floor_sy = f->row_d * (f->ray_dy1 - f->ray_dy0) / S_WIDTH;
	f->floor_x = game->p.p_x + f->row_d * f->ray_dx0;
	f->floor_y = game->p.p_y + f->row_d * f->ray_dy0;
}

void	calculate_textures(t_game *game, t_fray *f, int x, int y)
{
	int				cell_x;
	int				cell_y;
	int				t_x;
	int				t_y;
	int				t_offset;

	cell_x = (int)f->floor_x;
	cell_y = (int)f->floor_y;
	double fractional_x = f->floor_x - (double)cell_x;
	double fractional_y = f->floor_y - (double)cell_y;
	t_x = (int)(fractional_x * (double)(game->t[F_T].w)) & (game->t[F_T].w - 1);
	t_y = (int)(fractional_y * (double)(game->t[F_T].h)) & (game->t[F_T].h - 1);
	f->floor_x += f->floor_sx;
	f->floor_y += f->floor_sy;
	t_offset = t_y * game->t[F_T].line_len + t_x * (game->t[F_T].bpp / 8);
	f->color = *(unsigned int *)(game->t[F_T].data + t_offset);
	f->img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.data + f->img_offset) = f->color;
	t_offset = t_y * game->t[C_T].line_len + t_x * (game->t[C_T].bpp / 8);
	f->color = *(unsigned int *)(game->t[C_T].data + t_offset);
	f->ceiling_y = S_HEIGHT - y - 1;
	f->img_offset = f->ceiling_y * game->img.line_len + x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.data + f->img_offset) = f->color;
}

void	render_floor(t_game *game)
{
	int				x;
	int				y;
	t_fray			f;

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

// void	render_floor(t_game *game)
// {
// 	int				x;
// 	int				y;
// 	int				r;
// 	int				g;
// 	int				b;
// 	t_fray			f;
// 	// int				cell_x;
// 	// int				cell_y;
// 	// int				t_x;
// 	// int				t_y;
// 	// int				floor_t;
// 	// int				ceiling_t;
// 	// int				t_offset;

// 	f = game->floor_ray;
// 	y = 0;
// 	while (y < S_HEIGHT)
// 	{
// 		f.ray_dx0 = game->p.d_x - game->p.plane_x;
// 		f.ray_dy0 = game->p.d_y - game->p.plane_y;
// 		f.ray_dx1 = game->p.d_x + game->p.plane_x;
// 		f.ray_dy1 = game->p.d_y + game->p.plane_y;
// 		f.pos = y - S_HEIGHT / 2;
// 		f.pos_z = 0.5 * S_HEIGHT;
// 		f. row_d = f.pos_z / f.pos;
// 		f.floor_sx = f.row_d * (f.ray_dx1 - f.ray_dx0) / S_HEIGHT;
// 		f.floor_sy = f.row_d * (f.ray_dy1 - f.ray_dy0) / S_HEIGHT;
// 		f.floor_x = game->p.p_x + f.row_d * f.ray_dx0;
// 		f.floor_y = game->p.p_y + f.row_d * f.ray_dy0;
// 		x = 0;
// 		while (x++ < S_WIDTH)
// 		{
// 			// cell_x = (int)f.floor_x;
// 			// cell_y = (int)f.floor_y;
// 			// t_x = ((int)(tex_w * (floor_x - cell_x))) & (tex_w - 1);
// 			// t_y = ((int)(tex_w * (floor_y - cell_y))) & (tex_w - 1);
// 			f.floor_x += f.floor_sx;
// 			f.floor_y += f.floor_sy;
// 			// floor texture
// 			// t_offset = t_y * game->t[floor_t].line_len + t_x * (game->t[floor_t].bpp / 8);
// 			// color = *(unsigned int *)(game->t[floor_t].data + t_offset);
// 			r = 50;
// 			g = 50;
// 			b = 50;
// 			f.color = (r << 16) | (g << 8) | b;
// 			f.img_offset = y * game->img.line_len + x * (game->img.bpp / 8);
// 			*(unsigned int *)(game->img.data + f.img_offset) = f.color;
// 			// ceiling texture
// 			// t_offset = t_y * game->t[ceiling_t].line_len + t_x * (game->t[ceiling_t].bpp / 8);
// 			// color = *(unsigned int *)(game->t[ceiling_t].data + t_offset);
// 			r = 70;
// 			g = 70;
// 			b = 70;
// 			f.color = (r << 16) | (g << 8) | b;
// 			f.ceiling_y = S_HEIGHT - y - 1;
// 			f.img_offset = f.ceiling_y * game->img.line_len + x * (game->img.bpp / 8);
// 			*(unsigned int *)(game->img.data + f.img_offset) = f.color;
// 		}
// 		y++;
// 	}
// }
