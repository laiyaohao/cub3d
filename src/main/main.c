#include "../../inc/cub3D.h"

int main(int argc, char **argv)
{
    t_game      game;
    t_mlx       mlx;
    t_player    p;

    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return (1);
    }
    else
    {
        init(&game, &p, &mlx); // initialise the structs we use
        parse_map(argv, &game);
        game_start(&game); // render the map via raycasting and start the loop
        //free_all(); // cleanup
        return (0);
    }
}
