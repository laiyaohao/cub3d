/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiatan <tiatan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:24:58 by tiatan            #+#    #+#             */
/*   Updated: 2025/07/01 15:19:04 by tiatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	else
	{
		ft_memset(&game, 0, sizeof(t_game));
		game.map_fd = -1;
		init(&game);
		parse_map(argv, &game);
		game_start(&game);
		return (0);
	}
}
