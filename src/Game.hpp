#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "RessourceManager.hpp"
#include "InputManager.hpp"
#include "SceneManager.hpp"
#include "SceneMainMenu.hpp"

#include "config.hpp"

class Game
{
public:
    Game();
    ~Game();

    int init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen);
    void initManagers();

    void run();
    void update();
    void render();

    bool running();

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Uint64 frameStart;
	Uint64 frameTime;
    float deltaTime;

	std::unique_ptr<SceneManager> sceneManager {};
	std::unique_ptr<RessourceManager> ressourceManager {};
	InputManager inputManager;
};

#endif // GAME_HPP_INCLUDED