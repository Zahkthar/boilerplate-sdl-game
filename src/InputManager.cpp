#include "InputManager.hpp"

/*
 * Callbacks
 */

void InputManager::setMouseCallback(Uint32 eventType, std::function<void(Uint8)> callbackFunction)
{
    mouseCallbacks[eventType] = callbackFunction;
}

void InputManager::setKeyboardCallback(Uint32 eventType, std::function<void(Uint8)> callbackFunction)
{
    keyboardCallbacks[eventType] = callbackFunction;
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
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        mousePosX = event.motion.x;
        mousePosY = event.motion.y;
        break;

    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
        mouseState[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN) ? true : false;
        break;
    
    default:
        break;
    }

    if(mouseCallbacks.contains(event.type))
    {
        mouseCallbacks[event.type](event.button.button);
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

void InputManager::updateKeyboard(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        keyboardState[event.key.keysym.scancode] = true;
        break;

    case SDL_KEYUP:
        keyboardState[event.key.keysym.scancode] = false;
        break;

    default:
        break;
    }

    if(keyboardCallbacks.contains(event.type))
    {
        keyboardCallbacks[event.type](event.key.keysym.scancode);
    }
}

bool InputManager::isKeyboardKeyPressed(SDL_KeyCode key)
{
    return keyboardState[SDL_GetScancodeFromKey(key)];
}