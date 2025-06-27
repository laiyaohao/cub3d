#include "../../inc/cub3D.h"

void	set_values(t_game *game)
{
	game->b_path[0] = ft_strdup("./textures/Floor.xpm");
	game->b_path[1] = ft_strdup("./textures/Ceiling.xpm");
	game->b_path[2] = ft_strdup("./textures/Door.xpm");
	game->s_path[0] = ft_strdup("./textures/Sprite1.xpm");
	game->s_path[1] = ft_strdup("./textures/Sprite2.xpm");
	game->s_path[2] = ft_strdup("./textures/Sprite3.xpm");
	game->t_path[0] = ft_strdup("");
	game->t_path[1] = ft_strdup("");
	game->t_path[2] = ft_strdup("");
	game->t_path[3] = ft_strdup("");
	game->t_path[4] = NULL;
	game->first_mouse = 1;
	game->s_path[FRAMES] = NULL;
	game->b_path[3] = NULL;
	game->sprite.x = 10.5;
	game->sprite.y = 6.0;
}

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
	game->b_path = malloc(sizeof(char *) * (4));
	if (!game->b_path)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	set_values(game);
}
