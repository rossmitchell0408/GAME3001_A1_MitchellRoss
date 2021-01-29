#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Obstacle.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	SpaceShip* m_pSpaceShip;
	Target* m_pTarget;
	Obstacle* m_pObstacle;
	
	// UI Items
	Label* m_pInstructionLabel1;
	Label* m_pInstructionLabel2;
	Label* m_pInstructionLabel3;
	Label* m_pInstructionLabel4;
	
	
};

#endif /* defined (__PLAY_SCENE__) */