#include "../../inc/cub3D.h"

void    game_start(t_mlx *mlx, t_game *game)
{
    (void)game;
    create_window(mlx);
    mlx_hook(mlx->mlx_win, keydown, 1L << 0, key_press, mlx);
	mlx_hook(mlx->mlx_win, destroy, 1L << 0, exit_game, mlx);
	mlx_loop_hook(mlx->mlx_ptr, run_game, mlx);
	mlx_loop(mlx->mlx_ptr);
	mlx_loop_end(mlx->mlx_ptr);
}