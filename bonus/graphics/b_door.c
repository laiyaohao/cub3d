#include "../../inc/cub3D.h"

void    count_doors(t_game *game)
{
    int i;
    int j;

    i = 0;
    while(game->map[i])
    {
        j = 0;
        while(game->map[i][j])
        {
            if (game->[i][j] == 'D')
                game->d_count++;
            j++;
        }
        i++;
    }
}

void    process_door(t_game *game, int x, int y, int *counter)
{
    if (game->map[y][x] != 'D' || !game->doors[*counter])
        return ;
    game->doors[*counter]->map_x = x;
    game->doors[*counter]->map_y = y;
    game->doors[*counter]->state = 1;
    *counter++;
}

void    add_doors(t_game *game)
{
    int i;
    int j;
    int counter;

    count_doors(game);
    game->doors = malloc(sizeof(t_door *) * (game->d_count + 1));
    if (!game->doors)
    {
        ft_putstr_fd("Error: Fatal\n");
        exit_game(game);
    }
    i = 0;
    counter = 0;
    while(game->map[i])
    {
        j = 0;
        while(game->map[i][j])
        {
            process_door(game, j, i, &counter);
            j++;
        }
        i++;
    }
    game->doors[counter] = NULL;
}

void    something_door(t_game *game)
{
    int i;

    i = 0;
    while (game->doors[i])
    {
        if (game->p.p_x - game->doors[i]->map_x <= 1 && game->p.p_y - game->doors[i]->map_y)
            // change the door state
            // need to check if changing the state and painting based on the state is better or the texture is better
        i++;
    }
}
