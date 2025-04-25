#include "../../inc/cub3D.h"

void    game_start(t_game *game)
{
    (void)game;
    create_window(game->mlx);
    mlx_hook(mlx->mlx_win, keydown, 1L << 0, key_press, mlx);
	mlx_hook(mlx->mlx_win, destroy, 1L << 0, exit_game, mlx);
	mlx_loop_hook(mlx->mlx_ptr, run_game, mlx);
	mlx_loop(game->mlx->mlx_ptr);
	mlx_loop_end(mlx->mlx_ptr);
}

void    exit_game(t_game *game)
{
    if (game->mlx->mlx_win)
    {
        mlx_clear_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
        mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
    }
    if (game->mlx->mlx_ptr)
    {
        mlx_destroy_display(game->mlx->mlx_ptr);
        free(game->mlx->mlx_ptr);
    }
    clean_up(game);
}
