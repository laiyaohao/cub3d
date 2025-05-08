#include "../../inc/cub3D.h"

void    init(t_game *game)
{
    int i;

    game->t_path = malloc(sizeof(char *) * (T_COUNT + 1));
    if (!game->t_path)
    {
        ft_putstr_fd("Error: Fatal\n", 2);
        exit_game(game);
    }
    i = 0;
    while (i < T_COUNT)
    {
        game->t_path[i] = ft_strdup("./textures/North.xpm");
        if (!game->t_path)
        {
            ft_putstr_fd("Error: Fatal\n", 2);
            exit_game(game);
        }
        i++;
    }
    game->t_path[T_COUNT] = NULL;
    game->p.p_x = 4;
	game->p.p_y = 2;
	game->p.d_x = -1;
	game->p.d_y = 0;
	game->p.plane_x = 0;
	game->p.plane_y = 0.66;
	game->time = 0;
	game->old_time = 0;
}
