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

void    read_map(t_game *game)
{
    int     bytes;
    char    buffer[2];
    char    *temp;
    
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
    game->map = ft_split(temp, '\n');
    free(temp);
}
