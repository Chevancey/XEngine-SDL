//#include <SDL.h>
//#include <SDL_image.h>
//#include <iostream>
//#include <string>
//#include <functional>
//#include <map>
//
//class InputManager
//{
//public:
//    InputManager(const InputManager&) = delete;
//    InputManager(InputManager&&) noexcept;
//
//    ~InputManager();
//
//    void BindKeyPressed(SDL_Keycode key, std::string& keyname);
//    void BindMouseButtonPressed(Uint8 id, std::string& keyname);
//    void OnAction(std::string& keyname, std::function<void()> func);
//
//    //void Attack();
//    //void Jump();
//    //void Run();
//
//    InputManager& operator=(const InputManager&) = delete;
//    //InputManager& operator=(InputManager&&) noexcept;
//
//private:
//    //InputManager* m_input;
//
//    enum MouseButton
//    {
//        LeftClick = SDLK_0,
//        RightClick = SDLK_1,
//        Middle = SDLK_2
//    };
//
//    std::map<std::string, SDL_Keycode> m_inputSystem
//    {
//        {"attack", SDLK_0},
//        {"jump", SDLK_SPACE},
//        {"run", SDLK_RSHIFT}
//    };
//};