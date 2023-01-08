#include "SceneManager.hpp"

SceneManager::SceneManager() : scenes()
{
    
}

SceneManager::~SceneManager()
{

}

void SceneManager::addScene(const std::string &name, std::unique_ptr<Scene> newScene)
{
    scenes[name] = std::move(newScene);
}

void SceneManager::removeScene(const std::string &name)
{
    scenes.erase(name);
}

void SceneManager::setCurrentScene(const std::string &newScene)
{
    // S'il y avait une scene avant, on la clean
    if(scenes.find(currentScene) != scenes.end())
    {
        scenes[currentScene]->cleanScene();
    }

    // Changement de scene
    currentScene = newScene;

    // Initialistaion de la scene
    if(currentScene != "exitGame")
    {
        scenes[currentScene]->initScene();
    }
}

std::string SceneManager::getCurrentScene()
{
    return currentScene;
}

void SceneManager::updateCurrentScene(float deltaTime)
{
    scenes[currentScene]->update(deltaTime);
}

void SceneManager::renderCurrentScene()
{
    scenes[currentScene]->render();
}