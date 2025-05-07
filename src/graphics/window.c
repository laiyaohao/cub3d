#include "../../inc/cub3D.h"

void    create_window(t_game *game)
{
    game->mlx.mlx_ptr = mlx_init();
    if (!game->mlx.mlx_ptr)
    {
        ft_putstr_fd("Error: Failed to initialise mlx pointer\n", 2);
        exit_game(game);
    }
    mlx->mlx_win = mlx_new_window(game->mlx.mlx_ptr, S_HEIGHT, S_WIDTH, "cub3D");
    if (!game->mlx.mlx_win)
    {
        ft_putstr_fd("Error: Failed to create mlx window\n", 2);
        exit_game(game);
    }
}
