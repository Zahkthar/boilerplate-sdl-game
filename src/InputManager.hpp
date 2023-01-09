#ifndef INPUT_MANAGER_HPP_INCLUDED
#define INPUT_MANAGER_HPP_INCLUDED

#include <unordered_map>
#include <functional>
#include <utility>

#include <SDL2/SDL.h>

class InputManager
{
public:
    // Callbacks
    void setMouseCallback(Uint32 eventType, std::function<void(void *, Uint8)> callbackFunction, void *thisPtr);
    void setKeyboardCallback(Uint32 eventType, std::function<void(void *, Uint8)> callbackFunction, void *thisPtr);
    void clearCallbacks();

    // Mouse
    void updateMouse(SDL_Event &event);

    bool isMouseButtonPressed(Uint32 button);
    std::pair<int, int> getMousePositionAbsolute();
    std::pair<int, int> getMousePosition();
    void setMousePositionAbsolute(int x, int y);
    void setMousePosition(SDL_Window *window, int x, int y);

    // Keyboard
    void updateKeyboard(SDL_KeyboardEvent &event);

    bool isKeyboardKeyPressed(SDL_KeyCode key);

private:
    // Mouse
    std::unordered_map<int, bool> mouseState;
    std::unordered_map<int, std::pair<std::function<void(void *, Uint8)>, void *>> mouseCallbacks;

    int mousePosX;
    int mousePosY;

    // Keyboard
    std::unordered_map<SDL_Scancode, bool> keyboardState;
    std::unordered_map<int, std::pair<std::function<void(void *, SDL_Scancode)>, void *>> keyboardCallbacks;
};

#endif // INPUT_MANAGER_HPP_INCLUDED