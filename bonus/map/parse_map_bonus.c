#include "../../inc/cub3D.h"

void	sprite_pos(int i, int k, t_game *game)
{
	game->sprite.x = (double)k + 0.5;
	game->sprite.y = (double)i + 0.5;
}

void	process_p(t_game *game, int c, int *count)
{
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
			if (ft_strchr("NSEW", game->map[i][k]))
				process_p(game, game->map[i][k], &count);
			if (ft_strchr("A", game->map[i][k]))
				sprite_pos(i, k, game);
			k++;
		}
		i++;
	}
	if (count != 1)
	{
		ft_putstr_fd("Error: Map should have exactly 1 player\n", 2);
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

void	parse_map(char **argv, t_game *game)
{
	check_file(argv, game);
	read_map(game);
	check_f_str(game);
	check_arr(game);
	get_w_h(game);
	check_map(game);
}
