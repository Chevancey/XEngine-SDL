//#include "SDLEvent.h"
//
//SDLEvent* SDLEvent::s_Instance = nullptr;
//
//SDLEvent::SDLEvent()
//{
//	m_KeyStates = NULL;
//}
//
//SDLEvent::~SDLEvent()
//{
//	delete[] m_KeyStates;
//	m_KeyStates = NULL;
//}
//
//void SDLEvent::Listen()
//{
//	SDL_Event event;
//	while (SDL_PollEvent(&event)) 
//	{
//		switch (event.type) {
//			//case SDL_QUIT: SDL_Quit();
//				//break;
//			case SDL_KEYDOWN: KeyDown();
//				break;
//			case SDL_KEYUP: KeyUp();
//				break;
//		}
//	}
//}
//
//bool SDLEvent::GetKeyDown(SDL_Scancode key)
//{
//	return m_KeyStates ? m_KeyStates[key] == 1 : false;
//
//}
//
//void SDLEvent::KeyUp()
//{
//	m_KeyStates = SDL_GetKeyboardState(nullptr);
//}
//
//void SDLEvent::KeyDown()
//{
//	m_KeyStates = SDL_GetKeyboardState(nullptr);
//}  