#include "../../inc/cub3D.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		ft_error("Error: Unable to get current time\n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
