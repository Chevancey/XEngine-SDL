#include <SDLImGui.h>
#include <SDLRenderer.h>
#include <SDLWindow.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

SDLImGui::SDLImGui(SDLWindow& window, SDLRenderer& renderer)
{
	// Setup imgui
	IMGUI_CHECKVERSION();
	m_context = ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(window.get(), renderer.get());
	ImGui_ImplSDLRenderer_Init(renderer.get());
}

SDLImGui::~SDLImGui()
{
	// Cleanup
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext(m_context);
}

ImGuiContext* SDLImGui::GetContext()
{
	return m_context;
}

void SDLImGui::Render()
{
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void SDLImGui::NewFrame()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void SDLImGui::ProcessEvent(SDL_Event& event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}