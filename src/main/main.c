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
        printf("Game Start\n");
        init(&game, &p, &mlx); // initialise the structs we use
        check_file(argv, &game);
        read_map(&game);
        //parse_map(argv); // check the map if it is valid, then store it in the game struct as well as the player position and direction
        game_start(&game); // render the map via raycasting and start the loop
        //free_all(); // cleanup
        return (0);
    }
}
