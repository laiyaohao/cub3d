#include "../../inc/cub3D.h"

void	strcjoin(int c, char **res)
{
	int		len;
	char	*temp;

	if (!(*res))
		return ;
	else
		len = ft_strlen(*res);
	temp = malloc(sizeof(char) * (len + 2));
	if (!temp)
		return ;
	len = 0;
	while ((*res)[len])
	{
		temp[len] = (*res)[len];
		len++;
	}
	temp[len] = c;
	temp[len + 1] = '\0';
	free(*res);
	*res = temp;
}
