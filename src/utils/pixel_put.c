/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:27:31 by tiatan            #+#    #+#             */
/*   Updated: 2025/06/30 19:27:32 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	pixel_put(t_game *game, int x, int y, int color)
{
	char	*dest;

	dest = game->img.data + (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dest = color;
}
