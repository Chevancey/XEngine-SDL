#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <functional>
#include <map>


enum Mouse_Button
{
    LeftClick = SDLK_0,
    RightClick = SDLK_1,
    Middle = SDLK_2
};


class InputManager
{
public:

    static InputManager* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new InputManager();
    }

    InputManager(InputManager&&) noexcept;


    void BindKeyPressed(SDL_Keycode key, const std::string& keyname);
    void BindMouseButtonPressed(Mouse_Button id, const std::string& keyname);
    void OnAction(const std::string& keyname, std::function<void()> func);

    InputManager& operator=(const InputManager&) = delete;

    void Listen();
    bool GetKeyDown(SDL_Keycode key);




private:
    InputManager() {}
    ~InputManager() {}

    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;

    static InputManager* s_Instance;
    //InputManager* m_input;

    std::map<std::string, SDL_Keycode> m_inputSystem;
    std::map<std::string, std::function<void()>> m_actionSystem;
};