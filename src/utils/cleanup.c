/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:27:21 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:27:22 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	free_2d(void **content)
{
	int	i;

	i = 0;
	if (!content)
		return ;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
}

void	cleanup(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_2d((void **)game->map);
	if (game->t_path)
		free_2d((void **)game->t_path);
	if (game->doors)
		free_2d((void **)game->doors);
	if (game->s_path)
		free_2d((void **)game->s_path);
	if (game->b_path)
		free_2d((void **)game->b_path);
	if (game->map_file)
		free_2d((void **)game->map_file);
}
