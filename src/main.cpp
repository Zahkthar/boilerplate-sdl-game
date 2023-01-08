#include <iostream>

#include "Game.hpp"
#include "config.hpp"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    Game game;

    if(game.init(SCREEN_TITLE, SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, IS_GAME_FULLSCREEN) != 0)
    {
        return 1;
    }

    game.run();

    return 0;
}