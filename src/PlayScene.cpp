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
		//GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	

	CollisionManager::circleAABBCheck(m_pSpaceShip, m_pObstacle);
	CollisionManager::squaredRadiusCheck(m_pSpaceShip, m_pTarget);
}

void PlayScene::clean()
{
	removeAllChildren();
	SoundManager::Instance().unload("PlaySong", SOUND_MUSIC);
}

void PlayScene::handleEvents()
{
	/*bool press = false;*/
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		if (m_pressed == false)
		{
			SoundManager::Instance().playSound("click", 0, -1);
			m_pSpaceShip->getTransform()->position = glm::vec2(rand() % 700 + 50, rand() % 600);
			m_pTarget->getTransform()->position = glm::vec2(rand() % 700 + 50, rand() % 600);
			m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
			m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pSpaceShip->setRotation(0.0f);
			m_pSpaceShip->setBehaviour(SEEKING);
			m_pSpaceShip->setEnabled(true);
			m_pTarget->setEnabled(true);
			m_pObstacle->setEnabled(false);
			m_pressed = true;
		}
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		if (m_pressed == false)
		{
			SoundManager::Instance().playSound("click", 0, -1);
			m_pTarget->getTransform()->position = glm::vec2(rand() % 200 + 300, rand() % 200 + 200);
			m_pSpaceShip->getTransform()->position = glm::vec2(rand() % 200 + 300, rand() % 200 + 200);
			m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
			m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pSpaceShip->setRotation(0.0f);
			m_pSpaceShip->setBehaviour(FLEEING);
			m_pSpaceShip->setEnabled(true);
			m_pTarget->setEnabled(true);
			m_pObstacle->setEnabled(false);
			m_pressed = true;
		}
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		if (m_pressed == false)
		{
			SoundManager::Instance().playSound("click", 0, -1);
			m_pSpaceShip->getTransform()->position = glm::vec2(rand() % 700 + 50, 50);
			m_pTarget->getTransform()->position = glm::vec2(rand() % 700 + 50, 500);
			m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
			m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pSpaceShip->setRotation(0.0f);
			m_pSpaceShip->setBehaviour(ARRIVAL);
			m_pSpaceShip->setEnabled(true);
			m_pTarget->setEnabled(true);
			m_pObstacle->setEnabled(false);
			m_pressed = true;
		}
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		if (m_pressed == false)
		{
			SoundManager::Instance().playSound("click", 0, -1);
			m_pSpaceShip->getTransform()->position = glm::vec2(rand() % 700 + 50, 50.0f);
			m_pTarget->getTransform()->position = glm::vec2(400.0f, 500.0f);
			m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
			m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pSpaceShip->setRotation(0.0f);
			m_pSpaceShip->setBehaviour(OBSTACLE_AVOIDANCE);
			m_pSpaceShip->setEnabled(true);
			m_pTarget->setEnabled(true);
			m_pObstacle->setEnabled(true);
			
			m_pressed = true;
		}
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		SoundManager::Instance().playSound("click", 0, -1);
		if (m_pressed == false)
		{
			if (m_pSpaceShip->getDisplayLines())
			{
				m_pSpaceShip->setDisplayLines(false);
			}
			else
			{
				m_pSpaceShip->setDisplayLines(true);
			}
			m_pressed = true;
		}
	}
	else
	{
		m_pressed = false;
	}
}

void PlayScene::start()
{
	
	const SDL_Color pink = { 255, 100, 150, 255 };

	// Set GUI Title
	m_guiTitle = "Play Scene";

	SoundManager::Instance().load("../Assets/audio/Menu.mp3", "PlaySong", SOUND_MUSIC);
	SoundManager::Instance().playMusic("PlaySong", -1, 0);
	
	m_pInstructionLabel1 = new Label("Press 1 for Seeking", "Pixel", 15, pink, glm::vec2(400.0f, 20.0f));
	m_pInstructionLabel1->setParent(this);
	addChild(m_pInstructionLabel1);

	m_pInstructionLabel2 = new Label("Press 2 for Fleeing", "Pixel", 15, pink, glm::vec2(400.0f, 40.0f));
	m_pInstructionLabel2->setParent(this);
	addChild(m_pInstructionLabel2);
	
	m_pInstructionLabel3 = new Label("Press 3 for Arrival", "Pixel", 15, pink, glm::vec2(400.0f, 60.0f));
	m_pInstructionLabel3->setParent(this);
	addChild(m_pInstructionLabel3);
	
	m_pInstructionLabel4 = new Label("Press 4 for Obstacle Avoidance", "Pixel", 15, pink, glm::vec2(400.0f, 80.0f));
	m_pInstructionLabel4->setParent(this);
	addChild(m_pInstructionLabel4);

	m_pInstructionLabel0 = new Label("Press 0 to toggle lines", "Pixel", 15, pink, glm::vec2(400.0f, 100.0f));
	m_pInstructionLabel0->setParent(this);
	addChild(m_pInstructionLabel0);
	
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 500.0f);
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);

	m_pObstacle = new Obstacle();
	m_pObstacle->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pObstacle->setEnabled(false);
	addChild(m_pObstacle);

	// instantiating spaceship
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(400.0f, 100.0f);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	m_pSpaceShip->setObstacle(m_pObstacle);
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
