#include "../../inc/cub3D.h"

void    init(t_game *game)
{
    // int i;

    game->t_path = malloc(sizeof(char *) * (T_COUNT + 1));
    if (!game->t_path)
    {
        ft_putstr_fd("Error: Fatal\n", 2);
        exit_game(game);
    }
    game->t_path[N_T] = ft_strdup("./textures/North.xpm");
    game->t_path[S_T] = ft_strdup("./textures/South.xpm");
    game->t_path[E_T] = ft_strdup("./textures/East.xpm");
    game->t_path[W_T] = ft_strdup("./textures/West.xpm");
    game->t_path[F_T] = ft_strdup("./textures/Floor.xpm");
    game->t_path[C_T] = ft_strdup("./textures/Ceiling.xpm");
    game->first_mouse = 1;
    game->t_path[T_COUNT] = NULL;
    game->p.p_x = 10.5;
	game->p.p_y = 3.5;
}
