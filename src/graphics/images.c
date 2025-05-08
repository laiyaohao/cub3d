#include "../../inc/cub3D.h"

void	process_textures(t_game *game)
{
	int	i;

	game->img.img_ptr = mlx_new_image(game->mlx.mlx_ptr, S_WIDTH, S_HEIGHT);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	i = 0;
	while (i < T_COUNT)
	{
		game->t[i].image = mlx_xpm_file_to_image(game->mlx.mlx_ptr, game->t_path[i],
				&game->t[i].w, &game->t[i].h);
		if (!game->t[i].image)
		{
			ft_putstr_fd("Error: Invalid texture file, please use a .xpm\n", 2);
			exit_game(game);
		}
		game->t[i].data = mlx_get_data_addr(game->t[i].image, &game->t[i].bpp,
				&game->t[i].line_len, &game->t[i].endian);
		i++;
	}
}
