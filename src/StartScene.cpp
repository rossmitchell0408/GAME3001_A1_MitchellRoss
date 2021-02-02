#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color pink = { 255, 100, 150, 255 };
	m_pStartLabel = new Label("Start Scene", "Pixel", 40, pink, glm::vec2(400.0f, 60.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pNameLabel = new Label("Ross Mitchell 100967443", "Pixel", 20, pink, glm::vec2(400.0f, 120.0f));
	m_pNameLabel->setParent(this);
	addChild(m_pNameLabel);

	/*m_pInstructionLabel = new Label("Click to start", "Pixel", 30, pink, glm::vec2(400.0f, 350.0f));
	m_pInstructionLabel->setParent(this);
	addChild(m_pInstructionLabel);*/

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 300.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

