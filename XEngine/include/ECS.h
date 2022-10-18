#include<entt/entt.hpp>
#include"Vector2.h"
#include"SDLRenderer.h"
#include"Sprite.h"

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

class Scene 
{
public:

    void RendererStystem(entt::registry& registry, SDLRenderer& renderer);
    void VelocitySystem(entt::registry& registry, float TimePassed);

private:

};

