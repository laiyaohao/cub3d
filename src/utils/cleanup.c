#include "../../inc/cub3D.h"

void    free_2d(void **content)
{
    int i;

    i = 0;
    if (!content)
        return ;
    while (content[i])
    {
        free(content[i]);
        i++;
    }
    free(content);
}

void    cleanup(t_game *game)
{
    if (!game)
        return ;
    if (game->map)
        free_2d((void **)game->map);
}
