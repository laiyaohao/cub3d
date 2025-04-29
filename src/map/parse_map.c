#include "../../inc/cub3D.h"

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
