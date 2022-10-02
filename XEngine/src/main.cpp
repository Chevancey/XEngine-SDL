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
#include "MemoryManager.h"
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Transform.h"
#include "InputManager.h"

void Animation(Sprite* sprite, int animationIndex, float timer, int frameIndex, int frameCount);

//Lesson 1
int main(int argc, char** argv)
{
    SDLpp sdl;
    SDLUtility sdlutility;
    SDLTime Time;


    //int a[3] = { 1,2,3 };

    if (TTF_Init() < 0)
    {
        std::cout << "Error: " << TTF_GetError() << std::endl;
    }

    SDLWindow window("XEngine", 1200, 720);

    SDLRenderer renderer(window);

    auto backgroundtText = MemoryManager::GetInstance()->getTexture(renderer, "assets/Background.png");
    //auto backgroundtText2 = MemoryManagement::GetInstance()->getTexture(renderer, "assets/Background.png");
    //auto backgroundtText3 = MemoryManagement::GetInstance()->getTexture(renderer, "assets/Background.png");
    
    auto spriteTexture = MemoryManager::GetInstance()->getTexture(renderer, "assets/Runner.png");
    auto spriteTexture2 = MemoryManager::GetInstance()->getTexture(renderer, "assets/kirby.png");
    //auto spriteTexture3 = MemoryManager::GetInstance()->getTexture(renderer, "assets/knight shovel.png");

    Sprite background(backgroundtText);
    Sprite sprite(spriteTexture, { 0, 0, 32, 32 }, 5, 0);
    Sprite sprite1(spriteTexture, { 0, 0, 32, 32 }, 5, 0);
    Sprite sprite2(spriteTexture, { 0, 0, 32, 32 }, 5, 0);
    //Sprite sprite3(spriteTexture, { 0, 0, 32, 32 }, 5, 0);
    
    //Matrix3x3i(3,3);
    
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

    //translation test:
    
    //Transform transform;

    //transform.SetPosition(Vector2(1, 0));
    //transform.SetRotation(1.5708);

    //Vector2f(20.0, 10.20) + Vector2f(22, 10.40);
    //Vector2f(20.0, 10.20) += Vector2f(22, 10);
    //Vector2f(20.0, 10.20) - Vector2f(22, 10.40);
    //Vector2f(20.0, 10.20) -= Vector2f(22, 10.40);
    //Vector2f(20.0, 10.20) * 2;
    //Vector2f(20.0, 10.20) *= 2;
    //Vector2f(20.0, 10.20) / 2;
    //Vector2f(20.0, 10.20) /= 2;
    //Vector2f(20.0, 10.20) == Vector2f(20.0, 10.20);
    //Vector2f(20.0, 10.20) == Vector2f(22, 10.40);
    //Vector2f(20.0, 10.20) != Vector2f(22, 10.40);
    //Vector2f(20.0, 10.20) != Vector2f(20.0, 10.20);

    //Matrix3x3f();

    

    InputManager::GetInstance()->BindMouseButtonPressed(LeftClick, "attack");
    InputManager::GetInstance()->BindKeyPressed(0, "attack");


    Transform transform;

    transform.SetPosition(Vector2f(1, 0));
    transform.SetRotation(180);
    transform.SetScale(Vector2f(2,2));
    transform.TransformPoint(Vector2f(22.1, 10.1));

   // Transform translate;
    //translate.SetPosition(Vector2f(1,0));
    //translate.SetRotation(1.5708);

    bool isOpen = true;
    while(isOpen)
    {

        SDL_Event event;
        Time.CountDeltaTime();
        timer += Time.getDeltaTime();

        //while (SDLpp::PollEvent(&event)) {
        //    if (event.type == SDL_QUIT)
        //    {
        //        MemoryManager::GetInstance()->Purge();
        //        isOpen = false;
        //    }
        //}

        InputManager::GetInstance()->Listen();
        InputManager::GetInstance()->OnAction("attack", [&]()
            {
                x -= Time.getDeltaTime();
            }
        );

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

        //SDLEvent::GetInstance()->Listen();

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
        //{
        //    x -= 1000 * Time.getDeltaTime();
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
        //{
        //    x += 1000 * Time.getDeltaTime();
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
        //{
        //    y += 1000 * Time.getDeltaTime();
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
        //{
        //    y -= 1000 * Time.getDeltaTime();
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_UP))
        //{
        //    h -= 1;
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN))
        //{
        //    h += 1;
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))
        //{
        //    w += 1;
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))
        //{
        //    w -= 1;
        //}

        //if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        //{
        //    isOpen = false;
        //}

        renderer.SDLDrawBG(color);

        if (!SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
        {
            renderer.Clear();
            background.Draw(renderer, 0, 0);
        }
        
        background.Resize(window.GetWindowSizeX(), window.GetWindowSizeY());
        sprite.Draw(renderer, x, y);
        //sprite.Animate(Time.getDeltaTime());
        sprite.Resize(w, h);

        renderer.Present();
    }
    //rm.Purge();
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

//main


//SDLTexture cat1 = SDLTexture::LoadFromFile(renderer, "assets/Cat/1.png");
//SDLTexture cat2 = SDLTexture::LoadFromFile(renderer, "assets/Cat/2.png");
//SDLTexture cat3 = SDLTexture::LoadFromFile(renderer, "assets/Cat/3.png");
//SDLTexture cat4 = SDLTexture::LoadFromFile(renderer, "assets/Cat/4.png");
//SDLTexture cat5 = SDLTexture::LoadFromFile(renderer, "assets/Cat/5.png");
//SDLTexture cat6 = SDLTexture::LoadFromFile(renderer, "assets/Cat/6.png");
//SDLTexture cat7 = SDLTexture::LoadFromFile(renderer, "assets/Cat/7.png");
//SDLTexture cat8 = SDLTexture::LoadFromFile(renderer, "assets/Cat/8.png");

//Sprite spriteCat1(cat1);
//Sprite spriteCat2(cat2);
//Sprite spriteCat3(cat3);
//Sprite spriteCat4(cat4);
//Sprite spriteCat5(cat5);
//Sprite spriteCat6(cat6);
//Sprite spriteCat7(cat7);
//Sprite spriteCat8(cat8);

//float b = 0;

// While loop


//switch ((int)b)
//{
//case(0):
//    spriteCat1.Draw(renderer, x, y);
//    break;
//case(1):
//    spriteCat2.Draw(renderer, x, y);
//    break;
//case(2):
//    spriteCat3.Draw(renderer, x, y);
//    break;
//case(3):
//    spriteCat4.Draw(renderer, x, y);
//    break;
//case(4):
//    spriteCat5.Draw(renderer, x, y);
//    break;
//case(5):
//    spriteCat6.Draw(renderer, x, y);
//    break;
//case(6):
//    spriteCat7.Draw(renderer, x, y);
//    break;
//case(7):
//    spriteCat6.Draw(renderer, x, y);
//    break;
//case(8):
//    spriteCat5.Draw(renderer, x, y);
//    break;
//case(9):
//    spriteCat4.Draw(renderer, x, y);
//    break;
//case(10):
//    spriteCat3.Draw(renderer, x, y);
//    break;
//case(11):
//    spriteCat2.Draw(renderer, x, y);
//    break;
//case(12):
//    spriteCat1.Draw(renderer, x, y);
//    break;
//default:
//    b = 0;
//    break;
//}
//b += 0.01;









// Lesson 2 pointers and refferences

//simple example

//int main(int argc, char** argv)
//{
//    {
//    int a = 42;
//    int& b = a;
//    int c = 0;
//
//    b = c;
//
//    std::cout << a << std::endl;
//
//    }
//    
//    {
//
//    int a = 42;
//    int* b = &a;
//    int c = 0;
//
//    *b = c;
//    b = &c;
//
//    std::cout << a << std::endl;
//    }
//
//    return 0;
//}


//struct Caracteristiques
//{
//    int healthMax;
//};
//
//class FichePersonnage
//{
//public:
//    FichePersonnage(const std::string& name, const Caracteristiques& carac) :
//        m_caracteristiques(carac),
//        m_name(name)
//    {
//        std::cout << "Constructeur FichePersonnage" << std::endl;
//    }
//
//    const Caracteristiques& GetCaracteristiques() const
//    {
//        return m_caracteristiques;
//    }
//
//    const std::string& GetName() const
//    {
//        return m_name;
//    }
//    void SetName(std::string& name)
//    {
//        this->m_name = name;
//    }
//
//private:
//    const Caracteristiques& m_caracteristiques;
//    std::string m_name;
//};
//
//int main()
//{
//    Caracteristiques carac;
//    carac.healthMax = 100;
//
//    FichePersonnage personnage("SirLynix", carac);
//    std::cout << personnage.GetCaracteristiques().healthMax << std::endl;
//
//    carac.healthMax = 200;
//
//    std::cout << personnage.GetCaracteristiques().healthMax << std::endl;
//
//    std::cout << personnage.GetCaracteristiques().healthMax << std::endl;
//
//    return 0;
//}

//int main(int argc, char** argv)
//{
//    SDLpp sdl;
//
//    const int FPS = 60;
//    const int frameDelay = 1000 / FPS;
//    float frameTime;
//    Uint32 startTime;
//
//
//    if (TTF_Init() < 0)
//    {
//        std::cout << "Error: " << TTF_GetError() << std::endl;
//    }
//
//    SDLWindow appWindow("XEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 720, false);
//    SDLRenderer appRenderer(appWindow);
//    bool isOpen = true;
//
//    SDL_Surface* screen = NULL;
//    TTF_Font* font = TTF_OpenFont("NITEMARE.TTF", 20);
//    SDL_Color color = { 0, 255, 0 , 255 };
//    SDL_Surface* message = TTF_RenderText_Solid(font, "XEngine", color);
//    SDL_Texture* text = SDL_CreateTextureFromSurface(appRenderer.get(), message);
//
//    SDL_Rect textRect;
//    textRect.x = textRect.y = 0;
//
//    SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
//
//    SDL_FreeSurface(message);
//    message = nullptr;
//
//    appRenderer.SDLDrawBG(127, 0, 127, 255);
//
//    while (isOpen)
//    {
//        //frameTime = (double)(frameTime - startTime);
//        startTime = SDL_GetTicks();
//
//        std::cout << frameTime << std::endl;
//        SDLEvent::GetInstance()->Listen();
//
//        if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
//        {
//            std::cout << "hello" << std::endl;
//        }
//
//        if (SDLEvent::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
//        {
//            isOpen = false;
//        }
//
//        appRenderer.Clear();
//
//        SDL_RenderCopy(appRenderer.get(), text, NULL, &textRect);
//
//        appRenderer.Present();
//        frameTime = SDL_GetTicks() - startTime;
//    }
//    text = nullptr;
//    SDL_DestroyTexture(text);
//    TTF_CloseFont;
//    TTF_Quit;
//
//    return 0;
//}