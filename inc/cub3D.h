#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
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
	int	p_x;
	int	p_y;
	int	direction;
}				t_player;

typedef struct s_game
{
    char		**map;
	t_player	*p;
}				t_game;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *mlx_win;
}               t_mlx;

int 	main(int argc, char **argv);
void	init(char **argv, t_game *game, t_player *p, t_mlx *mlx);

#endif