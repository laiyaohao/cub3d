/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:34:42 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:34:43 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	missing_path(t_game *game)
{
	int	i;

	i = 0;
	while (i < T_COUNT)
	{
		if (!game->t_path[i])
			return (1);
		i++;
	}
	return (0);
}

void	create_map(t_game *game, int i, int j)
{
	int	k;

	game->map = malloc(sizeof(char *) * (i - j + 1));
	if (!game->map)
	{
		ft_putstr_fd("Error: Fatal\n", 2);
		exit_game(game);
	}
	k = 0;
	while (j < i)
	{
		game->map[k] = ft_strdup(game->map_file[j]);
		k++;
		j++;
	}
	game->map[k] = NULL;
}

void	check_f_str(t_game *game)
{
	int	i;
	int	tex_num;
	int	j;

	i = 0;
	tex_num = 0;
	while (game->map_file[i])
	{
		store_help(game, i, &tex_num);
		i++;
		if (tex_num == 4 && missing_path(game))
		{
			ft_putstr_fd("Error: Missing texture paths\n", 2);
			exit_game(game);
		}
		else if (tex_num == 4)
			break ;
	}
	j = i;
	i = valid_map(game, i);
	create_map(game, i, j);
}
