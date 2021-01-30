#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"
#include "Behaviour.h"
#include "CollisionManager.h"

class SpaceShip final : public DisplayObject
{
public:
	// constructor(s)
	SpaceShip();

	// destructor
	~SpaceShip();
	
	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	glm::vec2 getOrientationMinus() const;
	void setOrientationMinus(glm::vec2 orientation);
	glm::vec2 getOrientationPlus() const;
	void setOrientationPlus(glm::vec2 orientation);
	glm::vec2 getOrientationSideLeft() const;
	void setOrientationSideLeft(glm::vec2 orientation);
	glm::vec2 getOrientationSideRight() const;
	void setOrientationSideRight(glm::vec2 orientation);
	float getRotation() const;
	void setRotation(float angle);
	float getTurnRate() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);
	Behaviour getBehaviour();
	void setBehaviour(Behaviour behave);
	float getSlowRadius();
	void setSlowRadius(float radius);
	GameObject* getObstacle();
	void setObstacle(GameObject* obstacle);
	
private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	glm::vec2 m_orientationMinus;
	glm::vec2 m_orientationPlus;
	glm::vec2 m_orientationSideLeft;
	glm::vec2 m_orientationSideRight;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	
	Behaviour m_behaviour;
	float m_targetRadius;
	float m_slowRadius;
	float m_timeToTarget = 0.1f;
	float m_maxAcceleration = 10.0f;
	float m_stopRadius = 0.0f;
	GameObject* m_pObstacle;
	float m_targetRotation = 0.0f;
	
	// private function
	void m_Move();
	void m_seeking();
	void m_fleeing();
	void m_arrival();
	void m_obstacleAvoidance();
};

#endif /* defined (__SPACE_SHIP__) */