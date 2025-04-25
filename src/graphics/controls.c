#include "../../inc/cub3D.h"

void    key_press(int key, t_game *game)
{
    if (game->mlx->move == 0)
    {
        if (key == KEY_W)
            game->mlx->move = 1;
        else if (key == KEY_S)
            game->mlx->move = 2;
        else if (key == KEY_A)
            game->mlx->move = 3;
        else if (key == KEY_D)
            game->mlx->move = 4;
        else if (key == KEY_LEFT)
            game->p->p_angle -= 1;
        else if (key == KEY_RIGHT)
            game->p->p_angle += 1;
    }
    if (key == KEY_ESC)
        exit_game(mlx);
}
