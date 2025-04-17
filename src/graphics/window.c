#include "../../inc/cub3D.h"

void    create_window(t_mlx *mlx, t_game *game)
{
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        //clean up and error message
    }
    mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, 30 * 64, 16.875 * 64, "cub3D");
    if (!mlx->mlx_win)
    {
        //clean up and error message
    }
}
