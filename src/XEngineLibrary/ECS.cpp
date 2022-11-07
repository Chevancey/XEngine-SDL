//#include"ECS.h"
//#include"Transform.h"
//
//void Scene::RendererStystem(entt::registry& registry, SDLRenderer& renderer)
//{
//    auto view = registry.view<SpriteRenderer, Transform>();
//    for (entt::entity e : view)
//    {
//        auto& sprite = view.get<SpriteRenderer>(e);
//        auto& transform = view.get<Transform>(e);
//
//        sprite.sprite->Draw(renderer, transform);
//    }
//}
//
//void Scene::VelocitySystem(entt::registry& registry, float TimePassed)
//{
//    auto view = registry.view<Transform, VelocityComponent>();
//    for (entt::entity e : view)
//    {
//        auto& position = view.get<Transform>(e);
//        auto& velocity = view.get<VelocityComponent>(e);
//        position.Translate(position.GetGlobalPosition() + velocity.vel * TimePassed);
//        std::cout << position.GetGlobalPosition().x << ", " << position.GetGlobalPosition().y << std::endl;
//    }
//}