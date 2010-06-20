#include <stdio.h>
#include <GL/glfw.h>

#include "kernel.h"
#include "game.h"
#include "actors/player.h"

int main(void)
{
    game_s *game = make_game();

    make_player(game);

    kernel_start(game_scene(game));

    release_game(game);
    game = NULL;

    return 0;
}
