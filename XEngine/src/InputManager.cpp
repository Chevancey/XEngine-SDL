#include "InputManager.h"

InputManager* InputManager::s_Instance = nullptr;

void InputManager::Listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            //case SDL_QUIT: SDL_Quit();
                //break;
        case SDL_KEYDOWN: KeyDown();
            break;
        case SDL_KEYUP: KeyUp();
            break;
        }
    }
}

void InputManager::BindKeyPressed(SDL_Keycode key, const std::string& keyname)
{
    m_inputSystem.insert({keyname, key});

    for (auto it = m_inputSystem.begin(); it != m_inputSystem.end(); it++)
    {
        std::cout << it->first << " was bound to: " << it->second << std::endl;
    }
}

void InputManager::BindMouseButtonPressed(Mouse_Button id, const std::string& keyname)
{
    m_inputSystem.insert({keyname, id });

    for (auto it = m_inputSystem.begin(); it != m_inputSystem.end(); it++)
    {
        std::cout << it->first << " was bound to: " << it->second << std::endl;
    }
}

void InputManager::OnAction(const std::string& keyname, std::function<void()> func)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        std::cout << keyname << " Has been Triggered" << std::endl;
        auto actionIterator = m_actionSystem.find(keyname);
        auto inputIterator = m_inputSystem.find(keyname);
        if (m_actionSystem.size() > 0 && m_inputSystem.size())
        {
            if (actionIterator != m_actionSystem.end() && inputIterator != m_inputSystem.end())
            {
                if (actionIterator->first == keyname && event.type == inputIterator->second)
                {
                    std::cout << actionIterator->first << " Has been Triggered" << std::endl;
                    actionIterator->second;
                }
            }
        }
        else
        {
            func();
            m_actionSystem.insert({ keyname, func });
        }
    }
}

bool InputManager::GetKeyDown(SDL_Keycode key)
{
    return m_KeyStates ? m_KeyStates[key] == 1 : false;
}

void InputManager::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void InputManager::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}