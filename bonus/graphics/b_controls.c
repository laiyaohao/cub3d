#include "../../inc/cub3D.h"

int	key_up(int key, t_game *game)
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

int	key_down(int key, t_game *game)
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
	if (key == KEY_SPACE)
		something_door(game);
	if (key == KEY_ESC)
		exit_game(game);
	return (0);
}
