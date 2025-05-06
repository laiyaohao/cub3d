#include "../../inc/cub3D.h"

void	init_p(t_game *game)
{
	game->p->p_x = 22;
	game->p->p_y = 12;
	game->p->d_x = -1;
	game->p->d_y = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
	game->time = 0;
	game->old_time = 0;
}

int     run_game(t_game *game)
{
	int x;

	x = 0;
	while (x < game->max_w)
	{
		game->camera_x = 2 * x / (double)w - 1;
		game->ray_dx = game->p->d_x + game->plane_x * game->camera_x;
		game->ray_dy = game->p->d_y + game->plane_y * game->camera_x;
	}
}

void    game_start(t_game *game)
{
    (void)game;
    create_window(game->mlx);
    mlx_hook(game->mlx->mlx_win, keydown, 1L << 0, key_press, game);
	mlx_hook(game->mlx->mlx_win, destroy, 1L << 0, exit_game, game);
	mlx_loop_hook(game->mlx->mlx_ptr, run_game, game->mlx);
	mlx_loop(game->mlx->mlx_ptr);
	mlx_loop_end(game->mlx->mlx_ptr);
}
