#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <SDL2/SDL.h>

#include "SceneManager.hpp"
#include "RessourceManager.hpp"
#include "InputManager.hpp"

class SceneManager;

class Scene
{
public:
    Scene(SDL_Window *window, SDL_Renderer **renderer, SceneManager &sceneManager, RessourceManager &ressourceManager, InputManager &inputManager)
    : m_window(window), m_renderer(renderer), m_sceneManager(sceneManager), m_ressourceManager(ressourceManager), m_inputManager(inputManager) { }

    virtual ~Scene() = default;

    virtual void initScene() = 0;
    virtual void cleanScene() = 0;

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

protected:
    SDL_Window *m_window;
    SDL_Renderer **m_renderer;
    
    SceneManager &m_sceneManager;
    RessourceManager &m_ressourceManager;
    InputManager &m_inputManager;
};

#endif // SCENE_HPP_INCLUDED