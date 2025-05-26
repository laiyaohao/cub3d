#include "../../inc/cub3D.h"

int find_textiles(t_game *game, int i, int j)
{
  if (ft_strncmp(&game->map_file[i][j], "NO", 2) == 0)
    return (N_T);
  else if (ft_strncmp(&game->map_file[i][j], "SO", 2) == 0)
    return (S_T);
  else if (ft_strncmp(&game->map_file[i][j], "EA", 2) == 0)
    return (E_T);
  else if (ft_strncmp(&game->map_file[i][j], "WE", 2) == 0)
    return (W_T);
  else if (ft_strncmp(&game->map_file[i][j], "F", 1) == 0)
    return (F_T);
  else if (ft_strncmp(&game->map_file[i][j], "C", 1) == 0)
    return (C_T);
  return -1;
}

void  store_addr(t_game *game, int i, int j, int tex)
{
  int x;
  int len;
  char  *addr;
  int full_len;

  full_len = ft_strlen(game->map_file[i]);
  len = full_len - j;
  addr = malloc(len + 1);
  if (!addr)
    exit_game(game);
  x = 0;
  while (j < full_len)
  {
    addr[x] = game->map_file[i][j];
    j++;
    x++;
  }
  addr[x] = '\0';
  game->t_path[tex] = addr;
}

void  store_help(t_game *game, int i, int *tex_num)
{
  int j;
  int tex;

  j = 0;
  while (ft_isspace(game->map_file[i][j]))
    j++;
  printf("here\n");
  if (!game->map_file[i][j])
    return ;
  tex = find_textiles(game, i, j);
  if (tex == -1)
    exit_game(game);
  if (tex == 4 || tex == 5)
    j++;
  else
    j += 2;
  while (ft_isspace(game->map_file[i][j]))
    j++;
  if (!game->map_file[i][j])
    exit_game(game);
  if ((tex == 4 || tex == 5) && store_color(game, i, &j, tex) == 0)
    exit_game(game);
  else
    store_addr(game, i, j, tex);
  *tex_num += 1;
}

/**
 * check if file has all the map elements
 * i.e example, NO ./path
 * SO ./path
 * .
 * .
 * and shun bian store the map in last part of map_file in map
 */

int missing_path(t_game *game)
{
  int i;

  i = 0;
  while (i < T_COUNT)
  {
    if (!game->t_path[i])
      return (1);
    i++;
  }
  printf("finished missing path\n");
  return (0);
}

void create_map(t_game *game, int i, int j)
{
  int k;

  game->map = malloc(sizeof(char *) * (i - j + 1));
  if (!game->map)
    exit_game(game);
  k = 0;
  while (j < i)
  {
    game->map[k] = ft_strdup(game->map_file[j]);
    k++;
    j++;
  }
  game->map[k] = NULL;
}

void free_map_file(char **map_file)
{
  int i;

  i = 0;
  while (map_file[i])
  {
    free(map_file[i]);
    i++;
  }
  free(map_file);
}

void	check_f_str(t_game *game)
{
  // game->map_file is the one with all the NO ./path_to_north_texture
  // game->map has not been configured yet, need to retrieve from game->map_f
  int i;
  int tex_num;
  int j;

  i = 0;
  tex_num = 0;
  while (game->map_file[i])
  {
    store_help(game, i, &tex_num);
    i++;
    printf("tex_num: %d\n", tex_num);
    if (tex_num == 6 && missing_path(game))
      exit_game(game);
    else if (tex_num == 6)
      break;
  }
  j = i;
  i = valid_map(game, i);
  create_map(game, i, j);
  free_map_file(game->map_file);
  // game->map = malloc(sizeof(char *) * (i - j + 1));
  // if (!game->map)
  //   exit_game(game);
  // i = 0;
  // while (j < i + (i - j))
  // {
  //   game->map[i] = ft_strdup(game->map_file[j]);
  //   i++;
  //   j++;
  // }
  // game->map[i] = NULL;
}


