#include "../../inc/cub3D.h"

void	store_addr(t_game *game, int i, int j, int tex)
{
	int		x;
	int		len;
	char	*addr;
	int		full_len;

	full_len = ft_strlen(game->map_file[i]);
	len = full_len - j;
	addr = malloc(len + 1);
	if (!addr)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	x = 0;
	while (j < full_len)
	{
		addr[x] = game->map_file[i][j];
		j++;
		x++;
	}
	addr[x] = '\0';
	if (game->t_path[tex])
		free(game->t_path[tex]);
	game->t_path[tex] = addr;
}

void	store_help_help(t_game *game, int i, int *j, int tex)
{
	if ((tex == 4 || tex == 5))
	{
		if (store_color(game, i, j, tex) == 0)
		{
			ft_putstr_fd("Error: Incorrect RGB values\n", 2);
			exit_game(game);
		}
	}
	else
		store_addr(game, i, *j, tex);
}

void	increment_j(int *j, int tex)
{
	if (tex == 4 || tex == 5)
		*j += 1;
	else
		*j += 2;
}

int	find_textiles(t_game *game, int i, int j)
{
	if (ft_strncmp(&game->map_file[i][j], "NO", 2) == 0)
		return (N_T);
	else if (ft_strncmp(&game->map_file[i][j], "SO", 2) == 0)
		return (S_T);
	else if (ft_strncmp(&game->map_file[i][j], "EA", 2) == 0)
		return (E_T);
	else if (ft_strncmp(&game->map_file[i][j], "WE", 2) == 0)
		return (W_T);
	else if (ft_strncmp(&game->map_file[i][j], "F", 1) == 0)
		return (4);
	else if (ft_strncmp(&game->map_file[i][j], "C", 1) == 0)
		return (5);
	return (-1);
}

void	store_help(t_game *game, int i, int *tex_num)
{
	int	j;
	int	tex;

	j = 0;
	while (ft_isspace(game->map_file[i][j]))
		j++;
	if (!game->map_file[i][j])
		return ;
	tex = find_textiles(game, i, j);
	if (tex == -1)
	{
		ft_putstr_fd("Error: Incorrect textures\n", 2);
		exit_game(game);
	}
	increment_j(&j, tex);
	while (ft_isspace(game->map_file[i][j]))
		j++;
	if (!game->map_file[i][j])
	{
		ft_putstr_fd("Error: Incorrect structure for textures\n", 2);
		exit_game(game);
	}
	store_help_help(game, i, &j, tex);
	*tex_num += 1;
}
