/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:39 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:29:42 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	process_textures(t_game *game)
{
	int	i;

	game->img.img_ptr = mlx_new_image(game->mlx.mlx_ptr, S_WIDTH, S_HEIGHT);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	i = 0;
	while (i < T_COUNT)
	{
		game->t[i].image = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
				game->t_path[i], &game->t[i].w, &game->t[i].h);
		if (!game->t[i].image)
		{
			ft_putstr_fd("Error: Invalid texture file, please use a .xpm\n", 2);
			exit_game(game);
		}
		game->t[i].data = mlx_get_data_addr(game->t[i].image, &game->t[i].bpp,
				&game->t[i].line_len, &game->t[i].endian);
		i++;
	}
}

void	process_b_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		game->b[i].image = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
				game->b_path[i], &game->b[i].w, &game->b[i].h);
		if (!game->b[i].image)
		{
			ft_putstr_fd("Error: Invalid texture file, please use a .xpm\n", 2);
			exit_game(game);
		}
		game->b[i].data = mlx_get_data_addr(game->b[i].image, &game->b[i].bpp,
				&game->b[i].line_len, &game->b[i].endian);
		i++;
	}
}

void	process_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		game->s[i].image = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
				game->s_path[i], &game->s[i].w, &game->s[i].h);
		if (!game->s[i].image)
		{
			ft_putstr_fd("Error: Invalid texture file, please use a .xpm\n", 2);
			exit_game(game);
		}
		game->s[i].data = mlx_get_data_addr(game->s[i].image, &game->s[i].bpp,
				&game->s[i].line_len, &game->s[i].endian);
		i++;
	}
}
