#include "../../inc/cub3D.h"

void	move_player(double *new_x, double *new_y, t_game *game,
		double move_speed)
{
	*new_x = game->p.p_x;
	*new_y = game->p.p_y;
	if (game->input.move_up)
	{
		*new_x += game->p.d_x * move_speed;
		*new_y += game->p.d_y * move_speed;
	}
	if (game->input.move_left)
	{
		*new_x += game->p.plane_x * move_speed;
		*new_y += game->p.plane_y * move_speed;
	}
	if (game->input.move_down)
	{
		*new_x -= game->p.d_x * move_speed;
		*new_y -= game->p.d_y * move_speed;
	}
	if (game->input.move_right)
	{
		*new_x -= game->p.plane_x * move_speed;
		*new_y -= game->p.plane_y * move_speed;
	}
}

int	check_door(t_game *game, int x, int y)
{
	int	i;
	int	x_diff;
	int	y_diff;

	i = 0;
	while (game->doors[i])
	{
		x_diff = x - game->doors[i]->map_x;
		y_diff = y - game->doors[i]->map_y;
		if ((x_diff == 0 || y_diff == 0) && game->doors[i]->state)
			return (0);
		i++;
	}
	return (1);
}

void	process_movement(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.03;
	move_player(&new_x, &new_y, game, move_speed);
	if (game->map[(int)game->p.p_y][(int)new_x] == '1')
		return ;
	if (game->map[(int)game->p.p_y][(int)new_x] == 'D')
	{
		if (check_door(game, new_x, (int)game->p.p_y))
			game->p.p_x = new_x;
	}
	else
		game->p.p_x = new_x;
	if (game->map[(int)new_y][(int)game->p.p_x] == '1')
		return ;
	if (game->map[(int)new_y][(int)game->p.p_x] == 'D')
	{
		if (check_door(game, (int)game->p.p_x, new_y))
			game->p.p_y = new_y;
	}
	else
		game->p.p_y = new_y;
}

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dx;
	double	old_planex;

	old_dx = game->p.d_x;
	old_planex = game->p.plane_x;
	game->p.d_x = game->p.d_x * cos(rot_speed) - game->p.d_y * sin(rot_speed);
	game->p.d_y = old_dx * sin(rot_speed) + game->p.d_y * cos(rot_speed);
	game->p.plane_x = game->p.plane_x * cos(rot_speed) - game->p.plane_y
		* sin(rot_speed);
	game->p.plane_y = old_planex * sin(rot_speed) + game->p.plane_y
		* cos(rot_speed);
}

void	process_rotation(t_game *game)
{
	double	rot_speed;

	rot_speed = 0.01;
	if (game->input.rot_left)
		rotate_player(game, -rot_speed);
	if (game->input.rot_right)
		rotate_player(game, rot_speed);
}
