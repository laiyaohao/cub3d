#include "../../inc/cub3D.h"

void	process_plane(t_game *game)
{
	double	aspect_ratio;
	double	fov_deg;
	double	fov_rad;
	double	plane_len;

	aspect_ratio = (double)S_WIDTH / (double)S_HEIGHT;
	fov_deg = 66.0;
	fov_rad = fov_deg * (M_PI / 180.0);
	plane_len = tan(fov_rad / 2.0) * aspect_ratio;
	game->p.plane_x = game->p.d_y * plane_len;
	game->p.plane_y = -game->p.d_x * plane_len;
}

void	find_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->p.p_x = (double)j + 0.5;
				game->p.p_y = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}
}

int	**copy_map(t_game *game)
{
	int	**copy;
	int	i;

	i = 0;
	copy = ft_calloc((game->max_h + 1), sizeof(int *));
	while (i < game->max_h)
	{
		copy[i] = ft_calloc(game->max_w + 1, sizeof(int));
		if (!copy[i])
			exit_game(game);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	copy_ff(t_game *game, int *is_sur)
{
	int	i;
	int	j;
	int	**map;

	i = 0;
	while (i < game->max_h)
	{
		j = 0;
		while (j < game->max_w && game->map[i][j])
		{
			if (game->map[i][j] && game->map[i][j] != ' '
				&& game->map[i][j] != '1')
			{
				map = copy_map(game);
				if (flood_fill(game, i, j, map) == 0)
					*is_sur = 0;
				free_2d((void **)map);
			}
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	int	is_sur;

	is_sur = 1;
	find_player(game);
	copy_ff(game, &is_sur);
	if (!is_sur)
	{
		ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
		exit_game(game);
	}
}
