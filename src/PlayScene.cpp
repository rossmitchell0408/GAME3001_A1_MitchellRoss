#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	
	PlayScene::start();
	
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::AABBCheck(m_pSpaceShip, m_pObstacle);
}

void PlayScene::clean()
{
	removeAllChildren();
	SoundManager::Instance().unload("PlaySong", SOUND_MUSIC);
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		//TheGame::Instance()->changeSceneState(START_SCENE);
		m_pSpaceShip->setBehaviour(SEEKING);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		//TheGame::Instance()->changeSceneState(END_SCENE);
		m_pSpaceShip->setBehaviour(FLEEING);
		//m_pSpaceShip->setDestination({100.0f, 100.0f});
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		//TheGame::Instance()->changeSceneState(END_SCENE);
		m_pSpaceShip->setBehaviour(ARRIVAL);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		//TheGame::Instance()->changeSceneState(END_SCENE);
		m_pSpaceShip->setBehaviour(OBSTACLE_AVOIDANCE);
	}
}

void PlayScene::start()
{
	const SDL_Color pink = { 255, 100, 150, 255 };

	// Set GUI Title
	m_guiTitle = "Play Scene";

	SoundManager::Instance().load("../Assets/audio/Menu.mp3", "PlaySong", SOUND_MUSIC);
	SoundManager::Instance().playMusic("PlaySong", -1, 0);
	
	m_pInstructionLabel1 = new Label("Press 1 for Seeking", "Dock51", 20, pink, glm::vec2(400.0f, 20.0f));
	m_pInstructionLabel1->setParent(this);
	addChild(m_pInstructionLabel1);

	m_pInstructionLabel2 = new Label("Press 2 for Fleeing", "Dock51", 20, pink, glm::vec2(400.0f, 40.0f));
	m_pInstructionLabel2->setParent(this);
	addChild(m_pInstructionLabel2);
	
	m_pInstructionLabel3 = new Label("Press 3 for Arrival", "Dock51", 20, pink, glm::vec2(400.0f, 60.0f));
	m_pInstructionLabel3->setParent(this);
	addChild(m_pInstructionLabel3);
	
	m_pInstructionLabel4 = new Label("Press 4 for Obstacle Avoidance", "Dock51", 20, pink, glm::vec2(400.0f, 80.0f));
	m_pInstructionLabel4->setParent(this);
	addChild(m_pInstructionLabel4);
	
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(700.0f, 300.0f);
	addChild(m_pTarget);

	m_pObstacle = new Obstacle();
	m_pObstacle->getTransform()->position = glm::vec2(550.0f, 300.0f);
	addChild(m_pObstacle);

	// instantiating spaceship
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 300.0f);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - Lab 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float speed = 10.0f;
	if(ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 100.0f))
	{
		m_pSpaceShip->setMaxSpeed(speed);
	}

	static float acceleration_rate = 2.0f;
	if(ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pSpaceShip->setAccelerationRate(acceleration_rate);
	}

	static float turn_rate = 5.0f;
	if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pSpaceShip->setTurnRate(turn_rate);
	}

	static float angleInRadians = m_pSpaceShip->getRotation();
	if(ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pSpaceShip->setRotation(angleInRadians * Util::Rad2Deg);
	}
	
	if(ImGui::Button("Start"))
	{
		m_pSpaceShip->setEnabled(true);
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setRotation(0.0f);
		acceleration_rate = 2.0f;
		turn_rate = 5.0f;
		speed = 10.0f;
		angleInRadians = m_pSpaceShip->getRotation();
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
