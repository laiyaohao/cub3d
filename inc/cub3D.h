#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_W 119
# define KEY_SPACE 32
# define KEY_ESC 65307
# define S_HEIGHT 1024
# define S_WIDTH 1280
# define MM_RADIUS 5
# define MM_SCALE 8
# define MM_SIZE (2 * MM_RADIUS + 1)
# define MM_PX (MM_SIZE * MM_SCALE)
# define MM_OFFSET 10
# define FRAMES 3
# define SPRITE_WIDTH 64
# define SPRITE_HEIGHT 64

enum
{
	keydown = 2,
	keyup = 3,
	mousedown = 4,
	mouseup = 5,
	mousemove = 6,
	expose = 12,
	destroy = 17
};

enum
{
	N_T,
	S_T,
	E_T,
	W_T,
	T_COUNT
};

enum
{
	F_T,
	C_T,
	D_T,
	B_TCOUNT
};

typedef struct s_player
{
	double p_x; // x start position
	double p_y; // y start position
	double d_x; // initial x direction
	double d_y; // initial y direction
	double fov; // 2 *atan(0.66/1.0) = 66degrees
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_input
{
	int				rot_left;
	int				rot_right;
	int				move_up;
	int				move_left;
	int				move_right;
	int				move_down;
}					t_input;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*mlx_win;
}					t_mlx;

typedef struct s_door
{
	int				state;
	int				map_x;
	int				map_y;
}					t_door;

typedef struct s_texture
{
	void			*image;
	char			*data;
	int				w;
	int				h;
	int				bpp;
	int				line_len;
	int				endian;
}					t_texture;

typedef struct s_img
{
	void			*img_ptr;
	char			*data;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_sprite
{
	int				c_frame;
	int				sprite_h;
	int				sprite_w;
	int				tex_x;
	int				tex_y;
	int				draw_x_start;
	int				draw_x_end;
	int				draw_y_start;
	int				draw_y_end;
	int				screen_x;
	unsigned int	color;
	double			x;
	double			y;
	double			sprite_x;
	double			sprite_y;
	double			trans_x;
	double			trans_y;
	double			inv_det;
	t_img			img;
}					t_sprite;

typedef struct s_fray
{
	int				pos;
	unsigned int	color;
	double			pos_z;
	double			row_d;
	double			ray_dx0;
	double			ray_dy0;
	double			ray_dx1;
	double			ray_dy1;
	double			floor_x;
	double			floor_y;
	double			floor_sx;
	double			floor_sy;
	int				img_offset;
	int				ceiling_y;
}					t_fray;

typedef struct s_wray
{
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				img_offset;
	int				t_x;
	int				t_y;
	unsigned int	color;
	double			draw_start;
	double			draw_end;
	double			line_h;
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
}					t_wray;

typedef struct s_game
{
	int				prev_mouse_x;
	int				first_mouse;
	int				map_fd;
	int				max_w;
	int				max_h;
	int				d_count;
	int64_t			l_time;
	char			**map;
	char			**map_file;
	char			**t_path;
	char			**s_path;
	double			camera_x;
	double			ray_dx;
	double			ray_dy;
	t_player		p;
	t_input			input;
	t_mlx			mlx;
	t_door			**doors;
	t_texture		t[T_COUNT];
	t_texture		s[FRAMES];
	t_img			img;
	t_fray			floor_ray;
	t_wray			wall_ray;
	t_sprite		sprite;
	int				fl_r;
	int				fl_g;
	int				fl_b;
	int				ce_r;
	int				ce_g;
	int				ce_b;
}					t_game;

int					main(int argc, char **argv);
void				init(t_game *game);
void				check_file(char **argv, t_game *game);
void				read_map(t_game *game);
void				parse_map(char **argv, t_game *game);
void				game_start(t_game *game);
int					exit_game(t_game *game);
void				process_textures(t_game *game);
void				process_sprite(t_game *game);
void				add_doors(t_game *game);
void				select_texture(t_game *game, t_wray *w, t_texture **tex);
void				texture_value(t_game *game, t_wray *w, t_texture *tex);
void				cast_texture(t_game *game, t_wray *w, int x,
						t_texture *tex);
void				render_wall(t_game *game);
void				render_floor(t_game *game);
int					key_up(int key, t_game *game);
int					key_down(int key, t_game *game);
int					mouse_move(int x, int y, t_game *game);
int64_t				get_time(void);
void				process_movement(t_game *game);
void				process_rotation(t_game *game);
void				rotate_player(t_game *game, double rot_speed);
void				something_door(t_game *game);
void				door_hit(t_game *game, t_wray *w);
void				draw_minimap(t_game *game);
void				update_sprite(t_game *game, double c_time);
void				render_sprite(t_game *game);
void				cleanup(t_game *game);
void				draw_to_img(t_game *game, int x, int y, int color);
void				pixel_put(t_game *game, int x, int y, int color);
void				strcjoin(int c, char **res);
void				check_f_str(t_game *game);
int					store_color(t_game *game, int i, int *j, int tex);
int					valid_map(t_game *game, int i);
int					flood_fill(t_game *game, int x, int y, int **map);
void				check_f_str(t_game *game);
void				increment_j(int *j, int tex);
void				store_help(t_game *game, int i, int *tex_num);
void 				free_2d(void **content);
void				check_map(t_game *game);

#endif