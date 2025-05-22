#include "../../inc/cub3D.h"

void	count_doors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'D')
				game->d_count++;
			j++;
		}
		i++;
	}
}

void	process_door(t_game *game, int x, int y, int *counter)
{
	if (game->map[y][x] != 'D' || !game->doors[*counter])
		return ;
	game->doors[*counter]->map_x = x;
	game->doors[*counter]->map_y = y;
	game->doors[*counter]->state = 1;
	*counter += 1;
}

void	add_doors(t_game *game)
{
	int	i;
	int	j;
	int	counter;

	count_doors(game);
	game->doors = malloc(sizeof(t_door *) * (game->d_count + 1));
	ft_memset(game->doors, 0, sizeof(t_door **));
	if (!game->doors)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	i = 0;
	counter = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			process_door(game, j, i, &counter);
			j++;
		}
		i++;
	}
	game->doors[counter] = NULL;
}

void	something_door(t_game *game)
{
	int		i;
	double	x_diff;
	double	y_diff;

	i = 0;
	while (game->doors[i])
	{
		x_diff = game->p.p_x - game->doors[i]->map_x;
		y_diff = game->p.p_y - game->doors[i]->map_y;
		if (x_diff <= 1.5 && x_diff >= -1.5 && y_diff <= 1.5 && y_diff >= -1.5)
		{
			if (game->doors[i]->state)
				game->doors[i]->state = 0;
			else
				game->doors[i]->state = 1;
		}
		i++;
	}
}
