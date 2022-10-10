#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <memory>
#include <list>
#include <map>
#include <vector>

#include "SDLpp.h"
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "SDLEvent.h"
#include "SDLTexture.h"
#include "SDLUtility.h"
#include "SDLTime.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Transform.h"
#include "InputManager.h"

#include  <imgui.h>
#include  <imgui_impl_sdl.h>
#include  <imgui_impl_sdlrenderer.h>
#include  <entt/entt.hpp>

void Animation(Sprite* sprite, int animationIndex, float timer, int frameIndex, int frameCount);


//Lesson 1
int main(int argc, char** argv)
{
    SDLpp sdl;
    SDLUtility sdlutility;
    SDLTime Time;

    if (TTF_Init() < 0)
    {
        std::cout << "Error: " << TTF_GetError() << std::endl;
    }

    SDLWindow window("XEngine", 1200, 720);

    SDLRenderer renderer(window);
    ResourceManager resourceManager(renderer);

    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window.get(), renderer.get());
    ImGui_ImplSDLRenderer_Init(renderer.get());

    auto backgroundtText = ResourceManager::Instance().GetTexture("assets/Background.png");
    
    auto spriteTexture = ResourceManager::Instance().GetTexture("assets/Runner.png");
    auto spriteTexture2 = ResourceManager::Instance().GetTexture("assets/kirby.png");

    Sprite background(backgroundtText);
    Sprite sprite(spriteTexture, { 0, 0, 32, 32 });

    Transform transform;
    Transform spriteTransform;
    InputManager inputManager;
    
    sprite.Resize(704, 64);
    sprite.SetRect(SDL_Rect{ 0, 0, 64, 64 });

    float x = 0;
    float y = 0;
    int w = 250;
    int h = 250;

    Uint8 color[]
    {
        127, 0, 127, 255
    };

    int frameCount = 5;
    int frameIndex = 0;
    float timer = 0;

    InputManager::Instance().BindKeyPressed(
        SDLK_d, "MoveRight");

    bool isOpen = true;
    while(isOpen)
    {
        Time.CountDeltaTime();
        timer += Time.getDeltaTime();
        SDL_Event event;

        while (SDLpp::PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isOpen = false;

            ImGui_ImplSDL2_ProcessEvent(&event);

            InputManager::Instance().HandleEvent(event);
        }

        float scale;
        
        if (InputManager::Instance().IsActive("MoveRight"))
        {
            scale += 0.1f * Time.getDeltaTime();
            spriteTransform.SetScale(Vector2f(scale, scale));
            //transformParent.Translate(Vector2f(500.f * deltaTime, 0.f));
            //transformParent.Rotate(30.f * deltaTime);
        }

        if (timer > 0.1f)
        {
            timer -= 0.1f;
            frameIndex++;

            if (frameIndex >= frameCount)
            {
                frameIndex = 0;
            }

            //std::cout << frameIndex << std::endl;

            sprite.SetRect({ frameIndex * 32, 0, 32, 32 });
        }

        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        renderer.SDLDrawBG(color);
        renderer.Clear();
        background.Draw(renderer, spriteTransform);

        background.Resize(window.GetWindowSizeX(), window.GetWindowSizeY());
        sprite.Draw(renderer, transform);

            ImGui::Render();
            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

        sprite.Resize(w, h);

        renderer.Present();
    }

    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

void Animation(Sprite* sprite, int animationIndex, float timer, int frameIndex, int frameCount)
{
    if (timer > 0.1f)
    {
        timer -= 0.1f;
        frameIndex++;

        if (frameIndex >= frameCount)
        {
            frameIndex = 0;
        }

        //std::cout << frameIndex << std::endl;

        sprite->SetRect({ frameIndex * 32, 32 * animationIndex, 32, 32 });
    }
}