#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <SDL2/SDL.h>

// CONFIG CONSTANTS
static const char *SCREEN_TITLE = "Boilerplate-SDL-Game";

#define SCREEN_POS_X SDL_WINDOWPOS_CENTERED
#define SCREEN_POS_Y SDL_WINDOWPOS_CENTERED

static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 720;

static const bool IS_GAME_FULLSCREEN = false;

static const int TARGET_FRAMERATE = 60;

#endif // CONFIG_HPP_INCLUDED