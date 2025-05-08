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

void    update_values(int key, double *new_x, double *new_y, t_game *game)
{
    double  move_speed;

    move_speed = 0.1;
    if (key == KEY_W)
    {
        *new_x = game->p.p_x + game->p.d_x * move_speed;
        *new_y = game->p.p_y + game->p.d_y * move_speed;
    }
    else if (key == KEY_A)
    {
        *new_x = game->p.p_x - game->p.plane_x * move_speed;
        *new_y = game->p.p_y - game->p.plane_y * move_speed;
    }
    else if (key == KEY_S)
    {
        *new_x = game->p.p_x - game->p.d_x * move_speed;
        *new_y = game->p.p_y - game->p.d_y * move_speed;
    }
    else if (key == KEY_D)
    {
        *new_x = game->p.p_x + game->p.plane_x * move_speed;
        *new_y = game->p.p_y + game->p.plane_y * move_speed;
    }
}

void    process_movement(int key, t_game *game)
{
    double  new_x;
    double  new_y;

    update_values(key, &new_x, &new_y, game);
    if (game->map[(int)new_x][(int)game->p.p_y] != '1')
        game->p.p_x = new_x;
    if (game->map[(int)game->p.p_x][(int)new_y] != '1')
        game->p.p_y = new_y;
}

int    key_press(int key, t_game *game)
{
    if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
        process_movement(key, game);
    if (key == KEY_ESC)
        exit_game(game);
    return (0);
}
