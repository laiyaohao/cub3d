#include "../../inc/cub3D.h"

int     run_game(t_game *game)
{
	//raycast
}

void    game_start(t_game *game)
{
    (void)game;
    create_window(game->mlx);
    mlx_hook(game->mlx->mlx_win, keydown, 1L << 0, key_press, game);
	mlx_hook(game->mlx->mlx_win, destroy, 1L << 0, exit_game, game);
	// mlx_loop_hook(game->mlx->mlx_ptr, run_game, game->mlx);
	mlx_loop(game->mlx->mlx_ptr);
	mlx_loop_end(game->mlx->mlx_ptr);
}
