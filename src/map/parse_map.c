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
	if (ft_strchr("NSEW", c))
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
		printf("game->map[i]: %s\n", game->map[i]);
		while (game->map[i][k])
		{
			check_c(game->map[i][k], &count, game);
			k++;
		}
		i++;
	}
	if (count != 1)
	{
		printf("count: %d\n", count);
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
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->p.p_x = i;
				game->p.p_y = j;
			}
			j++;
		}
		i++;
	}
}

void	free_map(void **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

int	**copy_map(t_game *game)
{
  int	**copy;
  int		i;

  i = 0;
  copy = ft_calloc((game->max_h + 1), sizeof(int *));
  while (i < game->max_h)
  {
    copy[i] = ft_calloc(game->max_w + 1, sizeof(int));
		if (!copy[i])
		{
			free_map((void **)copy);
			exit_game(game);
		}
    i++;
  }
  copy[i] = NULL;
  return (copy);
}

void	check_map(t_game *game)
{
	int is_sur;
	int **map;

	is_sur = 1;
	get_w_h(game);
	check_arr(game);
	find_player(game);
	int i = 0;
	int j;
	while (i < game->max_h)
	{
		j = 0;
		while (j < game->max_w)
		{
			if (game->map[i][j] && game->map[i][j] != ' ' && game->map[i][j] != '1')
			{
				map = copy_map(game);
				if (flood_fill(game, i, j, map) == 0)
					is_sur = 0;
				free_map((void **)map);
			} 
			j++;
		}
		i++;
	}
	if (!is_sur)
		exit_game(game);
}

void	parse_map(char **argv, t_game *game)
{
	check_file(argv, game);
	read_map(game);
	check_f_str(game);
	check_map(game);
}
