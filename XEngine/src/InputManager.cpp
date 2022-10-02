#include <InputManager.h>
#include <iostream>

InputManager* ::InputManager::m_instance = nullptr;

void InputManager::BindKeyPressed(SDL_Keycode key, const std::string keyname)
{
    m_bindSystem.emplace(key, keyname);
}

void InputManager::BindMouseButtonPressed(MouseButton id, const std::string keyname)
{
    m_mouseSystem.emplace(id, keyname);
}

void InputManager::OnAction(const std::string keyname, std::function<void()> func)
{
    auto it = m_actionSystem.find(keyname);

    if (it == m_actionSystem.end())
    {
        m_actionSystem.emplace(keyname, func);
    }
    else
    {
        it->second = func;
    }
}

void InputManager::KeyPress(SDL_Event event)
{
    auto it = m_bindSystem.find(event.key.keysym.sym);

    if (it != m_bindSystem.end())
    {
        m_actionSystem[m_bindSystem[event.key.keysym.sym]]();
    }
}

void InputManager::MousePress(SDL_Event event)
{
    auto it = m_mouseSystem.find(event.button.button);

    if (it != m_mouseSystem.end())
    {
        m_actionSystem[m_mouseSystem[event.button.button]]();
    }
}

//InputManager* InputManager::GetInstance()
//{
//    return m_instance = (m_instance != nullptr) ? m_instance : new InputManager;
//}