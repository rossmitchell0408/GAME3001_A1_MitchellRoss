#include "SpaceShip.h"


#include "Game.h"
#include "Util.h"

SpaceShip::SpaceShip()
{
	TextureManager::Instance()->load("../Assets/textures/space-ship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
	setMaxSpeed(30.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(30.0f);
	setTurnRate(10.0f);
	setBehaviour(SEEKING);
	setSlowRadius(300.0f);

	setDisplayLines(false);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	//glm::vec2 angle = m_orientation/* + 30.0f*/;
	TextureManager::Instance()->draw("spaceship", 
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	if (getDisplayLines() == true)
	{
		Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 150.0f));
		Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientationMinus * 150.0f));
		Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientationPlus * 150.0f));
		Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientationSideLeft * 100.0f));
		Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientationSideRight * 100.0f));

		Util::DrawCircle(getTransform()->position, getSlowRadius());
	}
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{
}

void SpaceShip::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 SpaceShip::getOrientation() const
{
	return m_orientation;
}

void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

glm::vec2 SpaceShip::getOrientationMinus() const
{
	return m_orientationMinus;
}

void SpaceShip::setOrientationMinus(glm::vec2 orientation)
{
	m_orientationMinus = orientation;
}

glm::vec2 SpaceShip::getOrientationPlus() const
{
	return m_orientationPlus;
}

void SpaceShip::setOrientationPlus(glm::vec2 orientation)
{
	m_orientationPlus = orientation;
}

glm::vec2 SpaceShip::getOrientationSideLeft() const
{
	return m_orientationSideLeft;
}

void SpaceShip::setOrientationSideLeft(glm::vec2 orientation)
{
	m_orientationSideLeft = orientation;
}

glm::vec2 SpaceShip::getOrientationSideRight() const
{
	return m_orientationSideRight;
}

void SpaceShip::setOrientationSideRight(glm::vec2 orientation)
{
	m_orientationSideRight = orientation;
}

float SpaceShip::getRotation() const
{
	return m_rotationAngle;
}

void SpaceShip::setRotation(float angle)
{
	m_rotationAngle = angle;
	auto angle_in_radians = (angle - 90.0f) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);
	
	// convert angle to normalized vector and store in orientation
	setOrientation(glm::vec2(x, y));

	angle_in_radians = (angle - 60.0f) * Util::Deg2Rad;

	x = cos(angle_in_radians);
	y = sin(angle_in_radians);
	
	// convert angle to normalized vector and store in orientation
	setOrientationMinus(glm::vec2(x, y));

	angle_in_radians = (angle - 120.0f) * Util::Deg2Rad;

	x = cos(angle_in_radians);
	y = sin(angle_in_radians);
	
	// convert angle to normalized vector and store in orientation
	setOrientationPlus(glm::vec2(x, y));
	
	angle_in_radians = (angle) * Util::Deg2Rad;

	x = cos(angle_in_radians);
	y = sin(angle_in_radians);
	
	// convert angle to normalized vector and store in orientation
	setOrientationSideRight(glm::vec2(x, y));
	
	angle_in_radians = (angle - 180.0f) * Util::Deg2Rad;

	x = cos(angle_in_radians);
	y = sin(angle_in_radians);
	
	// convert angle to normalized vector and store in orientation
	setOrientationSideLeft(glm::vec2(x, y));
	
}

float SpaceShip::getTurnRate() const
{
	return m_turnRate;
}

void SpaceShip::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float SpaceShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

void SpaceShip::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

Behaviour SpaceShip::getBehaviour()
{
	return m_behaviour;
}

void SpaceShip::setBehaviour(Behaviour behave)
{
	m_behaviour = behave;
}

float SpaceShip::getSlowRadius()
{
	return m_slowRadius;
}

void SpaceShip::setSlowRadius(float radius)
{
	m_slowRadius = radius;
}

GameObject* SpaceShip::getObstacle()
{
	return m_pObstacle;
}

void SpaceShip::setObstacle(GameObject* obstacle)
{
	m_pObstacle = obstacle;
}

bool SpaceShip::getDisplayLines()
{
	return m_displayLines;
}

void SpaceShip::setDisplayLines(bool display)
{
	m_displayLines = display;
}

void SpaceShip::m_Move()
{
	switch (getBehaviour())
	{
	case SEEKING:
		m_seeking();
		setMaxSpeed(10.0f);
		setAccelerationRate(30.0f);
		break;
	case FLEEING:
		m_fleeing();
		setMaxSpeed(10.0f);
		setAccelerationRate(30.0f);
		break;
	case ARRIVAL:
		setMaxSpeed(10.0f);
		setAccelerationRate(20.0f);
		setTurnRate(5.0f);
		m_arrival();
		break;
	case OBSTACLE_AVOIDANCE:
		setMaxSpeed(5.0f);
		setAccelerationRate(20.0f);
		setTurnRate(10.0f);
		m_obstacleAvoidance();
		break;
	}
}

void SpaceShip::m_seeking()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	
	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * deltaTime;

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity; 
}

void SpaceShip::m_fleeing()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = getTransform()->position - m_destination;

	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * deltaTime;

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void SpaceShip::m_arrival()
{
	float timeToTarget = 0.1f;
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	float targetSpeed = 0;

	m_targetDirection = m_destination - getTransform()->position;
	float distance = Util::magnitude(m_targetDirection);
	m_targetDirection = Util::normalize(m_targetDirection);
	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}
	
	if (distance > getSlowRadius())
	{
		targetSpeed = m_maxSpeed;
	}
	else
	{
		targetSpeed = m_maxSpeed * distance / getSlowRadius();

		glm::vec2 targetVelocity = m_targetDirection;
		targetVelocity = Util::normalize(targetVelocity);
		targetVelocity *= targetSpeed;

		m_targetDirection = targetVelocity - getRigidBody()->velocity;
		m_targetDirection /= timeToTarget;
		
		if (Util::magnitude(m_targetDirection) > getAccelerationRate())
		{
			getRigidBody()->velocity /= 1.01;
		}
	}

	if (!(distance == m_stopRadius))
	{
		getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

		getRigidBody()->velocity += getOrientation() * (deltaTime)
			+0.5f * getRigidBody()->acceleration * deltaTime;
	
		getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, targetSpeed);
	
		getTransform()->position += getRigidBody()->velocity;
	}
}

void SpaceShip::m_obstacleAvoidance()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	
	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);
	
	if (CollisionManager::lineRectCheck(getTransform()->position, (getTransform()->position + m_orientationSideLeft * 100.0f), m_pObstacle->getTransform()->position - glm::vec2(100, 50), m_pObstacle->getWidth(), m_pObstacle->getHeight()))
	{
		m_targetRotation = Util::signedAngle(getOrientation(), getOrientationSideRight());
	}
	else if (CollisionManager::lineRectCheck(getTransform()->position, (getTransform()->position + m_orientationSideRight * 100.0f), m_pObstacle->getTransform()->position - glm::vec2(100, 50), m_pObstacle->getWidth(), m_pObstacle->getHeight()))
	{
		m_targetRotation = Util::signedAngle(getOrientation(), getOrientationSideLeft());
	}
	else if (CollisionManager::lineRectCheck(getTransform()->position, (getTransform()->position + m_orientationPlus * 150.0f), m_pObstacle->getTransform()->position - glm::vec2(100, 50), m_pObstacle->getWidth(), m_pObstacle->getHeight()))
	{
		m_targetRotation = Util::signedAngle(getOrientation(), getOrientationMinus());
	}
	else if (CollisionManager::lineRectCheck(getTransform()->position, (getTransform()->position + m_orientationMinus * 150.0f), m_pObstacle->getTransform()->position - glm::vec2(100, 50), m_pObstacle->getWidth(), m_pObstacle->getHeight()))
	{
		m_targetRotation = Util::signedAngle(getOrientation(), getOrientationPlus());
	}
	//else if (CollisionManager::lineRectCheck(getTransform()->position, (getTransform()->position + m_orientation * 150.0f), m_pObstacle->getTransform()->position - glm::vec2(100, 50), m_pObstacle->getWidth(), m_pObstacle->getHeight()))
	//{
	//	m_targetRotation = Util::signedAngle(getOrientation(), getOrientationPlus());
	//}
	else
	{
		m_targetRotation = Util::signedAngle(getOrientation(), m_targetDirection);
	}

	auto turn_sensitivity = 5.0f;
	if (abs(m_targetRotation) > turn_sensitivity)
	{
		if (m_targetRotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (m_targetRotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}
	
	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * deltaTime;

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}
