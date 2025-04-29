#include "../../inc/cub3D.h"

void    init(t_game *game, t_player *p, t_mlx *mlx)
{
    ft_memset(mlx, 0, sizeof(t_mlx));
    ft_memset(game, 0, sizeof(t_game));
    ft_memset(p, 0, sizeof(t_player));
    game->p = p;
    game->mlx = mlx;
}
