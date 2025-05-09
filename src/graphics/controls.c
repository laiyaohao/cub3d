#include "../../inc/cub3D.h"

int    exit_game(t_game *game)
{
    int i;

    i = 0;
    while (i < T_COUNT)
    {
        if (game->t[i].image)
            mlx_destroy_image(game->mlx.mlx_ptr, game->t[i].image);
        i++;
    }
    if (game->img.img_ptr)
        mlx_destroy_image(game->mlx.mlx_ptr, game->img.img_ptr);
    if (game->mlx.mlx_win)
    {
        mlx_clear_window(game->mlx.mlx_ptr, game->mlx.mlx_win);
        mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.mlx_win);
    }
    if (game->mlx.mlx_ptr)
    {
        mlx_destroy_display(game->mlx.mlx_ptr);
        free(game->mlx.mlx_ptr);
    }
    cleanup(game);
    exit (0);
}

int     key_up(int key, t_game *game)
{
    if (key == KEY_W)
        game->input.move_up = 0;
    if (key == KEY_A)
        game->input.move_left = 0;
    if (key == KEY_S)
        game->input.move_down = 0;
    if (key == KEY_D)
        game->input.move_right = 0;
    if (key == KEY_LEFT)
        game->input.rot_left = 0;
    if (key == KEY_RIGHT)
        game->input.rot_right = 0;
    return (0);
}

int    key_down(int key, t_game *game)
{
    if (key == KEY_W)
        game->input.move_up = 1;
    if (key == KEY_A)
        game->input.move_left = 1;
    if (key == KEY_S)
        game->input.move_down = 1;
    if (key == KEY_D)
        game->input.move_right = 1;
    if (key == KEY_LEFT)
        game->input.rot_left = 1;
    if (key == KEY_RIGHT)
        game->input.rot_right = 1;
    if (key == KEY_ESC)
        exit_game(game);
    return (0);
}
