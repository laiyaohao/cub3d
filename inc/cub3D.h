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

typedef struct s_player
{
	double p_x; // x start position
	double p_y; // y start position
	double d_x; // initial x direction
	double d_y; // initial y direction
	double fov; // 2 *atan(0.66/1.0) = 66degrees
	double		p_dir;
	int			move;
}				t_player;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_mlx;

typedef struct s_game
{
	int			map_fd;
	char		**map;
	int			max_w;
	int			max_h;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dx;
	double		ray_dy;
	double		time;
	double		old_time;
	t_player	*p;
	t_mlx		*mlx;
}				t_game;

int				main(int argc, char **argv);
void			init(t_game *game, t_player *p, t_mlx *mlx);
void			check_file(char **argv, t_game *game);
void			read_map(t_game *game);
void    		parse_map(char **argv, t_game *game);
void			game_start(t_game *game);
int				exit_game(t_game *game);
void			create_window(t_mlx *mlx);
int				key_press(int key, t_game *game);
void			strcjoin(int c, char **res);
void    		cleanup(t_game *game);

#endif