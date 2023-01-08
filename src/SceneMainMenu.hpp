#ifndef MAIN_MENU_SCENE_HPP_INCLUDED
#define MAIN_MENU_SCENE_HPP_INCLUDED

#include <iostream>

#include <SDL2/SDL.h>

#include "RessourceManager.hpp"
#include "InputManager.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"

#include "config.hpp"

class SceneMainMenu : public Scene
{
public:
    SceneMainMenu(SDL_Window *window, SDL_Renderer **renderer, SceneManager &sceneManager, RessourceManager &ressourceManager, InputManager &inputManager)
	: Scene(window, renderer, sceneManager, ressourceManager, inputManager) { }

	void initScene();
	void cleanScene();

	void update(float deltaTime);
	void render();
	
private:
	SDL_Color mainMenuBackgroundColor = { 30, 74, 32, 255 };

	SDL_Rect chessBoardRect;
	SDL_Rect textRect;
};

#endif // MAIN_MENU_SCENE_HPP_INCLUDED
