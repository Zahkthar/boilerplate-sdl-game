#ifndef INPUT_MANAGER_HPP_INCLUDED
#define INPUT_MANAGER_HPP_INCLUDED

#include <unordered_map>
#include <utility>

#include <SDL2/SDL.h>

class InputManager
{
public:
    // Global
    void updateKeyboard(SDL_KeyboardEvent &event);
    void updateMouse(SDL_Event &event);

    // Mouse
    bool isMouseButtonPressed(Uint32 button);
    std::pair<int, int> getMousePositionAbsolute();
    std::pair<int, int> getMousePosition();
    void setMousePositionAbsolute(int x, int y);
    void setMousePosition(SDL_Window *window, int x, int y);

    // Keyboard
    bool isKeyboardKeyPressed(SDL_KeyCode key);

private:
    // Mouse
    std::unordered_map<int, bool> mouseState;
    int mousePosX;
    int mousePosY;

    // Keyboard
    std::unordered_map<SDL_Scancode, bool> keyboardState;
};

#endif // INPUT_MANAGER_HPP_INCLUDED