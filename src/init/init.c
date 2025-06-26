#include "../../inc/cub3D.h"

void	init(t_game *game)
{
	game->t_path = malloc(sizeof(char *) * (T_COUNT + 1));
	if (!game->t_path)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	game->s_path = malloc(sizeof(char *) * (FRAMES + 1));
	if (!game->s_path)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	game->s_path[0] = ft_strdup("./textures/Sprite1.xpm");
	game->s_path[1] = ft_strdup("./textures/Sprite2.xpm");
	game->s_path[2] = ft_strdup("./textures/Sprite3.xpm");
	game->first_mouse = 1;
	game->t_path[T_COUNT] = NULL;
	game->s_path[FRAMES] = NULL;
	game->sprite.x = 10.5;
	game->sprite.y = 6.0;
}
