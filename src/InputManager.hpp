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
    void setMouseCallback(Uint32 eventType, std::function<void(Uint8)> callbackFunction);
    void setKeyboardCallback(Uint32 eventType, std::function<void(Uint8)> callbackFunction);
    void clearCallbacks();

    // Mouse
    void updateMouse(SDL_Event &event);

    bool isMouseButtonPressed(Uint32 button);
    std::pair<int, int> getMousePositionAbsolute();
    std::pair<int, int> getMousePosition();
    void setMousePositionAbsolute(int x, int y);
    void setMousePosition(SDL_Window *window, int x, int y);

    // Keyboard
    void updateKeyboard(SDL_Event &event);

    bool isKeyboardKeyPressed(SDL_KeyCode key);

private:
    // Mouse
    std::unordered_map<int, bool> mouseState;
    std::unordered_map<int, std::function<void(Uint8)>> mouseCallbacks;

    int mousePosX;
    int mousePosY;

    // Keyboard
    std::unordered_map<SDL_Scancode, bool> keyboardState;
    std::unordered_map<int, std::function<void(SDL_Scancode)>> keyboardCallbacks;
};

#endif // INPUT_MANAGER_HPP_INCLUDED