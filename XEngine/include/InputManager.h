#pragma once

#include <sdl.h>
#include <string>
#include <functional>
#include <map>

enum MouseButton
{
    LeftClick = SDL_BUTTON_LEFT,
    RightClick = SDL_BUTTON_RIGHT,
    Middle = SDL_BUTTON_MIDDLE
};

class InputManager
{
public:

    ~InputManager();

    void BindKeyPressed(SDL_Keycode key, const std::string keyname);
    void BindMouseButtonPressed(MouseButton, const std::string keyname);
    void OnAction(const std::string keyname, std::function<void()> func);

    void KeyPress(SDL_Event event);
    void MousePress(SDL_Event event);

    bool IsBindIsPossible(const std::string keyname);

    static InputManager* GetInstance()
    {
        return m_instance = (m_instance != nullptr) ? m_instance : new InputManager;
    }

private:
    InputManager() = default;

    static InputManager* m_instance;

    std::map<int, std::string> m_mouseSystem;
    std::map<SDL_Keycode, std::string> m_bindSystem;
    std::map<std::string, std::function<void()>> m_actionSystem;
};