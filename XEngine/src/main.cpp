#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <memory>
#include <list>
#include <map>
#include <vector>
#include <fstream>

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
#include "Model.h"

#include  <imgui.h>
#include  <imgui_impl_sdl.h>
#include  <imgui_impl_sdlrenderer.h>
#include  <entt/entt.hpp>
#include  <chipmunk/chipmunk.h>
void Animation(Sprite* sprite, int animationIndex, float timer, int frameIndex, int frameCount);

struct Position 
{
    Vector2f pos;
};

struct VelocityComponent
{
    Vector2f vel;
};

struct SpriteRenderer
{
    Sprite* sprite;
};

void RendererStystem(entt::registry& registry, SDLRenderer& renderer) 
{
    auto view = registry.view<SpriteRenderer, Transform>();
    for (entt::entity e : view)
    {
        auto& sprite = view.get<SpriteRenderer>(e);
        auto& transform = view.get<Transform>(e);

        sprite.sprite->Draw(renderer, transform);
    }
}

void VelocitySystem(entt::registry& registry, int TimePassed)
{
    float factor = std::exp(-TimePassed);

    auto view = registry.view<Transform, VelocityComponent>();
    for (entt::entity e : view)
    {
        auto& position = view.get<Transform>(e);
        auto& velocity = view.get<VelocityComponent>(e);
        position.Translate(position.GetGlobalPosition() + velocity.vel * TimePassed);
        velocity.vel *= factor;
        std::cout << position.GetGlobalPosition().x << ", " << position.GetGlobalPosition().y << std::endl;
    }
}

//void VelocityStystem(entt::registry& registry, int TimePassed)
//{
//    float factor = std::exp(-TimePassed);
//
//    auto view = registry.view<Transform, VelocityComponent>();
//    for (entt::entity e : view)
//    {
//        auto& enitityPos = view.get<Transform>(e);
//        auto& enitityVel = view.get<VelocityComponent>(e);
//        enitityPos.Translate(GetGlobalPosition()) += enitityVel.vel * TimePassed;
//        enitityVel.vel *= factor;
//    }
//}

//Lesson 1
int main(int argc, char** argv)
{
    //ENTT
    entt::registry registry;
    entt::entity entity = registry.create();

    SpriteRenderer& entitySprite = registry.emplace<SpriteRenderer>(entity);
    Transform& entityTransform = registry.emplace<Transform>(entity);
    VelocityComponent& entityVelocity = registry.emplace<VelocityComponent>(entity);
    entityVelocity.vel = Vector2f(1.f,0.f);

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
    //auto spriteTexture2 = ResourceManager::Instance().GetTexture("assets/kirby.png");

    Sprite background(backgroundtText);
    Sprite sprite(spriteTexture, { 0, 0, 32, 32 });

    Transform transform;
    Transform spriteTransform;
    InputManager inputManager;

    // testing both reading and writing
    Model model("assets/example.model");
    model.SetTexture("assets/Runner.png");
    model.SetModel("assets/NEW_example.model");
    model.SaveModel();
    Model model2("assets/NEW_example.model");

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
    InputManager::Instance().BindKeyPressed(
        SDLK_w, "MoveUp");
    InputManager::Instance().BindKeyPressed(
        SDLK_a, "MoveLeft");
    InputManager::Instance().BindKeyPressed(
        SDLK_s, "MoveDown");

    entitySprite.sprite = &sprite;

    //float Xpos;
    //float Ypos;

    bool isOpen = true;
    while(isOpen)
    {
        entityTransform = transform;
        //entityPosition.pos = transform;
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

        
        //if (InputManager::Instance().IsActive("MoveRight"))
        //{
        //    Xpos += 500.f * Time.getDeltaTime();
        //    transform.SetPosition(Vector2f(Xpos, Ypos));
        //}
        //if (InputManager::Instance().IsActive("MoveDown"))
        //{
        //    Ypos += 500.f * Time.getDeltaTime();
        //    transform.SetPosition(Vector2f(Xpos, Ypos));
        //}
        //if (InputManager::Instance().IsActive("MoveLeft"))
        //{
        //    Xpos -= 500.f * Time.getDeltaTime();
        //    transform.SetPosition(Vector2f(Xpos, Ypos));
        //}
        //if (InputManager::Instance().IsActive("MoveUp"))
        //{
        //    Ypos -= 500.f * Time.getDeltaTime();
        //    transform.SetPosition(Vector2f(Xpos, Ypos));
        //}

        VelocitySystem(registry, timer);

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
        RendererStystem(registry, renderer);

        model.Draw(renderer);
        model2.Draw(renderer);
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