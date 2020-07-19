#pragma once
#include "Wheel.h"

class Tank
{
private:	
	float MAX_SPEED;
	float MOVE_DX;
	float MAX_ANGLE;
	float FRICTION_FORCE;
	float ANGLE_COEF;
	Render::Texture* _tank;
	short int _x;
	float _speed;
	float _scaleY;
	float _angle;
	float _t;
	//Wheel::HardPrt _
public:
	Tank();
	void init();
	typedef boost::shared_ptr<Tank> HardPrt;
	void draw();
	void update(float dt);
	void moveLeft();
	void moveRight();
};

