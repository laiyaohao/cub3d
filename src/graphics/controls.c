#include "../../inc/cub3D.h"

int    exit_game(t_game *game)
{
    if (game->mlx->mlx_win)
    {
        mlx_clear_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
        mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->mlx_win);
    }
    if (game->mlx->mlx_ptr)
    {
        mlx_destroy_display(game->mlx->mlx_ptr);
        free(game->mlx->mlx_ptr);
    }
    cleanup(game);
    exit (0);
}

int    key_press(int key, t_game *game)
{
    if (game->p->move == 0)
    {
        if (key == KEY_W)
            game->p->move = 1;
        else if (key == KEY_S)
            game->p->move = 2;
        else if (key == KEY_A)
            game->p->move = 3;
        else if (key == KEY_D)
            game->p->move = 4;
        else if (key == KEY_LEFT)
            game->p->p_dir -= 1;
        else if (key == KEY_RIGHT)
            game->p->p_dir += 1;
    }
    if (key == KEY_ESC)
        exit_game(game);
    return (0);
}
