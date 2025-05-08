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
        init(&game); // initialise the structs we use
        parse_map(argv, &game);
        game_start(&game);
        //free_all(); // cleanup
        return (0);
    }
}
