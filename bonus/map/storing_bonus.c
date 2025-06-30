#include "../../inc/cub3D.h"

static int	parse_integer(t_game *game, int i, int *j, int *result)
{
	int	sign;

	*result = 0;
	sign = 1;
	while (ft_isspace(game->map_file[i][*j]))
		*j += 1;
	while ((game->map_file[i][*j] >= 9 && game->map_file[i][*j] <= 13)
		|| game->map_file[i][*j] == 32)
		*j += 1;
	if (game->map_file[i][*j] == '-' || game->map_file[i][*j] == '+')
	{
		if (game->map_file[i][*j] == '-')
			sign = -1;
		*j += 1;
	}
	while (game->map_file[i][*j] >= '0' && game->map_file[i][*j] <= '9')
	{
		*result = *result * 10 + (game->map_file[i][*j] - 48);
		*j += 1;
	}
	if (sign == -1)
		*result = *result * -1;
	return (*result);
}

int	store_red(t_game *game, int i, int *j, int tex)
{
	int	value;
	int	state;

	state = 1;
	parse_integer(game, i, j, &value);
	if (value < 0 || value > 255)
		state = 0;
	if (tex == 4)
		game->fl_r = value;
	else if (tex == 5)
		game->ce_r = value;
	if (game->map_file[i][(*j)++] != ',')
		state = 0;
	return (state);
}

int	store_green(t_game *game, int i, int *j, int tex)
{
	int	value;
	int	state;

	state = 1;
	parse_integer(game, i, j, &value);
	if (value < 0 || value > 255)
		state = 0;
	if (tex == 4)
		game->fl_g = value;
	else if (tex == 5)
		game->ce_g = value;
	if (game->map_file[i][(*j)++] != ',')
		state = 0;
	return (state);
}

int	store_blue(t_game *game, int i, int *j, int tex)
{
	int	value;
	int	state;

	state = 1;
	parse_integer(game, i, j, &value);
	if (value < 0 || value > 255)
		state = 0;
	if (tex == 4)
		game->fl_b = value;
	else if (tex == 5)
		game->ce_b = value;
	return (state);
}

int	store_color(t_game *game, int i, int *j, int tex)
{
	if ((store_red(game, i, j, tex)) == 0)
		return (0);
	if ((store_green(game, i, j, tex)) == 0)
		return (0);
	if ((store_blue(game, i, j, tex)) == 0)
		return (0);
	while (ft_isspace(game->map_file[i][*j]))
		*j += 1;
	return (game->map_file[i][*j] == '\0');
}
