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

void	process_p(t_game *game, int c, int *count)
{
	printf("Hi player here\n");
	*count += 1;
	if (c == 'N')
	{
		game->p.d_x = 0;
		game->p.d_y = -1;
	}
	else if (c == 'S')
	{
		game->p.d_x = 0;
		game->p.d_y = 1;
	}
	else if (c == 'E')
	{
		game->p.d_x = 1;
		game->p.d_y = 0;
	}
	else if (c == 'W')
	{
		game->p.d_x = -1;
		game->p.d_y = 0;
	}
	game->p.plane_x = game->p.d_y * 0.66;
	game->p.plane_y = -game->p.d_x * 0.66;
}

void	check_c(int c, int *count, t_game *game)
{
	if (!ft_strchr("01NSEWD", c))
	{
		ft_putstr_fd("Error: Invalid character: ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("\n", 2);
		exit_game(game);
	}
	else if (ft_strchr("NSEW", c))
		process_p(game, c, count);
}

void	check_arr(t_game *game)
{
	int	i;
	int	k;
	int	count;

	i = 0;
	count = 0;
	while (game->map[i])
	{
		k = 0;
		while (game->map[i][k])
		{
			check_c(game->map[i][k], &count, game);
			k++;
		}
		i++;
	}
	if (count != 1)
	{
		ft_putstr_fd("Error: Include only 1 player in the map\n", 2);
		exit_game(game);
	}
}

void	get_w_h(t_game *game)
{
	int	i;
	int	tmp;
	int	w;

	i = 0;
	w = 0;
	while (game->map[i])
	{
		tmp = 0;
		while (game->map[i][tmp])
			tmp++;
		if (tmp > w)
			w = tmp;
		i++;
	}
	game->max_w = w;
	game->max_h = i;
}

void	check_map(t_game *game)
{
	get_w_h(game);
	check_arr(game);
}

void	parse_map(char **argv, t_game *game)
{
	check_file(argv, game);
	read_map(game);
	check_map(game);
}
