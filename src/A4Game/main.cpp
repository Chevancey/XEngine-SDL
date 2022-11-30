#include <iostream>
#include <SDL.h>
#include <A4Engine/AnimationSystem.hpp>
#include <A4Engine/CameraComponent.hpp>
#include <A4Engine/ChipmunkBody.hpp>
#include <A4Engine/ChipmunkShape.hpp>
#include <A4Engine/ChipmunkSpace.hpp>
#include <A4Engine/CollisionShape.hpp>
#include <A4Engine/GraphicsComponent.hpp>
#include <A4Engine/InputManager.hpp>
#include <A4Engine/Model.hpp>
#include <A4Engine/PhysicsSystem.hpp>
#include <A4Engine/RenderSystem.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppImGui.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/SpritesheetComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <A4Engine/VelocityComponent.hpp>
#include <A4Engine/VelocitySystem.hpp>

#include <A4Engine/SoundDevice.hpp>
#include <A4Engine/SoundSource.hpp>
#include <A4Engine/SoundEffect.hpp>
#include <A4Engine/SoundTrack.hpp>

#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include <AL/al.h>
#include <AL/alc.h>

entt::entity CreateBall(entt::registry& registry, std::shared_ptr<CollisionShape> shape);
entt::entity CreateCamera(entt::registry& registry);
entt::entity CreatePitch(entt::registry& registry);

entt::entity CreatePlayer1(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet);
entt::entity CreatePlayer2(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet);

entt::entity CreateLeftGoal(entt::registry& registry);
entt::entity CreateRightGoal(entt::registry& registry);
entt::entity CreateScoreSound(entt::registry& registry);

entt::entity CreateGoalText(entt::registry& registry);
entt::entity Wall(entt::registry& registry, float sizeX, float sizeY);

void CreatePlane(entt::registry& registry, Vector2f pointA, Vector2f pointB);

bool Timer(float deltaTime, float& timer, float amountOfTime, bool &boolValue);

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity);
void ScoreUI(int blueScore, int redScore, ImFont* font);
void BlueWins(ImFont* font);
void RedWins(ImFont* font);
void Paused(ImFont* font);
void PauseMenu(ImFont* font, bool& pause, bool& restart, float& time, int& b, int& r);


void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime);
void HandleRunnerMovement(entt::registry& registry, entt::entity runner, float deltaTime);

struct InputComponent
{
	bool left = false;
	bool right = false;
	bool jump = false;
};

struct RunOnce {
	template <typename T>
	RunOnce(T&& f) { f(); }
};

struct Player1Controlled {};
struct Player2Controlled {};

void Player1ControllerSystem(entt::registry& registry)
{
	auto view = registry.view<RigidBodyComponent, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		auto& entityPhysics = view.get<RigidBodyComponent>(entity);

		Vector2f velocity = Vector2f(0.f, 0.f);
		velocity.y = entityPhysics.GetLinearVelocity().y;

		if (entityInput.left)
			velocity.x -= 500.f;

		if (entityInput.right)
			velocity.x += 500.f;

		if (entityInput.jump && velocity.y < 1.f)
			velocity.y = -500.f;

		entityPhysics.SetLinearVelocity(velocity);
	}
}

void Player1InputSystem(entt::registry& registry)
{
	auto view = registry.view<Player1Controlled, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		entityInput.left = InputManager::Instance().IsActive("P1MoveLeft");
		entityInput.right = InputManager::Instance().IsActive("P1MoveRight");
		entityInput.jump = InputManager::Instance().IsActive("P1Jump");
	}
}

void Player2ControllerSystem(entt::registry& registry)
{
	auto view = registry.view<RigidBodyComponent, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		auto& entityPhysics = view.get<RigidBodyComponent>(entity);

		Vector2f velocity = Vector2f(0.f, 0.f);
		velocity.y = entityPhysics.GetLinearVelocity().y;

		if (entityInput.left)
			velocity.x -= 500.f;

		if (entityInput.right)
			velocity.x += 500.f;

		if (entityInput.jump && velocity.y < 1.f)
			velocity.y = -500.f;

		entityPhysics.SetLinearVelocity(velocity);
	}
}

void Player2InputSystem(entt::registry& registry)
{
	auto view = registry.view<Player2Controlled, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		entityInput.left = InputManager::Instance().IsActive("P2MoveLeft");
		entityInput.right = InputManager::Instance().IsActive("P2MoveRight");
		entityInput.jump = InputManager::Instance().IsActive("P2Jump");
	}
}

int main()
{
	SDLpp sdl;

	SDLppWindow window("A4Engine", 1280, 720);
	SDLppRenderer renderer(window, "direct3d11", SDL_RENDERER_PRESENTVSYNC);

	ResourceManager resourceManager(renderer);
	InputManager inputManager;

	SDLppImGui imgui(window, renderer);

	// Si on initialise ImGui dans une DLL (ce que nous faisons avec la classe SDLppImGui) et l'utilisons dans un autre exécutable (DLL/.exe)
	// la bibliothèque nous demande d'appeler ImGui::SetCurrentContext dans l'exécutable souhaitant utiliser ImGui, avec le contexte précédemment récupéré
	// Ceci est parce qu'ImGui utilise des variables globales en interne qui ne sont pas partagées entre la .dll et l'exécutable (comme indiqué dans sa documentation)
	ImGui::SetCurrentContext(imgui.GetContext());

	// WASD
	InputManager::Instance().BindKeyPressed(SDLK_a, "P1MoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_d, "P1MoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_w, "P1MoveUp");
	InputManager::Instance().BindKeyPressed(SDLK_s, "P1MoveDown");
	InputManager::Instance().BindKeyPressed(SDLK_SPACE, "P1Jump");

	// UP-LEFT-DOWN-RIGHT
	InputManager::Instance().BindKeyPressed(SDLK_LEFT,  "P2MoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_RIGHT, "P2MoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_UP,	"P2MoveUp");
	InputManager::Instance().BindKeyPressed(SDLK_DOWN,  "P2MoveDown");
	InputManager::Instance().BindKeyPressed(SDLK_RCTRL, "P2Jump");

	std::shared_ptr<Spritesheet> spriteSheetPlayer1 = std::make_shared<Spritesheet>();
	spriteSheetPlayer1->AddAnimation("idle", 1, 0.1f, Vector2i{ 0, 0 },  Vector2i{ 64, 64 });
	spriteSheetPlayer1->AddAnimation("jump", 3, 0.1f, Vector2i{ 0, 64 }, Vector2i{ 64, 64 });

	std::shared_ptr<Spritesheet> spriteSheetPlayer2 = std::make_shared<Spritesheet>();
	spriteSheetPlayer2->AddAnimation("idle", 1, 0.1f, Vector2i{ 0, 0 }, Vector2i{ 64, 64 });
	spriteSheetPlayer2->AddAnimation("jump", 3, 0.1f, Vector2i{ 0, 64 }, Vector2i{ 64, 64 });

	entt::registry registry;

	AnimationSystem animSystem(registry);
	RenderSystem renderSystem(renderer, registry);
	VelocitySystem velocitySystem(registry);
	PhysicsSystem physicsSystem(registry);
	physicsSystem.SetGravity({ 0.f, 981.f });
	physicsSystem.SetDamping(0.9f);

	// ALL SOUNDS
	SoundDevice::Init;
	SoundDevice::get()->SetAttunation(AL_EXPONENT_DISTANCE_CLAMPED);
	SoundDevice::get()->SetGain(0.2f);

	SoundTrack mySoundTrack("assets/stadium.wav");
	mySoundTrack.Play();

	uint32_t netSound = SoundEffect::get()->addSoundEffect("assets/net.wav");
	uint32_t scoreSound = SoundEffect::get()->addSoundEffect("assets/score.wav");

	//ALL ENTT
	//Camera
	entt::entity cameraEntity = CreateCamera(registry);

	// Front Environment and Static Objects

	entt::entity goalText = CreateGoalText(registry);
	registry.get<Transform>(goalText).SetPosition({ 640.f, 400.f });

	entt::entity leftGoal = CreateLeftGoal(registry);
	registry.get<RigidBodyComponent>(leftGoal).TeleportTo({ 0.f, 245.f });
	registry.get<SoundSource>(leftGoal).SetLooping(false);
	registry.get<SoundSource>(leftGoal).SetPosition(registry.get<RigidBodyComponent>(leftGoal).GetPosition());


	entt::entity rightGoal = CreateRightGoal(registry);
	registry.get<RigidBodyComponent>(rightGoal).TeleportTo({ 1080.f, 245.f });
	registry.get<SoundSource>(rightGoal).SetLooping(false);
	registry.get<SoundSource>(rightGoal).SetPosition(registry.get<RigidBodyComponent>(rightGoal).GetPosition());

	entt::entity goalSound = CreateScoreSound(registry);
	registry.get<SoundSource>(goalSound).SetLooping(false);

	//Player 1
	entt::entity player1 = CreatePlayer1(registry, spriteSheetPlayer1);
	registry.get<RigidBodyComponent>(player1).TeleportTo({ 200.f, 400.f });

	//Player 2
	entt::entity player2 = CreatePlayer2(registry, spriteSheetPlayer2);
	registry.get<RigidBodyComponent>(player2).TeleportTo({ 1080.f, 400.f });

	//Ball
	std::shared_ptr<CollisionShape> ballShape = std::make_shared<CircleShape>(40.f);
	entt::entity ball = CreateBall(registry, ballShape);
	registry.get<RigidBodyComponent>(ball).TeleportTo({ 1280/2, 100 }, 15.f);

	//Back Environment and Static objects
	entt::entity wallEnityLeft = Wall(registry, 160.f, 720.f);
	registry.get<RigidBodyComponent>(wallEnityLeft).TeleportTo({ -80.f, 360.f });

	entt::entity wallEnityRight = Wall(registry, 160.f, 720.f);
	registry.get<RigidBodyComponent>(wallEnityRight).TeleportTo({ 1360.f, 360.f });

	entt::entity wallEnityTop = Wall(registry, 1280.f, 160.f);
	registry.get<RigidBodyComponent>(wallEnityTop).TeleportTo({ 640.f, -160.f });

	entt::entity wallEnityBottom = Wall(registry, 1280.f, 160.f);
	registry.get<RigidBodyComponent>(wallEnityBottom).TeleportTo({ 640.f, 720.f });

	//Pitch is Always Last
	entt::entity pitch = CreatePitch(registry);




	//mySoundTrack.SetLooping(true);

	// ALL INPUTS
	InputManager::Instance().BindKeyPressed(SDL_KeyCode::SDLK_r, "PlayRun");

	InputManager::Instance().OnAction("P1Jump", [&](bool pressed)
		{
			if (pressed)
			{
				registry.get<SpritesheetComponent>(player1).PlayAnimation("jump");
			}
			else
				registry.get<SpritesheetComponent>(player1).PlayAnimation("idle");
		});

	InputManager::Instance().OnAction("P2Jump", [&](bool pressed)
		{
			if (pressed)
			{
				registry.get<SpritesheetComponent>(player2).PlayAnimation("jump");

			}
			else
				registry.get<SpritesheetComponent>(player2).PlayAnimation("idle");
				
		});

	InputManager::Instance().OnAction("PlayRun", [&](bool pressed)
		{
			if (pressed)
			{
				entt::entity ball2 = CreateBall(registry, ballShape);
				registry.get<RigidBodyComponent>(ball2).TeleportTo({ 400.f, 400.f }, 15.f);
			}
		});

	Uint64 lastUpdate = SDL_GetPerformanceCounter();

	// Variables
	int blueScore = 0;
	int redScore = 0;
	bool addScore = true;
	bool gameLoopRestart = false;
	bool isOpen = true;
	float sequencetimer = 0.f;
	bool isPause = false;
	
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("assets/segoe.ttf", 32);

	if (font1)
	{
		std::cout << "Hello" << std::endl;
	}

	while (isOpen)
	{
		Uint64 now = SDL_GetPerformanceCounter();
		Uint64 nowPause = SDL_GetPerformanceCounter();
		float deltaTime = (float)(now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;

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

		if (!isPause)
		{
			animSystem.Update(deltaTime);
			velocitySystem.Update(deltaTime);
			physicsSystem.Update(deltaTime);
			mySoundTrack.UpdateBufferStream();
		}
		else 
		{ Paused(font1); }
		renderSystem.Update(deltaTime);

		Player1InputSystem(registry);
		Player1ControllerSystem(registry);
		
		if (!gameLoopRestart)
		{
			if (registry.get<Transform>(ball).GetPosition().x < 200
				&& registry.get<Transform>(ball).GetPosition().x > 0
				&& registry.get<Transform>(ball).GetPosition().y > 250
				&& registry.get<Transform>(ball).GetPosition().y < 720)
			{

				if (addScore)
				{
					redScore += 1;
					std::cout << "BELGIQUE:" << redScore << std::endl;
					addScore = false;
					gameLoopRestart = true;
					registry.get<SoundSource>(leftGoal).Play(netSound);
					registry.get<SoundSource>(goalSound).SetPosition(registry.get<RigidBodyComponent>(leftGoal).GetPosition());
					registry.get<SoundSource>(goalSound).Play(scoreSound);
				}

				registry.get<GraphicsComponent>(goalText).renderable->Hide(false);
			}
			else if (registry.get<Transform>(ball).GetPosition().x > 1080
				&& registry.get<Transform>(ball).GetPosition().x < 1280
				&& registry.get<Transform>(ball).GetPosition().y > 250
				&& registry.get<Transform>(ball).GetPosition().y < 720)
			{

				if (addScore)
				{
					blueScore += 1;
					std::cout << "FRANCE:" << blueScore << std::endl;
					addScore = false;
					gameLoopRestart = true;
					registry.get<SoundSource>(rightGoal).Play(netSound);
					registry.get<SoundSource>(goalSound).SetPosition(registry.get<RigidBodyComponent>(rightGoal).GetPosition());
					registry.get<SoundSource>(goalSound).Play(scoreSound);
				}

				registry.get<GraphicsComponent>(goalText).renderable->Hide(false);
			}
			else
			{
				registry.get<Transform>(cameraEntity).SetPosition({ 0,  0 });
				registry.get<GraphicsComponent>(goalText).renderable->Hide(true);
				addScore = true;
			}
		}

		if (gameLoopRestart)
		{
			registry.get<Transform>(cameraEntity).SetPosition(
				{ registry.get<Transform>(ball).GetPosition().x - 1280 / 2,
				registry.get<Transform>(ball).GetPosition().y - 720 / 2 }
			);

			registry.get<Transform>(goalText).SetPosition(
				{ registry.get<Transform>(cameraEntity).GetPosition().x + 640.f,
				registry.get<Transform>(cameraEntity).GetPosition().y + 250.f }
			);

			if (blueScore >= 5)
			{
				BlueWins(font1);
			}
			else if (redScore >= 5)
			{
				RedWins(font1);
			}

			if (Timer(deltaTime, sequencetimer, 3.f, gameLoopRestart))
			{
				if (blueScore >= 5)
				{
					blueScore = 0;
					redScore = 0;
				}
				else if (redScore >= 5)
				{
					blueScore = 0;
					redScore = 0;
				}

				registry.get<RigidBodyComponent>(ball).TeleportTo({ 640.f, 200.f });
				registry.get<RigidBodyComponent>(ball).SetLinearVelocity({ 0.f,0.f });

				registry.get<RigidBodyComponent>(player1).TeleportTo({ 200.f, 400.f });
				registry.get<RigidBodyComponent>(player2).TeleportTo({ 1080.f, 400.f });

				sequencetimer = 0.f;
				gameLoopRestart = false;

			}
		}

		Player2InputSystem(registry);
		Player2ControllerSystem(registry);

		ScoreUI(blueScore, redScore, font1);
		PauseMenu(font1, isPause, gameLoopRestart, sequencetimer, blueScore, redScore);

		//physicsSystem.DebugDraw(renderer, registry.get<Transform>(cameraEntity).GetTransformMatrix().Inverse());
		
		imgui.Render();
		
		renderer.Present();
	}

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

void ScoreUI(int blueScore, int redScore, ImFont* font)
{
	ImGui::Begin("SCORE", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 250, 255));
	ImGui::LabelText("", "FRANCE: %i", blueScore);
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
	ImGui::LabelText("", "BELGIQUE: %i", redScore);
	ImGui::PopStyleColor();
	
	ImGui::End();
}

void BlueWins(ImFont* font)
{
	ImGui::Begin("", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 250, 255));
	ImGui::Text("FRANCE WINS");
	ImGui::PopStyleColor();

	ImGui::End();
}

void RedWins(ImFont* font)
{
	ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
	ImGui::Text("BELGIQUE WINS");
	ImGui::PopStyleColor();

	ImGui::End();
}


void PauseMenu(ImFont* font, bool& pause, bool& restart, float& time, int& b, int &r)
{
	ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));

	if (ImGui::Button("Pause"))
	{
		pause = !pause;
	}

	if (ImGui::Button("Restart"))
	{
		restart = !restart;
		time = 3.f;
		b = 0;
		r = 0;
	}
	
	ImGui::PopStyleColor();

	ImGui::End();
}


void Paused(ImFont* font)
{

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
	ImGui::Begin("Paused", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);// | ImGuiWindowFlags_NoMove);
	//ImGui::Text();
	ImGui::PopStyleColor();

	ImGui::End();
}

entt::entity CreateBall(entt::registry& registry, std::shared_ptr<CollisionShape> shape) 
{
	std::shared_ptr<Sprite> ball = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/Ball.png"));
	ball->SetOrigin({ 0.5f, 0.5f });
	ball->Resize(100,100);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(ball));
	registry.emplace<Transform>(entity);

	auto& entityPhysics = registry.emplace<RigidBodyComponent>(entity, 0.1f);
	entityPhysics.AddShape(std::move(shape));

	return entity;
}

entt::entity CreateCamera(entt::registry& registry)
{
	entt::entity entity = registry.create();
	registry.emplace<CameraComponent>(entity);
	registry.emplace<Transform>(entity);

	return entity;
}

bool Timer(float deltaTime, float &timer, float amountOfTime, bool &boolValue)
{
	if (timer >= amountOfTime)
	{
		std::cout << "Restart" << std::endl;
		boolValue = false;
		return true;
	}
	else
	{
		timer += deltaTime;
		std::cout << timer << std::endl;
		boolValue = true;
		return false;
	}
}

void CreatePlane(entt::registry& registry, Vector2f pointA, Vector2f pointB)
{
	std::shared_ptr<CollisionShape> groundShape = std::make_shared<SegmentShape>(pointA, pointB);
	
	entt::entity groundEntity = registry.create();
	
	auto& groundPhysics = registry.emplace<RigidBodyComponent>(groundEntity, RigidBodyComponent::Static{});
	groundPhysics.AddShape(groundShape);
}

entt::entity CreateGoalText(entt::registry& registry)
{
	std::shared_ptr<Sprite> pitch = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/GoalText.png"));
	pitch->SetOrigin({ .5f, .5f });
	pitch->Resize(1280/4, 720/4);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(pitch));
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity CreatePitch(entt::registry& registry)
{
	std::shared_ptr<Sprite> pitch = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/Pitch.png"));
	pitch->SetOrigin({ .333f, .333f });
	pitch->Resize(1280*3, 720*3);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(pitch));
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity Wall(entt::registry& registry, float sizeX, float sizeY)
{
	std::shared_ptr<CollisionShape> collider = std::make_shared<BoxShape>(sizeX, sizeY);

	entt::entity entity = registry.create();
	registry.emplace<Transform>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Static{});
	entityBody.AddShape(collider, Vector2f(0.f, 0.f), false);

	return entity;
}

entt::entity CreateScoreSound(entt::registry& registry)
{
	entt::entity entity = registry.create();
	registry.emplace<Transform>(entity);
	registry.emplace<SoundSource>(entity);

	return entity;
}


entt::entity CreateLeftGoal(entt::registry& registry)
{


	std::shared_ptr<Sprite> leftGoal = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/LeftGoal.png"));
	leftGoal->SetOrigin({ .0f, .0f });
	leftGoal->Resize(400, 400);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(leftGoal));
	registry.emplace<Transform>(entity);
	registry.emplace<SoundSource>(entity);

	std::shared_ptr<CollisionShape> leftGoalCollider = std::make_shared<SegmentShape>(Vector2{ 0.f, 0.f }, Vector2{ 200.f, 0.f });

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Static{});
	entityBody.AddShape(leftGoalCollider, Vector2f(0.f, 0.f), false);

	return entity;
}

entt::entity CreateRightGoal(entt::registry& registry)
{
	std::shared_ptr<Sprite> rightGoal = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/RightGoal.png"));
	rightGoal->SetOrigin({ 0.5f, .0f });
	rightGoal->Resize(400, 400);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(rightGoal));
	registry.emplace<Transform>(entity);
	registry.emplace<SoundSource>(entity);

	std::shared_ptr<CollisionShape> rightGoalCollider = std::make_shared<SegmentShape>(Vector2{ 0.f, 0.f }, Vector2{ 200.f, 0.f });

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Static{});
	entityBody.AddShape(rightGoalCollider, Vector2f(0.f, 0.f), false);

	return entity;
}

entt::entity CreatePlayer1(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/Player1.png"));
	sprite->SetOrigin({ .5f, .5f });
	sprite->Resize(256, 256);
	sprite->SetRect(SDL_Rect{ 0, 0, 64, 64 });

	std::shared_ptr<CollisionShape> collider = std::make_shared<BoxShape>(80.f, 245.f);
	std::shared_ptr<CollisionShape> footCollider = std::make_shared<SegmentShape>(Vector2{ 80.f, 60.f }, Vector2{ 40.f, 30.f });

	

	entt::entity entity = registry.create();
	registry.emplace<SpritesheetComponent>(entity, spritesheet, sprite);
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<Player1Controlled>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, 80.f, std::numeric_limits<float>::infinity());

	entityBody.AddShape(collider, Vector2f(0.f, 0.f), false);
	entityBody.AddShape(footCollider, Vector2f(0.f, 60.f), false);

	return entity;
}

entt::entity CreatePlayer2(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/Player2.png"));
	sprite->SetOrigin({ .5f, .5f });
	sprite->Resize(256, 256);
	sprite->SetRect(SDL_Rect{ 0, 0, 64, 64 });

	std::shared_ptr<CollisionShape> collider = std::make_shared<BoxShape>(80.f, 245.f);
	std::shared_ptr<CollisionShape> footCollider = std::make_shared<SegmentShape>(Vector2{ -80.f, 60.f }, Vector2{ -40.f, 30.f });

	entt::entity entity = registry.create();
	registry.emplace<SpritesheetComponent>(entity, spritesheet, sprite);
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<Player2Controlled>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, 80.f, std::numeric_limits<float>::infinity());

	entityBody.AddShape(collider, Vector2f(0.f, 0.f), false);
	entityBody.AddShape(footCollider, Vector2f(0.f, 60.f), false);

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