#include "../../inc/cub3D.h"

// void	free_map(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i] != NULL)
// 	{
// 		free(map[i]);
// 		map[i] = NULL;
// 		i++;
// 	}
// 	free(map);
// }

int	top_left_corner_empty(t_game *game, int x, int y)
{
	if ((x - 1) >= 0 && (y - 1) >= 0)
	{
		if (game->map[x - 1][y] == '1' && game->map[x][y - 1] == '1'
			&& (game->map[x - 1][y - 1] == ' ' || game->map[x - 1][y
				- 1] == '\0'))
			return (1);
	}
	return (0);
}

int	bottom_right_corner_empty(t_game *game, int x, int y)
{
	if ((x + 1) < game->max_h && (y + 1) < game->max_w)
	{
		if (game->map[x][y + 1] == '1' && game->map[x + 1][y] == '1'
			&& (game->map[x + 1][y + 1] == ' ' || game->map[x + 1][y
				+ 1] == '\0'))
			return (1);
	}
	return (0);
}

int	bottom_left_corner_empty(t_game *game, int x, int y)
{
	if ((x + 1) < game->max_h && (y - 1) >= 0)
	{
		if (game->map[x][y - 1] == '1' && game->map[x + 1][y] == '1'
			&& (game->map[x + 1][y - 1] == '\0' || game->map[x + 1][y
				- 1] == ' '))
			return (1);
	}
	return (0);
}

int	top_right_corner_empty(t_game *game, int x, int y)
{
	if ((x - 1) >= 0 && (y + 1) < game->max_w)
	{
		if (game->map[x - 1][y] == '1' && game->map[x][y + 1] == '1'
			&& (game->map[x - 1][y + 1] == ' ' || game->map[x - 1][y
				+ 1] == '\0'))
			return (1);
	}
	return (0);
}

int	flood_fill(t_game *game, int x, int y, int **map)
{
	int	is_surrounded;

	if (x < 0 || x >= game->max_h || y < 0 || y >= game->max_w)
		return (0);
	if (game->map[x][y] == '1' || map[x][y] == 1)
		return (1);
	else if (game->map[x][y] == ' ')
		return (0);
	else if (top_left_corner_empty(game, x, y)
		|| bottom_right_corner_empty(game, x, y)
		|| bottom_left_corner_empty(game, x, y) || top_right_corner_empty(game,
			x, y))
		return (0);
	else
		map[x][y] = 1;
	is_surrounded = 1;
	is_surrounded &= flood_fill(game, x + 1, y, map);
	is_surrounded &= flood_fill(game, x - 1, y, map);
	is_surrounded &= flood_fill(game, x, y + 1, map);
	is_surrounded &= flood_fill(game, x, y - 1, map);
	return (is_surrounded);
}
