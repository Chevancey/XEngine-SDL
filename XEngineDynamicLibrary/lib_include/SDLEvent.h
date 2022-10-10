//#pragma once
//#include <SDL.h>
//#include <iostream>
//#include <LIB_COMPILING.h>
//
//class LIB_API SDLEvent
//{
//public:
//
//	static SDLEvent* GetInstance()
//	{
//		return s_Instance = (s_Instance != nullptr) ? s_Instance : new SDLEvent();
//	}
//	
//	void Listen();
//	bool GetKeyDown(SDL_Scancode key);
//private:
//	SDLEvent();
//	~SDLEvent();
//
//
//	void KeyUp();
//	void KeyDown();
//
//	const Uint8* m_KeyStates;
//	static SDLEvent* s_Instance;
//
//};