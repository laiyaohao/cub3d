/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:27:26 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:27:27 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < T_COUNT)
	{
		if (game->t[i].image)
			mlx_destroy_image(game->mlx.mlx_ptr, game->t[i].image);
		i++;
	}
	i = 0;
	while (i < FRAMES)
	{
		if (game->s[i].image)
			mlx_destroy_image(game->mlx.mlx_ptr, game->s[i].image);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (game->b[i].image)
			mlx_destroy_image(game->mlx.mlx_ptr, game->b[i].image);
		i++;
	}
}

int	exit_game(t_game *game)
{
	destroy_images(game);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.img_ptr);
	if (game->mlx.mlx_win)
	{
		mlx_clear_window(game->mlx.mlx_ptr, game->mlx.mlx_win);
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.mlx_win);
	}
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
	cleanup(game);
	exit(0);
}
