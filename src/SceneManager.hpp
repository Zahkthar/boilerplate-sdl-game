#ifndef SCENE_MANAGER_HPP_INCLUDED
#define SCENE_MANAGER_HPP_INCLUDED

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

#include "SDL2/SDL.h"

#include "Scene.hpp"

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void addScene(const std::string &name, std::unique_ptr<Scene> newScene);
    void removeScene(const std::string &name);

    void setCurrentScene(const std::string &newScene); // set "exitGame" to quit the game
    std::string getCurrentScene();

    void updateCurrentScene(float deltaTime);
    void renderCurrentScene();

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes {};
    std::string currentScene;
};

#endif // SCENE_MANAGER_HPP_INCLUDED