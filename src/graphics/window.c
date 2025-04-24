#include "../../inc/cub3D.h"

void    create_window(t_mlx *mlx)
{
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        ft_putstr_fd("Error: Failed to initialise mlx pointer\n", 2);
        //clean up
    }
    mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, 1280, 720, "cub3D");
    if (!mlx->mlx_win)
    {
        ft_putstr_fd("Error: Failed to create mlx window\n", 2);
        //clean up
    }
}
