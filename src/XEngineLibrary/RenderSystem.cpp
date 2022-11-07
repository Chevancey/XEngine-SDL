#include <RenderSystem.h>
#include <CameraComponent.h>
#include <GraphicsComponent.h>
#include <Renderable.h>
#include <Transform.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <entt/entt.hpp>

RenderSystem::RenderSystem(SDLRenderer& renderer, entt::registry& registry) :
	m_renderer(renderer),
	m_registry(registry)
{
}

void RenderSystem::Update(float /*deltaTime*/)
{
	// S�lection de la cam�ra
	const Transform* cameraTransform = nullptr;
	auto cameraView = m_registry.view<Transform, CameraComponent>();
	for (entt::entity entity : cameraView)
	{
		// Nous avons d�j� une cam�ra ?
		if (cameraTransform)
			fmt::print(stderr, fg(fmt::color::red), "warning: multiple camera found\n");

		Transform& entityTransform = cameraView.get<Transform>(entity);
		cameraTransform = &entityTransform;
	}

	if (!cameraTransform)
	{
		fmt::print(stderr, fg(fmt::color::red), "warning: no camera found\n");
		return;
	}

	auto view = m_registry.view<Transform, GraphicsComponent>();
	for (entt::entity entity : view)
	{
		Transform& entityTransform = view.get<Transform>(entity);
		GraphicsComponent& entityGraphics = view.get<GraphicsComponent>(entity);

		entityGraphics.renderable->Draw(m_renderer, *cameraTransform, entityTransform);
	}
}