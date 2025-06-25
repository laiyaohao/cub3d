#include "../../inc/cub3D.h"

int main(int argc, char **argv)
{
    t_game      game;

    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return (1);
    }
    else
    {
        ft_memset(&game, 0, sizeof(t_game));
        init(&game); // initialise values which should be obtained from parsing the map
        parse_map(argv, &game);
        int i = 0;
        while(game.map[i])
        {
            printf("%s\n", game.map[i]);
            i++;
        }
        game_start(&game);
        return (0);
    }
}
