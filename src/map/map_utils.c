#include "../../inc/cub3D.h"

void	check_file(char **argv, t_game *game)
{
	size_t	i;

	i = 0;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (ft_strncmp(&argv[1][i], ".cub", 5))
	{
		ft_putstr_fd("Error: Invalid file, please use a .cub file\n", 2);
		exit(1);
	}
	else
	{
		game->map_fd = open(argv[1], O_RDONLY);
		if (game->map_fd < 0)
		{
			ft_putstr_fd("Error: Unable to open .cub file\n", 2);
			exit(1);
		}
	}
}

void	read_map(t_game *game)
{
	int		bytes;
	char	buffer[2];
	char	*temp;

	bytes = 1;
	temp = ft_strdup("");
	if (!temp)
		return ;
	while (bytes)
	{
		bytes = read(game->map_fd, buffer, 1);
		buffer[bytes] = '\0';
		strcjoin(buffer[0], &temp);
	}
	game->map_file = ft_split(temp, '\n');
	free(temp);
}

int	is_map_line(t_game *game, int i)
{
	int	j;

	j = 0;
	while (game->map_file[i][j])
	{
		if (!ft_strchr("01NSEW ", game->map_file[i][j]))
		{
			ft_putstr_fd("Error: Invalid character: ", 2);
			ft_putchar_fd(game->map_file[i][j], 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		j++;
	}
	return (1);
}

int	valid_map(t_game *game, int i)
{
	while (game->map_file[i])
	{
		if (!is_map_line(game, i))
		{
			ft_putstr_fd("not a valid map, sadly", 2);
			exit_game(game);
		}
		i++;
	}
	return (i);
}
