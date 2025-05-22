#include "../../inc/cub3D.h"

void	draw_to_img(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
    while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			px = x + j;
			py = y + i;
			if (px >= 0 && px < S_WIDTH && py >= 0 && py < S_HEIGHT)
				pixel_put(game, px, py, color);
			j++;
		}
		i++;
	}
}
