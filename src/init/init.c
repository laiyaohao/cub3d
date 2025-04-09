#include "../../inc/cub3D.h"

void    init_game(char **argv, t_game *game, t_player *p)
{
    ft_memset(game, 0, sizeof(t_game));
    game->map = ft_split(argv, '\n');
    if (!game->map)
    {
        perror("Error: Fatal failed to malloc for map\n");
        exit (1);
    }
    game->p = p;
}

void    init_mlx(t_mlx *mlx)
{
    ft_memset(mlx, 0, sizeof(t_mlx));
}

void    init(char **argv, t_game *game, t_player *p, t_mlx *mlx)
{
    init_game(argv, game, p);
    init_mlx(mlx);
}
