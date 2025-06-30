#include "../../inc/cub3D.h"

void	pixel_put(t_game *game, int x, int y, int color)
{
	char	*dest;

	dest = game->img.data + (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dest = color;
}
