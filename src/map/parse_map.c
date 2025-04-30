#include "../../inc/cub3D.h"

void	process_p(t_game *game, int c, int *count)
{
    (void)c;
    (void)game;
	printf("Hi player here\n");
    *count += 1;
	// if (c == 'N')
	//     something;
	// else if (c == 'S')
	//     something;
	// else if (c == 'E')
	//     something;
	// else if (c == 'W')
	//     something;
}

void    check_c(int c, int *count, t_game *game)
{
    if (!ft_strchr("01NSEW", c))
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
    int count;

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
