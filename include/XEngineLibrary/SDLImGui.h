#pragma once

#include <LIB_COMPILING.h>

class SDLRenderer;
class SDLWindow;
union SDL_Event;
struct ImGuiContext;

class LIB_API SDLImGui
{
public:
	SDLImGui(SDLWindow& window, SDLRenderer& renderer);
	SDLImGui(const SDLImGui&) = delete;
	SDLImGui(SDLImGui&&) = delete;
	~SDLImGui();

	ImGuiContext* GetContext();

	void Render();

	void NewFrame();

	void ProcessEvent(SDL_Event& event);

	SDLImGui& operator=(const SDLImGui&) = delete;
	SDLImGui& operator=(SDLImGui&&) = delete;

private:
	ImGuiContext* m_context;
};