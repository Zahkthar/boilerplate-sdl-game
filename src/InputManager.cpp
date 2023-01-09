#include "InputManager.hpp"

/*
 * Callbacks
 */

void InputManager::setMouseCallback(Uint32 eventType, std::function<void(void *, Uint8)> callbackFunction, void *thisPtr)
{
    mouseCallbacks[eventType].first = callbackFunction;
    mouseCallbacks[eventType].second = thisPtr;
}

void InputManager::setKeyboardCallback(Uint32 eventType, std::function<void(void *, Uint8)> callbackFunction, void *thisPtr)
{
    keyboardCallbacks[eventType].first = callbackFunction;
    mouseCallbacks[eventType].second = thisPtr;
}

void InputManager::clearCallbacks()
{
    mouseCallbacks.clear();
    keyboardCallbacks.clear();
}

/*
 * Mouse
 */

void InputManager::updateMouse(SDL_Event &event)
{
    if(event.type == SDL_MOUSEMOTION)
    {
        mousePosX = event.motion.x;
        mousePosY = event.motion.y;
    }
    else // SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP
    {
        mouseState[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN) ? true : false;
    }

    if(mouseCallbacks.contains(event.type))
    {
        mouseCallbacks[event.type].first(mouseCallbacks[event.type].second, event.button.button);
    }
}

bool InputManager::isMouseButtonPressed(Uint32 button)
{
    return mouseState[button];
}

std::pair<int, int> InputManager::getMousePositionAbsolute()
{
    int x = 0;
    int y = 0;

    SDL_GetGlobalMouseState(&x, &y);
    
    return std::make_pair(x, y);
}

std::pair<int, int> InputManager::getMousePosition()
{
    return std::make_pair(mousePosX, mousePosY);
}

void InputManager::setMousePositionAbsolute(int x, int y)
{
    SDL_WarpMouseGlobal(x, y);
}

void InputManager::setMousePosition(SDL_Window *window, int x, int y)
{
    SDL_WarpMouseInWindow(window, x, y);
}

/*
 * Keyboard
 */

void InputManager::updateKeyboard(SDL_KeyboardEvent &event)
{
    keyboardState[event.keysym.scancode] = (event.type == SDL_KEYDOWN) ? true : false;

    if(keyboardCallbacks.contains(event.type))
    {
        keyboardCallbacks[event.type].first(keyboardCallbacks[event.type].second, event.keysym.scancode);
    }
}

bool InputManager::isKeyboardKeyPressed(SDL_KeyCode key)
{
    return keyboardState[SDL_GetScancodeFromKey(key)];
}