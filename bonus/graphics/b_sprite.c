#include "../../inc/cub3D.h"

void    update_sprite(t_game *game, double d_time)
{
    game->sprite->timer += d_time;
    if (game->sprite->timer >= game->sprite->frame_duration)
    {
        game->sprite.timer = 0;
        game->sprite->c_frame = (game->sprite->c_frame + 1) % FRAMES;
    }
}

void    render_sprite(t_game *game)
{
    void    *img;
    int     x;
    int     y;

    img = game->sprite.i[game->sprite->c_frame];
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win, img, x, y);
}
