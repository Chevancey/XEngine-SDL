#include <iostream>
#include <memory>
#include <list>
#include <map>
#include <vector>
#include <fstream>

//SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

//entt
#include  <entt/entt.hpp>

//Physics
#include  <chipmunk/chipmunk.h>

//ImGUI-SDL
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

//fmt
#include <fmt/core.h>

//core
#include "SDLpp.h"
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "SDLEvent.h"
#include "SDLTexture.h"
#include "SDLUtility.h"
#include "SDLTime.h"
#include "SDLImGui.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Transform.h"
#include "InputManager.h"
#include "Model.h"
#include "ECS.h"

//render
#include "RenderSystem.h"

//physics
#include "VelocitySystem.h"
#include "PhysicsSystem.h"

//animation
#include <AnimationSystem.h>
#include "Spritesheet.h"
#include "SpritesheetComponent.h"

//camera
#include <CameraComponent.h>
#include <GraphicsComponent.h>

entt::entity CreateBox(entt::registry& registry);
entt::entity CreateCamera(entt::registry& registry);
entt::entity CreateHouse(entt::registry& registry);
entt::entity CreateRunner(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet);

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity);

void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime);
void HandleRunnerMovement(entt::registry& registry, entt::entity runner, float deltaTime);

struct InputComponent
{
	bool left = false;
	bool right = false;
	bool jump = false;
};

struct PlayerControlled {};

struct PhysicsComponent
{
	cpBody* body;
	cpShape* shape;
};

template <typename A>
void display(A n[][3]) {
	std::cout << "Displaying Values: " << std::endl;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout<< n[i][j] << ",";
		}
		std::cout << std::endl;
	}
}

void PlayerControllerSystem(entt::registry& registry)
{
	auto view = registry.view<PhysicsComponent, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		auto& entityPhysics = view.get<PhysicsComponent>(entity);

		Vector2f velocity = Vector2f(0.f, 0.f);
		if (entityInput.left)
			velocity.x -= 500.f;

		if (entityInput.right)
			velocity.x += 500.f;

		if (entityInput.jump)
			cpBodyApplyImpulseAtWorldPoint(entityPhysics.body, cpv(0.f, -1000.f), cpBodyGetPosition(entityPhysics.body));

		float velY = cpBodyGetVelocity(entityPhysics.body).y;
		cpBodySetVelocity(entityPhysics.body, cpv(velocity.x, velY));
	}
}

void PlayerInputSystem(entt::registry& registry)
{
	auto view = registry.view<PlayerControlled, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		entityInput.left = InputManager::Instance().IsActive("MoveLeft");
		entityInput.right = InputManager::Instance().IsActive("MoveRight");
		entityInput.jump = InputManager::Instance().IsActive("Jump");
	}
}

int main()
{
	SDLpp sdl;

	SDLWindow window("A4Engine", 1280, 720);
	SDLRenderer renderer(window); //, "", SDL_RENDERER_PRESENTVSYNC);

	ResourceManager resourceManager(renderer);
	InputManager inputManager;

	SDLImGui imgui(window, renderer);

	// Si on initialise ImGui dans une DLL (ce que nous faisons avec la classe SDLppImGui) et l'utilisons dans un autre ex�cutable (DLL/.exe)
	// la biblioth�que nous demande d'appeler ImGui::SetCurrentContext dans l'ex�cutable souhaitant utiliser ImGui, avec le contexte pr�c�demment r�cup�r�
	// Ceci est parce qu'ImGui utilise des variables globales en interne qui ne sont pas partag�es entre la .dll et l'ex�cutable (comme indiqu� dans sa documentation)
	ImGui::SetCurrentContext(imgui.GetContext());

	// ZQSD
	InputManager::Instance().BindKeyPressed(SDLK_a, "MoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_w, "MoveUp");
	InputManager::Instance().BindKeyPressed(SDLK_s, "MoveDown");

	// Touches directionnelles (cam�ra)
	InputManager::Instance().BindKeyPressed(SDLK_LEFT, "CameraMoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_RIGHT, "CameraMoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_UP, "CameraMoveUp");
	InputManager::Instance().BindKeyPressed(SDLK_DOWN, "CameraMoveDown");

	std::shared_ptr<Spritesheet> spriteSheet = std::make_shared<Spritesheet>();
	spriteSheet->AddAnimation("idle", 5, 0.1f, Vector2i{ 0, 0 }, Vector2i{ 32, 32 });
	spriteSheet->AddAnimation("run", 8, 0.1f, Vector2i{ 0, 32 }, Vector2i{ 32, 32 });
	spriteSheet->AddAnimation("jump", 4, 0.1f, Vector2i{ 0, 64 }, Vector2i{ 32, 32 });

	entt::registry registry;

	AnimationSystem animSystem(registry);
	RenderSystem renderSystem(renderer, registry);
	VelocitySystem velocitySystem(registry);

	entt::entity cameraEntity = CreateCamera(registry);

	entt::entity house = CreateHouse(registry);
	registry.get<Transform>(house).SetPosition({ 750.f, 275.f });
	registry.get<Transform>(house).SetScale({ 2.f, 2.f });

	entt::entity runner = CreateRunner(registry, spriteSheet);
	registry.get<Transform>(runner).SetPosition({ 300.f, 250.f });

	entt::entity box = CreateBox(registry);

	Uint64 lastUpdate = SDL_GetPerformanceCounter();

	InputManager::Instance().BindKeyPressed(SDL_KeyCode::SDLK_r, "PlayRun");

	InputManager::Instance().OnAction("PlayRun", [&](bool pressed)
		{
			if (pressed)
				registry.get<SpritesheetComponent>(runner).PlayAnimation("run");
			else
				registry.get<SpritesheetComponent>(runner).PlayAnimation("idle");
		});

	cpSpace* space = cpSpaceNew();
	cpSpaceSetGravity(space, { 0.f, 981.f });
	cpSpaceSetDamping(space, 0.5f);

	cpBody* boxBody = cpBodyNew(100.f, cpMomentForBox(100.f, 256, 256));
	cpSpaceAddBody(space, boxBody);
	cpBodySetPosition(boxBody, cpv(400.f, 400.f));
	cpBodySetAngle(boxBody, Rad2Deg(15.f));

	cpShape* boxShape = cpBoxShapeNew(boxBody, 256, 256, 0.f);
	cpShapeGetCenterOfGravity(boxShape);
	cpSpaceAddShape(space, boxShape);

	cpBody* floorBody = cpBodyNewStatic();

	cpShape* floorShape = cpSegmentShapeNew(floorBody, cpv(0.f, 720.f), cpv(10'000.f, 720.f), 0.f);
	cpSpaceAddShape(space, floorShape);

	cpBody* playerBody = cpBodyNew(80.f, std::numeric_limits<float>::infinity());
	cpShape* playerShape = cpBoxShapeNew(playerBody, 128.f, 256.f, 0.f);

	auto& playerPhysics = registry.get<PhysicsComponent>(runner);
	playerPhysics.body = playerBody;
	cpSpaceAddBody(space, playerPhysics.body);

	playerPhysics.shape = playerShape;
	cpSpaceAddShape(space, playerPhysics.shape);

	InputManager::Instance().BindKeyPressed(SDLK_SPACE, "Jump");

	// Rajoutez un InputComponent (contenant des bool�ens repr�sentant les contr�les, left/right/jump)
	// Rajoutez un VelocityComponent sur l'entit� runner
	// Rajoutez une fonction (system), qui modifie la v�locit� en fonction de l'input

	// Pas de physique pour l'instant

	float physicsTimestep = 1.f / 50.f;
	float physicsAccumulator = 0.f;


	// testing



	//Matrix3x3f( 1.f, 3.f, 3.f,
	//			1.f, 3.f, 3.f,
	//			1.f, 3.f, 3.f);

	float** m_Matrix;

	m_Matrix = new float* [3];

	for (int i = 0; i < 3; ++i)
	{
		m_Matrix[i] = new float[3];
	}


	float m[3][3] = {
		{1.f,3.f,3.f},
		{1.f,3.f,3.f},
		{1.f,3.f,3.f}
	};

	//for (int x = 0; x < 3; ++x)
	//{
	//	for (int y = 0; y < 3; ++y)
	//	{
	//		m_Matrix[x][y] = m[x][y];
	//	}
	//}

	//for (int k = 0; k < 3; ++k)
	//{
	//	for (int l = 0; l < 3; ++l)
	//	{
	//		std::cout << m_Matrix[k][l] << ",";
	//	}
	//	std::cout << std::endl;
	//}
	//Matrix3x3f(m);


	Matrix3x3f a;
	a.MatrixReplace(m);

	//(m);

	Matrix3x3f
	(
		1.f, 2.f, 3.f,
		1.f, 2.f, 3.f,
		1.f, 2.f, 3.f
	);


	bool isOpen = true;
	while (isOpen)
	{
		Uint64 now = SDL_GetPerformanceCounter();
		float deltaTime = (float)(now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;

		//fmt::print("FPS: {}\n", 1.f / deltaTime);

		SDL_Event event;
		while (SDLpp::PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isOpen = false;

			imgui.ProcessEvent(event);

			InputManager::Instance().HandleEvent(event);
		}

		imgui.NewFrame();

		renderer.SetDrawColor(127, 0, 127, 255);
		renderer.Clear();

		HandleCameraMovement(registry, cameraEntity, deltaTime);
		//HandleRunnerMovement(registry, runner, deltaTime);

		// Objectif : faire en sorte que la physique tourne � pas fixe (fixed delta time)

		physicsAccumulator += deltaTime;
		while (physicsAccumulator >= physicsTimestep)
		{
			cpSpaceStep(space, physicsTimestep);
			physicsAccumulator -= physicsTimestep;
		}

		// Box
		cpVect position = cpBodyGetPosition(boxBody);
		float rotation = Rad2Deg(cpBodyGetAngle(boxBody));

		registry.get<Transform>(box).SetPosition(Vector2f(position.x, position.y));
		registry.get<Transform>(box).SetRotation(rotation);

		// Player
		cpVect playerPos = cpBodyGetPosition(playerBody);
		float playerRot = Rad2Deg(cpBodyGetAngle(playerBody));

		registry.get<Transform>(runner).SetPosition(Vector2f(playerPos.x, playerPos.y));
		registry.get<Transform>(box).SetRotation(playerRot);

		animSystem.Update(deltaTime);
		velocitySystem.Update(deltaTime);
		renderSystem.Update(deltaTime);
		PlayerInputSystem(registry);
		PlayerControllerSystem(registry);

		EntityInspector("Box", registry, box);
		EntityInspector("Camera", registry, cameraEntity);
		EntityInspector("Runner", registry, runner);

		imgui.Render();

		renderer.Present();
	}

	cpSpaceRemoveShape(space, boxShape);
	cpShapeFree(boxShape);

	cpSpaceRemoveBody(space, boxBody);
	cpBodyFree(boxBody);

	cpSpaceFree(space);

	return 0;
}

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity)
{
	Transform& transform = registry.get<Transform>(entity);

	float rotation = transform.GetRotation();
	Vector2f pos = transform.GetPosition();
	Vector2f scale = transform.GetScale();

	ImGui::Begin(windowName);

	ImGui::LabelText("Position", "X: %f\nY: %f", pos.x, pos.y);

	if (ImGui::SliderFloat("Rotation", &rotation, -180.f, 180.f))
		transform.SetRotation(rotation);

	float scaleVal[2] = { scale.x, scale.y };
	if (ImGui::SliderFloat2("Scale", scaleVal, -5.f, 5.f))
		transform.SetScale({ scaleVal[0], scaleVal[1] });

	if (ImGui::Button("Reset"))
	{
		transform.SetScale({ 1.f, 1.f });
		transform.SetRotation(0.f);
		transform.SetPosition(Vector2f(0.f, 0.f));
	}

	ImGui::End();
}

entt::entity CreateBox(entt::registry& registry)
{
	std::shared_ptr<Sprite> box = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/kirby.png"));
	box->SetOrigin({ 0.5f, 0.5f });

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(box));
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity CreateCamera(entt::registry& registry)
{
	entt::entity entity = registry.create();
	registry.emplace<CameraComponent>(entity);
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity CreateHouse(entt::registry& registry)
{
	std::shared_ptr<Model> house = ResourceManager::Instance().GetModel("assets/house.model");

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(house));
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity CreateRunner(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/runner.png"));
	sprite->SetOrigin({ 0.5f, 0.5f });
	sprite->Resize(256, 256);
	sprite->SetRect(SDL_Rect{ 0, 0, 32, 32 });

	entt::entity entity = registry.create();
	registry.emplace<SpritesheetComponent>(entity, spritesheet, sprite);
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<PhysicsComponent>(entity);
	registry.emplace<PlayerControlled>(entity);

	return entity;
}

void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime)
{
	Transform& cameraTransform = registry.get<Transform>(camera);

	if (InputManager::Instance().IsActive("CameraMoveDown"))
		cameraTransform.Translate(Vector2f(0.f, 500.f * deltaTime));

	if (InputManager::Instance().IsActive("CameraMoveLeft"))
		cameraTransform.Translate(Vector2f(-500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("CameraMoveRight"))
		cameraTransform.Translate(Vector2f(500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("CameraMoveUp"))
		cameraTransform.Translate(Vector2f(0.f, -500.f * deltaTime));
}

void HandleRunnerMovement(entt::registry& registry, entt::entity runner, float deltaTime)
{
	Transform& transform = registry.get<Transform>(runner);

	if (InputManager::Instance().IsActive("MoveDown"))
		transform.Translate(Vector2f(0.f, 500.f * deltaTime));

	if (InputManager::Instance().IsActive("MoveLeft"))
		transform.Translate(Vector2f(-500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("MoveRight"))
		transform.Translate(Vector2f(500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("MoveUp"))
		transform.Translate(Vector2f(0.f, -500.f * deltaTime));
}