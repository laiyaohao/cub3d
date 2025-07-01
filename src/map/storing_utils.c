/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylai <ylai@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:39:34 by ylai              #+#    #+#             */
/*   Updated: 2025/07/01 15:36:53 by ylai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	store_result(int *j, int k, int sign, int *result)
{
	if (sign == -1)
		*result = *result * -1;
	else if ((*j - k) == 0)
		*result = 256;
	return (*result);
}

int	parse_integer(t_game *game, int i, int *j, int *result)
{
	int	sign;
	int	k;

	*result = 0;
	sign = 1;
	while (ft_isspace(game->map_file[i][*j]))
		*j += 1;
	k = *j;
	while ((game->map_file[i][*j] >= 9 && game->map_file[i][*j] <= 13)
		|| game->map_file[i][*j] == 32)
		*j += 1;
	if (game->map_file[i][*j] == '-' || game->map_file[i][*j] == '+')
	{
		if (game->map_file[i][*j] == '-')
			sign = -1;
		*j += 1;
	}
	while (game->map_file[i][*j] >= '0' && game->map_file[i][*j] <= '9')
	{
		*result = *result * 10 + (game->map_file[i][*j] - 48);
		*j += 1;
		if ((*j - k) >= 5)
			return (256);
	}
	return (store_result(j, k, sign, result));
}
