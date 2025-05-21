#include "../../inc/cub3D.h"

int	run_game(t_game *game)
{
	process_rotation(game);
	process_movement(game);
	render_floor(game);
	render_wall(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win,
		game->img.img_ptr, 0, 0);
	return (0);
}

void	create_window(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
	{
		ft_putstr_fd("Error: Failed to initialise mlx pointer\n", 2);
		exit_game(game);
	}
	game->mlx.mlx_win = mlx_new_window(game->mlx.mlx_ptr, S_WIDTH, S_HEIGHT,
			"cub3D");
	if (!game->mlx.mlx_win)
	{
		ft_putstr_fd("Error: Failed to create mlx window\n", 2);
		exit_game(game);
	}
}

void	game_start(t_game *game)
{
	create_window(game);
	process_textures(game);
	count_doors(game);
	mlx_hook(game->mlx.mlx_win, keydown, 1L << 0, key_down, game);
	mlx_hook(game->mlx.mlx_win, keyup, 1L << 1, key_up, game);
	mlx_hook(game->mlx.mlx_win, destroy, 1L << 17, exit_game, game);
	mlx_hook(game->mlx.mlx_win, mousemove, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx.mlx_ptr, run_game, game);
	mlx_loop(game->mlx.mlx_ptr);
	mlx_loop_end(game->mlx.mlx_ptr);
}
