#include "../../inc/cub3D.h"

static int parse_integer(t_game *game, int i, int *j, int *result)
{
	int		sign;

	*result = 0;
	sign = 1;
	while (ft_isspace(game->map_file[i][*j]))
    *j += 1;
	while ((game->map_file[i][*j] >= 9 && game->map_file[i][*j] <= 13) || game->map_file[i][*j] == 32)
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

int store_color(t_game *game, int i, int *j, int tex)
{
	int r;
	int g;
	int b;
	(void) tex;

	parse_integer(game, i, j, &r);
	if (r < 0 || r > 255)
		return 0;
	else if (tex == 4)
		game->fl_r = r;
	else
		game->ce_r = r;
	if (game->map_file[i][(*j)++] != ',')
		return 0;
	parse_integer(game, i, j, &g);
	if (g < 0 || g > 255)
		return 0;
	else if (tex == 4)
		game->fl_g = g;
	else
		game->ce_g = g;
	if (game->map_file[i][(*j)++] != ',')
		return 0;
	parse_integer(game, i, j, &b);
	if (b < 0 || b > 255)
		return 0;
	else if (tex == 4)
		game->fl_b = b;
	else
		game->ce_b = b;
	while (ft_isspace(game->map_file[i][*j]))
    *j += 1;
	return (game->map_file[i][*j] == '\0');
}
