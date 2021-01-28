#pragma once
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "DisplayObject.h"

class Obstacle final: public DisplayObject
{
public:
	Obstacle();

	~Obstacle();
	void draw() override;
	void update() override;
	void clean() override;
private:
};

#endif

