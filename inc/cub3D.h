#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
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
# define KEY_ESC 65307
# define S_HEIGHT 768
# define S_WIDTH 1024

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

typedef struct s_player
{
	double p_x; // x start position
	double p_y; // y start position
	double d_x; // initial x direction
	double d_y; // initial y direction
	double fov; // 2 *atan(0.66/1.0) = 66degrees
	double		plane_x;
	double		plane_y;
}				t_player;

typedef	struct s_input
{
	int	rot_left;
	int	rot_right;
	int	move_up;
	int	move_left;
	int	move_right;
	int	move_down;
}				t_input;


typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_mlx;

typedef struct s_ray
{
}				t_ray;

typedef struct s_texture
{
	void		*image;
	char		*data;
	int			w;
	int			h;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_img
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef	struct s_fray
{
	int				pos;
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
	int				img_offset;
	int				ceiling_y;
}				t_fray;

typedef	struct	s_wray
{
	
}				t_wray;


typedef struct s_game
{
	int			map_fd;
	int			max_w;
	int			max_h;
	char		**map;
	char		**t_path;
	double		camera_x;
	double		ray_dx;
	double		ray_dy;
	t_player	p;
	t_input		input;
	t_mlx		mlx;
	t_texture	t[T_COUNT];
	t_img		img;
	t_fray		floor_ray;
	t_wray		wall_ray;
}				t_game;

int				main(int argc, char **argv);
void			init(t_game *game);
void			check_file(char **argv, t_game *game);
void			read_map(t_game *game);
void			parse_map(char **argv, t_game *game);
void			game_start(t_game *game);
int				exit_game(t_game *game);
void			process_textures(t_game *game);
void			render_wall(t_game *game);
void			render_floor(t_game *game);
int				key_up(int key, t_game *game);
int				key_down(int key, t_game *game);
void    		process_movement(t_game *game);
void    		process_rotation(t_game *game);
void			strcjoin(int c, char **res);
void			cleanup(t_game *game);

#endif