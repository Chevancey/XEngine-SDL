//#include "InputManager.h"
//
//void InputManager::BindKeyPressed(SDL_Keycode key, std::string& keyname)
//{
//    m_inputSystem.at(keyname) = key;
//}
//
//void InputManager::BindMouseButtonPressed(Uint8 id, std::string& keyname)
//{
//    m_inputSystem.at(keyname) = id;
//}
//
//void InputManager::OnAction(std::string& keyname, std::function<void()> func)
//{
//    //switch statement = > case = update func delegate + call func
//
//    //std::function<void()> function = Attack;
//
//    if (keyname == "Attack")
//        func = Attack;
//    else if (keyname == "Jump")
//        func = Jump;
//    else if (keyname == "Run")
//        func = Run;
//    else
//        return;
//
//    func();
//}