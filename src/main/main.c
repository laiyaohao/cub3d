#include "../../inc/cub3D.h"

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return (1);
    }
    else
    {
        printf("Game Start\n");
        init(); // initialise the structs we use
        check_file(); // check the file extension as well as permission 
        parse_map(); // check the map if it is valid, then store it in the game struct as well as the player position and direction
        game_start(); // render the map via raycasting and start the loop
        free_all(); // cleanup
        return (0);
    }
}
