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

void	draw_minimap(t_game *game)
{
	int				x;
	int				x_end;
	int				y;
	int				y_end;
	int				mm_x;
	int				mm_y;
	unsigned int	color;

	y = floorf(game->p.p_y - MM_RADIUS);
	y_end = floorf(game->p.p_y + MM_RADIUS);
	while (y <= y_end)
	{
        x = floorf(game->p.p_x - MM_RADIUS);
        x_end = floorf(game->p.p_x + MM_RADIUS);
        while (x <= x_end)
		{
			if (x >= 0 && x < game->max_w && y >= 0 && y < game->max_h)
			{
				mm_x = (x - game->p.p_x + MM_RADIUS) * MM_SCALE;
				mm_y = (y - game->p.p_y + MM_RADIUS) * MM_SCALE;
				if (game->map[y][x] == '1')
					color = 0xFFFFFF;
				else
					color = 0x444444;
				draw_to_img(game, mm_x, mm_y, color);
			}
			x++;
		}
		y++;
	}
}
